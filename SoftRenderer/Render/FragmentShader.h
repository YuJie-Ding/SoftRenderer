#pragma once

#include "core.h"
#include "SRMath/SRMath.h"
#include "VertexShader.h"

namespace SR
{

	class Fragment
	{
	private:
		Vector4f m_position;

	public:
		Fragment(const Vector4f& position = { 0, 0, 0, 0 },
			const Vector4f& normal = { 0, 0, 0, 0 },
			const Vector4f& uv = { 0, 0, 0, 0 },
			const Vector4f& color = { 0, 0, 0, 0 });
		Fragment(const Vertex& vertex);
		Vector4f position;
		Vector4f normal;
		Vector4f uv;
		Vector4f color;

		friend class Renderer;
		friend class FragmentShader;
	};


	class FragmentShader
	{

	};

}

