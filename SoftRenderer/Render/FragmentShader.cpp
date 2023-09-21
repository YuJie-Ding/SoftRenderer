#include "FragmentShader.h"

SR::Fragment::Fragment(const Vector4f& position, const Vector4f& normal, const Vector4f& uv, const Vector4f& color)
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
