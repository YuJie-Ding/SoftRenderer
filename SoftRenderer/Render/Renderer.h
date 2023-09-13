#pragma once

#include "core.h"
#include "Render/RenderObject.h"
#include "Render/VertexShader.h"

namespace SR
{

	class DLL_API Renderer
	{
	public:
		Renderer() { }

		std::vector<SR::Vertex> OnRender(RenderObject& obj, const VertexShader& vShader);
	};

}


