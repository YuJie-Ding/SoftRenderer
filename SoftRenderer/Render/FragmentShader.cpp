#include "FragmentShader.h"
#include "Render/Texture.h"
#include "SRMath/Vector4c.h"

SR::Fragment::Fragment(const Vector4f& position, const Vector4f& normal, const Vector4f& uv, const Vector4c& color)
{
	this->position = position;
	this->normal = normal;
	this->uv = uv;
	this->color = color;
}

SR::Fragment::Fragment(const DefaultVertexAttribute& vertex)
{
	this->position = vertex.position;
	this->normal = vertex.normal;
	this->uv = vertex.uv;
	this->m_position = vertex.m_position;
	this->color = vertex.color;
}

SR::Fragment SR::FragmentShader::Execute(const Fragment& in) const
{
	Fragment frag;
	Vector4f color;
	Vector3f normal = in.normal;
	Vector3f normal_Normalize = normal.Normalize();
	//color = in.uv;
	//color = normal_Normalize;
	//color = (color + 1) * 0.5;
	color = m_texture1->tex(in.uv.x, in.uv.y);
	//color = { 1.0, 1.0, 1.0, 1.0 };
	color = color * 255;
	frag.color = Vector4f(color.x, color.x, color.x, color.x);
	return frag;
}
