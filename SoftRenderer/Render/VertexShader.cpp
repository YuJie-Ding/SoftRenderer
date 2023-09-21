#include "VertexShader.h"

void SR::VertexShader::SetMVP(Matrix4x4f model_Mat, Matrix4x4f view_Mat, Matrix4x4f proj_Mat)
{
	this->model_Mat = model_Mat;
	this->view_Mat = view_Mat;
	this->proj_Mat = proj_Mat;
	MVP = proj_Mat * view_Mat * model_Mat;
}

SR::Vertex SR::VertexShader::Execute(const Vertex& in) const
{
	Vertex out;
	//out.position = model_Mat * view_Mat * in.position;
	out.position = in.position;
	out.normal = in.normal;
	out.color = in.color;
	out.uv = in.uv;

	out.m_position = MVP * in.position;
	return out;
}

SR::Vertex SR::Lerp(const SR::Vertex& v1, const SR::Vertex& v2, double weight)
{
	SR::Vertex out;
	float t = (weight * v1.m_position.w) / ((weight * v1.m_position.w + (1 - weight) * v2.m_position.w));
	if (t > 0 == false)
	{
		int a = 0;
	}
	out.m_position.z = v1.m_position.z + t * (v2.m_position.z - v1.m_position.z);
	out.m_position.w = v1.m_position.w + t * (v2.m_position.w - v1.m_position.w);
	out.position = SR::Lerp(v1.position, v2.position, t);
	out.normal = SR::Lerp(v1.normal, v2.normal, t);
	out.uv = SR::Lerp(v1.uv, v2.uv, t);
	out.color = SR::Lerp(v1.color, v2.color, t);
	return out;
}

SR::Vertex::Vertex(const Vector4f& position, const Vector4f& normal, const Vector4f& uv, const Vector4f& color)
{
	this->position = position;
	this->normal = normal;
	this->uv = uv;
	this->color = color;
}

SR::Vertex::Vertex(const Vertex& vertex)
{
	this->m_position = vertex.m_position;
	this->position = vertex.position;
	this->normal = vertex.normal;
	this->uv = vertex.uv;
	this->color = vertex.color;
}
