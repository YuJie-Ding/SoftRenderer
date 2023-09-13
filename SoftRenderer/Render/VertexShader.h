#pragma once

#include "core.h"
#include "SRMath/SRMath.h"

namespace SR
{

	struct DLL_API Vertex
	{
		Vector4f position;
		Vector4f normal;
		Vector4f uv;
	};

	class DLL_API VertexShader
	{
	public:
		VertexShader() { }
		virtual Vertex Execute(const Vertex& in) const;

	public:
		Matrix4x4f model_Mat;
		Matrix4x4f view_Mat;
		Matrix4x4f proj_Mat;
	};

}
