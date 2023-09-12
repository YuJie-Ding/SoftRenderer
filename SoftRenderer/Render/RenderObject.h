#pragma once

#include "Buffer.h"

namespace SR
{

	class RenderObject
	{
	public:
		std::string name;
		VertexBuffer* vb;
		IndexBuffer* ib;
		// TODO: transfrom component;
	};

}
