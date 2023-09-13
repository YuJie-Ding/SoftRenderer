#pragma once


#include "core.h"
#include "Buffer.h"
#include "Translation.h"
#include <memory>

namespace SR
{

	class DLL_API RenderObject
	{
	public:
		RenderObject();
		RenderObject(std::string name, std::shared_ptr<VertexBuffer> vb,
			std::shared_ptr<IndexBuffer> ib, const Translation&& translation);

	public:
		std::string m_name;
		std::shared_ptr<VertexBuffer> m_vb;
		std::shared_ptr<IndexBuffer> m_ib;
		Translation m_translation;
	};

}
