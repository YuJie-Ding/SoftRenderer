#include "Translation.h"

SR::Transform::Transform()
{
	m_position = { 0.0f, 0.0f, 0.0f };
	m_rotation = { 0.0f, 0.0f, 0.0f };
	m_scaling = { 1.0f, 1.0f, 1.0f };
}

SR::Transform::Transform(Vector3f position, Vector3f rotation, Vector3f scaling)
{
	m_position = position;
	m_rotation = rotation;
	m_scaling = scaling;
}

SR::Transform& SR::Transform::operator=(const Transform& t)
{
	if (&t == this)
		return *this;
	this->m_position = t.m_position;
	this->m_rotation = t.m_rotation;
	this->m_scaling = t.m_scaling;
	return *this;
}