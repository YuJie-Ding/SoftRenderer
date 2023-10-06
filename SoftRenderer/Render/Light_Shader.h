#pragma once

#include "Render/VertexShader.h"
#include "Render/FragmentShader.h"

namespace SR
{
	class DLL_API Light_VShader : public VertexShader
	{
		virtual Vertex Execute(const Vertex& in) const override;
	};


	class DLL_API Light_FShader : public FragmentShader
	{
		virtual Fragment Execute(const Fragment& in) const override;
	};

}
