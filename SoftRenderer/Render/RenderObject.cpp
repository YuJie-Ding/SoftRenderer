#include "RenderObject.h"

SR::RenderObject::RenderObject()
{
	m_name = "No-name Object";
	m_vb.reset(new VertexBuffer());
	m_ib.reset(new IndexBuffer());
	m_translation = Translation();
}

SR::RenderObject::RenderObject(std::string name, std::shared_ptr<VertexBuffer> vb,
	std::shared_ptr<IndexBuffer> ib, const Translation&& translation)
{
	m_name = name;
	m_vb = vb;
	m_ib = ib;
	m_translation = translation;
}



