#include "RenderObject.h"

SR::RenderObject::RenderObject()
{
	m_name = "No-name Object";
	m_vb.reset(new VertexBuffer());
	m_ib.reset(new IndexBuffer());
	m_transform = Transform();
}

SR::RenderObject::RenderObject(std::string name, std::shared_ptr<VertexBuffer> vb,
	std::shared_ptr<IndexBuffer> ib, const Transform&& Transform)
{
	m_name = name;
	m_vb = vb;
	m_ib = ib;
	m_transform = Transform;
}



