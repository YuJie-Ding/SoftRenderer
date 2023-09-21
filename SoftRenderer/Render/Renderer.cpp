#include "Renderer.h"
#include <vector>
#include <chrono>

struct Point
{
	uint32_t x;
	uint32_t y;
};


void SR::Renderer::Init(uint32_t width, uint32_t height)
{
	if (m_Camera == nullptr)
	{
		SR_ASSERT(false, "Renderer hasn't set camera yet!!");
		return;
	}
	if (m_isInit == true)
	{
		return;
	}
	m_Camera->SetFrameBuffer(width, height);
	m_Camera->m_frameBuffer->ClearColor();
	m_isInit = true;
}

void SR::Renderer::ReSize(uint32_t width, uint32_t height)
{
	if (!m_isInit)
		return;
	m_Camera->SetFrameBuffer(width, height);
	m_Camera->m_frameBuffer->ClearColor();
}

#include <Windows.h>
#undef min

const std::shared_ptr<SR::FrameBuffer> SR::Renderer::OnRender(RenderObject& obj, VertexShader& vShader)
{
	if (!m_isInit)
		return nullptr;
	if (m_Camera->m_frameBuffer->GetWidth() == 0 || m_Camera->m_frameBuffer->GetHeight() == 0)
		return nullptr;

	SR::Matrix4x4f model_Mat = SR::Matrix4x4f::Translation(obj.m_translation.m_position) *
		SR::Matrix4x4f::Rotation(obj.m_translation.m_rotation.z, SR::Axis::Axis_Z) *
		SR::Matrix4x4f::Rotation(obj.m_translation.m_rotation.y, SR::Axis::Axis_Y) *
		SR::Matrix4x4f::Rotation(obj.m_translation.m_rotation.x, SR::Axis::Axis_X) *
		SR::Matrix4x4f::Scale(obj.m_translation.m_scaling);
	SR::Matrix4x4f view_Mat = SR::Matrix4x4f::Translation(-m_Camera->m_translation.m_position)*
		SR::Matrix4x4f::Rotation(-m_Camera->m_translation.m_rotation.z, SR::Axis::Axis_Z) *
		SR::Matrix4x4f::Rotation(-m_Camera->m_translation.m_rotation.y, SR::Axis::Axis_Y) *
		SR::Matrix4x4f::Rotation(-m_Camera->m_translation.m_rotation.x, SR::Axis::Axis_X);
	SR::Matrix4x4f proj_Mat = SR::GetProjMatrix(m_Camera->aspect, m_Camera->FOV, m_Camera->m_near, m_Camera->m_far);
	vShader.SetMVP(model_Mat, view_Mat, proj_Mat);


	//m_Camera->m_frameBuffer->ClearCenterColor();
	//m_Camera->m_frameBuffer->ClearZBuffer();
	std::shared_ptr<VertexBuffer> vb = obj.m_vb;
	std::shared_ptr<IndexBuffer> ib = obj.m_ib;
	SR::Vertex *result = new SR::Vertex[ib->GetCount()];

	for (unsigned int i = 0; i < ib->GetCount(); i++)
	{
		unsigned int index = ib->GetIndex(i);
		const float* pObjPosition = (const float*)vb->GetVertexData(index, 0);
		const float* pObjNormal = (const float*)vb->GetVertexData(index, 1);
		const float* pObjUV = (const float*)vb->GetVertexData(index, 2);
		Vector4f ObjPosition = { pObjPosition[0], pObjPosition[1], pObjPosition[2], 1.0f };
		Vector4f ObjNormal = { pObjNormal[0], pObjNormal[1], pObjNormal[2], 0.0f };
		Vector4f uv = { pObjUV[0], pObjUV[1], 0.0, 0.0};
		result[i] = vShader.Execute({ ObjPosition, ObjNormal, uv });
		// 齐次除法，保留w分量（为相机坐标空间下的z值），便于后边透视矫正插值
		{
			result[i].m_position.x /= result[i].m_position.w;
			result[i].m_position.y /= result[i].m_position.w;
			result[i].m_position.z /= result[i].m_position.w;
		}
		// x和y坐标转换到屏幕空间，z坐标保留为齐次裁剪空间的z坐标，用于深度测试
		{
			result[i].m_position.x *= m_Camera->m_frameBuffer->GetCenterWidth();
			result[i].m_position.y *= m_Camera->m_frameBuffer->GetCenterHeight();
		}
		if ((i + 1) % 3 == 0)
		{
			// 裁剪

			// 光栅化和插值
			uint32_t* fragsIndex;
			uint32_t row;
			auto frags = Rasterize(&result[i - 2], &result[i - 1], &result[i], fragsIndex, row);
			// 逐片元操作
			for (int i = 0; i < row; i++)
			{
				for (int j = 0; j < fragsIndex[i]; j++)
				{
					if (frags[i][j].m_position.x >= 0 && frags[i][j].m_position.x < m_Camera->m_frameBuffer->GetCenterWidth() &&
						frags[i][j].m_position.y >= 0 && frags[i][j].m_position.y < m_Camera->m_frameBuffer->GetCenterHeight())
					{
						if (m_Camera->m_frameBuffer->GetZBuffer(frags[i][j].m_position.x, frags[i][j].m_position.y) <
							frags[i][j].m_position.z)
						{
							continue;
						}
						//m_Camera->m_frameBuffer->SetPixelColor(
						//	frags[i][j].m_position.x, 
						//	frags[i][j].m_position.y, 
						//	(uint32_t)((frags[i][j].position.x + 1) / 2 * 255),
						//	(uint32_t)((frags[i][j].position.y + 1) / 2 * 255),
						//	(uint32_t)((frags[i][j].position.z + 1) / 2 * 255),
						//	255
						//);
						//Vector3f normal = frags[i][j].normal;
						//Vector3f normal_Normalize = normal.Normalize();
						//m_Camera->m_frameBuffer->SetPixelColor(
						//	frags[i][j].m_position.x,
						//	frags[i][j].m_position.y,
						//	(uint32_t)(normal_Normalize.x * 255),
						//	(uint32_t)(normal_Normalize.y * 255),
						//	(uint32_t)(normal_Normalize.z * 255),
						//	255
						//);
						frags[i][j].uv = frags[i][j].uv.Normalize();
						m_Camera->m_frameBuffer->SetPixelColor(
							frags[i][j].m_position.x,
							frags[i][j].m_position.y,
							(uint32_t)(frags[i][j].uv.x * 255),
							(uint32_t)(frags[i][j].uv.y * 255),
							0,
							255
						);
						m_Camera->m_frameBuffer->SetZBuffer(frags[i][j].m_position.x, frags[i][j].m_position.y, frags[i][j].m_position.z);
					}
				}
				delete[] frags[i];
			}
			delete[] frags;
			delete[] fragsIndex;
		}
	}
	delete[] result;
	return m_Camera->m_frameBuffer;
}


namespace SR
{
	Fragment** Renderer::Rasterize(SR::Vertex* v1, SR::Vertex* v2, SR::Vertex* v3,
		uint32_t*& fragsIndex_, uint32_t& row_)
	{
		Fragment** frags;
		uint32_t* fragsIndex;
		uint32_t row;

		auto swap = [](Vertex*& v1, Vertex*& v2)
		{
			auto temp = v1;
			v1 = v2;
			v2 = temp;
		};
		if (v1->m_position.y <= v2->m_position.y)
			swap(v1, v2); 
		if (v1->m_position.y <= v3->m_position.y)
			swap(v1, v3);
		if (v2->m_position.y <= v3->m_position.y)
			swap(v2, v3);

		row = ((uint32_t)v1->m_position.y - (uint32_t)v3->m_position.y) + 1;
		row_ = row;
		frags = new Fragment * [row];
		fragsIndex = new uint32_t[row];
		fragsIndex_ = fragsIndex;

		float k1_2_inv = (float)((int)v1->m_position.x - (int)v2->m_position.x) / ((int)v1->m_position.y - (int)v2->m_position.y);
		float k2_3_inv = (float)((int)v2->m_position.x - (int)v3->m_position.x) / ((int)v2->m_position.y - (int)v3->m_position.y);
		float k1_3_inv = (float)((int)v1->m_position.x - (int)v3->m_position.x) / ((int)v1->m_position.y - (int)v3->m_position.y);
		float x1 = (uint32_t)v1->m_position.x;
		float x2 = (uint32_t)v1->m_position.x;
		float x3 = (uint32_t)v2->m_position.x;
		uint32_t count1 = 0;
		for (uint32_t y = v1->m_position.y; y >= (uint32_t)v3->m_position.y; y--)
		{
			uint32_t count2 = 1;
			if (y >= v2->m_position.y)
			{
				float weight1 = sqrt(pow(x1 - v1->m_position.x, 2) + pow(y - v1->m_position.y, 2)) /
					sqrt(pow(v1->m_position.x - v3->m_position.x, 2) + pow(v1->m_position.y - v3->m_position.y, 2)); 
				float weight2 = sqrt(pow(x2 - v1->m_position.x, 2) + pow(y - v1->m_position.y, 2)) /
					sqrt(pow(v1->m_position.x - v2->m_position.x, 2) + pow(v1->m_position.y - v2->m_position.y, 2));
				Vertex v1_l = Lerp(*v1, *v3, weight1);
				v1_l.m_position.x = (uint32_t)x1;
				v1_l.m_position.y = y;
				Vertex v2_l = Lerp(*v1, *v2, weight2);
				v2_l.m_position.x = (uint32_t)x2;
				v2_l.m_position.y = y;
				if ((uint32_t)v1_l.m_position.x > (uint32_t)v2_l.m_position.x)
				{
					auto temp = v1_l;
					v1_l = v2_l;
					v2_l = temp;
				}

				uint32_t lengthOfRow = (uint32_t)abs((long long)v2_l.m_position.x - (long long)v1_l.m_position.x) + 1;
				fragsIndex[count1] = lengthOfRow;
				frags[count1] = new Fragment[lengthOfRow];
				frags[count1][0] = v1_l;
				frags[count1][lengthOfRow - 1] = v1_l;

				for (uint32_t x = v1_l.m_position.x + 1; x < (uint32_t)v2_l.m_position.x; x++)
				{
					frags[count1][count2] =
						Lerp(v1_l, v2_l, (x - (uint32_t)v1_l.m_position.x) / (v2_l.m_position.x - v1_l.m_position.x));
					frags[count1][count2].m_position.x = (uint32_t)x;
					frags[count1][count2].m_position.y = (uint32_t)y;
					count2++;
				}
				x1 -= k1_3_inv;
				x2 -= k1_2_inv;
			}
			else
			{
				float weight1 = sqrt(pow(x1 - v1->m_position.x, 2) + pow(y - v1->m_position.y, 2)) /
					sqrt(pow(v1->m_position.x - v3->m_position.x, 2) + pow(v1->m_position.y - v3->m_position.y, 2));
				float weight2 = sqrt(pow(x3 - v2->m_position.x, 2) + pow(y - v2->m_position.y, 2)) /
					sqrt(pow(v3->m_position.x - v2->m_position.x, 2) + pow(v3->m_position.y - v2->m_position.y, 2));
				Vertex v1_l = Lerp(*v1, *v3, weight1);
				v1_l.m_position.x = (uint32_t)x1;
				v1_l.m_position.y = y;
				Vertex v2_l = Lerp(*v2, *v3, weight2);
				v2_l.m_position.x = (uint32_t)x3;
				v2_l.m_position.y = y;
				if ((uint32_t)v1_l.m_position.x > (uint32_t)v2_l.m_position.x)
				{
					auto temp = v1_l;
					v1_l = v2_l;
					v2_l = temp;
				}
				uint32_t lengthOfRow = (uint32_t)abs((long long)v2_l.m_position.x - (long long)v1_l.m_position.x) + 1;
				fragsIndex[count1] = lengthOfRow;
				frags[count1] = new Fragment[lengthOfRow];
				frags[count1][0] = v1_l;
				frags[count1][lengthOfRow - 1] = v1_l;

				for (uint32_t x = v1_l.m_position.x + 1; x < (uint32_t)v2_l.m_position.x; x++)
				{
					frags[count1][count2] =
						Lerp(v1_l, v2_l, (x - (uint32_t)v1_l.m_position.x) / (v2_l.m_position.x - v1_l.m_position.x));
					frags[count1][count2].m_position.x = (uint32_t)x;
					frags[count1][count2].m_position.y = (uint32_t)y;
					count2++;
				}
				x1 -= k1_3_inv;
				x3 -= k2_3_inv;
			}
			count1++;
		}
		return frags;
	}

}





