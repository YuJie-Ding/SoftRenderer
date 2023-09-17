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
	m_frameBuffer.reset(new FrameBuffer(width, height));
	m_isInit = true;
}

void SR::Renderer::ReSize(uint32_t width, uint32_t height)
{
	if (!m_isInit)
		return;
	m_frameBuffer.reset(new FrameBuffer(width, height));
}
#include <Windows.h>
#undef min

const std::shared_ptr<SR::FrameBuffer> SR::Renderer::OnRender(RenderObject& obj, const VertexShader& vShader)
{
	if (!m_isInit)
		return nullptr;
	if (m_frameBuffer->GetWidth() == 0 || m_frameBuffer->GetHeight() == 0)
		return nullptr;

	m_frameBuffer->ClearColor();
	std::shared_ptr<VertexBuffer> vb = obj.m_vb;
	std::shared_ptr<IndexBuffer> ib = obj.m_ib;
	SR::Vertex *result = new SR::Vertex[ib->GetCount()];


	std::chrono::time_point<std::chrono::high_resolution_clock> d_start;
	d_start = std::chrono::high_resolution_clock::now();

	for (unsigned int i = 0; i < ib->GetCount(); i++)
	{
		unsigned int index = ib->GetIndex(i);
		const float* pObjPosition = (const float*)vb->GetVertexData(index, 0);
		const float* pObjNormal = (const float*)vb->GetVertexData(index, 1);
		Vector4f ObjPosition = { pObjPosition[0], pObjPosition[1], pObjPosition[2], 1.0f };
		Vector4f ObjNormal = { pObjNormal[0], pObjNormal[1], pObjNormal[2], 0.0f };
		Vector4f uv;
		result[i] = vShader.Execute({ ObjPosition, ObjNormal, uv });
	}
	auto d_end = std::chrono::high_resolution_clock::now();
	auto _start = std::chrono::time_point_cast<std::chrono::microseconds>(d_start)
		.time_since_epoch()
		.count();
	auto _end = std::chrono::time_point_cast<std::chrono::microseconds>(d_end)
		.time_since_epoch()
		.count();
	auto duration = _end - _start;
	std::cout << duration << std::endl;

	float width = m_frameBuffer->GetWidth();
	float height = m_frameBuffer->GetHeight();
	float minPixel = std::min(width, height);
	//if (width > height)
	//{
	//	for (unsigned int i = (width - height) / 2.0; i < (width + height) / 2.0; i++)
	//	{
	//		for (unsigned int j = 0; j < minPixel; j++)
	//		{
	//			m_frameBuffer->SetPixelColor(i, j, 128, 100, 200, 0);
	//		}
	//	}
	//}
	//else
	//{
	//	for (unsigned int i = 0; i < minPixel; i++)
	//	{
	//		for (unsigned int j = (height - width) / 2.0; j < (height + width) / 2.0; j++)
	//		{
	//			m_frameBuffer->SetPixelColor(i, j, 128, 100, 200, 0);
	//		}
	//	}
	//}

	int count = 0;
	float X1;
	float Y1;
	float X2;
	float Y2;
	//std::chrono::time_point<std::chrono::high_resolution_clock> d_start;
	//d_start = std::chrono::high_resolution_clock::now();
	for (unsigned int i = 0; i < ib->GetCount(); i++)
	{
		auto& vertex = result[i];
		float x, y;
		if (width > height)
		{
			x = (vertex.position.x / vertex.position.z + 1.0) / 2 * minPixel + (width - height) / 2.0;
			y = (vertex.position.y / vertex.position.z + 1.0) / 2 * minPixel;
		}
		else
		{
			x = (vertex.position.x / vertex.position.z + 1.0) / 2 * minPixel;
			y = (vertex.position.y / vertex.position.z + 1.0) / 2 * minPixel + (height - width) / 2.0;
		}
		if (count == 0)
		{
			X1 = x;
			Y1 = y;
		}
		else if (count == 1)
		{
			if (X1 < 0 || x < 0 || Y1 < 0 || y < 0 || X1 >= width || x >= width || Y1 >= height || y >= height)
				continue;
			DrawLine(X1, Y1, x, y);

			X2 = x;
			Y2 = y;
		}
		else if (count == 2)
		{
			if (X1 < 0 || x < 0 || Y1 < 0 || y < 0 || X1 >= width || x >= width || Y1 >= height || y >= height)
				continue;
			if (X2 < 0 || Y2 < 0 || X2 >= width || Y2 >= height)
				continue;
			DrawLine(X2, Y2, x, y);
			DrawLine(X1, Y1, x, y);
		}
		count++;
		if (count == 3)
			count = 0;
	}			
	//auto d_end = std::chrono::high_resolution_clock::now();
	//auto _start = std::chrono::time_point_cast<std::chrono::microseconds>(d_start)
	//	.time_since_epoch()
	//	.count();
	//auto _end = std::chrono::time_point_cast<std::chrono::microseconds>(d_end)
	//	.time_since_epoch()
	//	.count();
	//auto duration = _end - _start;
	//std::cout << duration << std::endl;
	delete[] result;
	return m_frameBuffer;
}


namespace SR
{

	Point* GetLinePoints(Point start, Point end, unsigned int& count)
	{
		int vecX = (int)end.x - (int)start.x;
		int vecY = (int)end.y - (int)start.y;
		Point* points;
		int counter = 0;
		if (abs(vecX) > abs(vecY))
		{
			if (vecX > 0)
			{
				float y = start.y;
				float k = (float)vecY / vecX;
				points = new Point[end.x - start.x + 1];
				for (uint32_t x = start.x; x <= end.x; x++)
				{
					points[counter++] = { x, (unsigned int)y };
					y += k;
				}
			}
			else
			{
				float y = end.y;
				float k = (float)vecY / vecX;
				points = new Point[start.x - end.x + 1];
				for (uint32_t x = end.x; x <= start.x; x++)
				{
					points[counter++] = { x, (unsigned int)y };
					y += k;
				}
			}
		}
		else
		{
			if (vecY > 0)
			{
				float x = start.x;
				float k = (float)vecX / vecY;
				points = new Point[end.y - start.y + 1];
				for (uint32_t y = start.y; y <= end.y; y++)
				{
					points[counter++] = { (unsigned int)x, (unsigned int)y };
					x += k;
				}
			}
			else
			{
				float x = end.x;
				float k = (float)vecX / vecY;
				points = new Point[start.y - end.y + 1];
				for (uint32_t y = end.y; y <= start.y; y++)
				{
					points[counter++] = { (unsigned int)x, (unsigned int)y };
					x += k;
				}
			}

		}
		count = counter;
		return points;
	}

	void SR::Renderer::DrawLine(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2)
	{
		if (!m_isInit)
			return;
		unsigned int count;
		Point* points = GetLinePoints({ x1, y1 }, { x2, y2 }, count);
		for (unsigned i = 0; i < count; i++)
		{
			m_frameBuffer->SetPixelColor(points[i].x, points[i].y, 255, 255, 255, 0);
		}
		delete[] points;
	}

}





