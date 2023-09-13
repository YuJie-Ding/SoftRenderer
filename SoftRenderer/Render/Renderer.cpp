#include "Renderer.h"

std::vector<SR::Vertex> SR::Renderer::OnRender(RenderObject& obj, const VertexShader& vShader)
{
	std::shared_ptr<VertexBuffer> vb = obj.m_vb;
	std::shared_ptr<IndexBuffer> ib = obj.m_ib;
	std::vector<SR::Vertex> result;
	for (unsigned int i = 0; i < ib->GetCount(); i++)
	{
		unsigned int index = ib->GetIndex(i);
		const float* pObjPosition = (const float*)vb->GetVertexData(index, 0);
		const float* pObjNormal = (const float*)vb->GetVertexData(index, 1);
		Vector4f ObjPosition = { pObjPosition[0], pObjPosition[1], pObjPosition[2], 1.0f };
		Vector4f ObjNormal = { pObjNormal[0], pObjNormal[1], pObjNormal[2], 0.0f };
		Vector4f uv;
		result.push_back(vShader.Execute({ ObjPosition, ObjNormal, uv }));
	}
	return result;
}
