#include "VertexAttribute.h"

SR::DefaultVertexAttribute SR::Lerp(const SR::DefaultVertexAttribute& v1, const SR::DefaultVertexAttribute& v2, double weight)
{
	SR::DefaultVertexAttribute out;
	// 透视矫正插值
	double t = (weight * v1.m_position.w) / ((weight * v1.m_position.w + (1 - weight) * v2.m_position.w));
	//t = weight;
	out.m_position.z = v1.m_position.z + t * (v2.m_position.z - v1.m_position.z);
	out.m_position.w = v1.m_position.w + t * (v2.m_position.w - v1.m_position.w);
	out.position = SR::Lerp(v1.position, v2.position, t);
	out.normal = SR::Lerp(v1.normal, v2.normal, t);
	out.uv = SR::Lerp(v1.uv, v2.uv, t);
	out.color = SR::Lerp(v1.color, v2.color, t);
	return out;
}

SR::DefaultVertexAttribute::DefaultVertexAttribute(const Vector4f& position, const Vector4f& normal, const Vector4f& uv, const Vector4f& color)
{
	this->position = position;
	this->normal = normal;
	this->uv = uv;
	this->color = color;
}

SR::DefaultVertexAttribute::DefaultVertexAttribute(const DefaultVertexAttribute& vertex)
{
	this->m_position = vertex.m_position;
	this->position = vertex.position;
	this->normal = vertex.normal;
	this->uv = vertex.uv;
	this->color = vertex.color;
}

void SR::DefaultVertexAttribute::Object2Clip_POS(const DefaultVertexAttribute& in, const Matrix4x4f& MVP)
{
	m_position = MVP * in.position;
}
