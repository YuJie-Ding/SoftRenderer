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

SR::Fragment::Fragment(const Vertex& vertex)
{
	this->position = vertex.position;
	this->normal = vertex.normal;
	this->uv = vertex.uv;
	this->color = vertex.color;
	this->m_position = vertex.m_position;
}

SR::Fragment SR::FragmentShader::Execute(const Fragment& in) const
{
	Fragment frag;
	Vector3f normal = in.normal;
	Vector3f normal_Normalize = normal.Normalize();
	frag.color.r = (uint32_t)((normal_Normalize.x + 1) / 2 * 255);
	frag.color.g = (uint32_t)((normal_Normalize.y + 1) / 2 * 255);
	frag.color.b = (uint32_t)((normal_Normalize.z + 1) / 2 * 255);
	//frag.color = m_texture1->tex(in.uv.x, in.uv.y);
	//frag.color.r = frag.color.r;
	//frag.color.g = frag.color.g;
	//frag.color.b = frag.color.b;
	return frag;
}
