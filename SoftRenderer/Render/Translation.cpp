#include "Translation.h"

SR::Translation::Translation()
{
	m_position = { 0.0f, 0.0f, 0.0f };
	m_rotation = { 0.0f, 0.0f, 0.0f };
	m_scaling = { 1.0f, 1.0f, 1.0f };
}

SR::Translation::Translation(Vector3f position, Vector3f rotation, Vector3f scaling)
{
	m_position = position;
	m_rotation = rotation;
	m_scaling = scaling;
}

SR::Translation& SR::Translation::operator=(const Translation& t)
{
	if (&t == this)
		return *this;
	this->m_position = t.m_position;
	this->m_rotation = t.m_rotation;
	this->m_scaling = t.m_scaling;
	return *this;
}