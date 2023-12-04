#pragma once


#include "core.h"
#include "Buffer.h"
#include "Transform.h"
#include <memory>

namespace SR
{

	class DLL_API RenderObject
	{
	public:
		RenderObject();
		RenderObject(std::string name, std::shared_ptr<VertexBuffer> vb,
			std::shared_ptr<IndexBuffer> ib, const Transform&& Transform);

	public:
		std::string m_name;
		std::shared_ptr<VertexBuffer> m_vb;
		std::shared_ptr<IndexBuffer> m_ib;
		Transform m_transform;
	};

}
