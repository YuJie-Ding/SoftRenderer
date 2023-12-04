#pragma once
#include "core.h"
#include "SRMath/SRMath.h"

namespace SR
{

	class DLL_API DefaultVertexAttribute
	{
	protected:
		Vector4f m_position;

	public:
		DefaultVertexAttribute(const Vector4f& position = { 0, 0, 0, 0 },
			const Vector4f& normal = { 0, 0, 0, 0 },
			const Vector4f& uv = { 0, 0, 0, 0 },
			const Vector4f& color = { 0, 0, 0, 0 });
		DefaultVertexAttribute(const DefaultVertexAttribute& vertex);
		Vector4f position;
		Vector4f normal;
		Vector4f uv;
		Vector4f color;
		void Object2Clip_POS(const DefaultVertexAttribute& in, const Matrix4x4f& MVP); // 将顶点坐标变换到裁剪空间

		friend DefaultVertexAttribute Lerp(const SR::DefaultVertexAttribute& v1, const SR::DefaultVertexAttribute& v2, double weight);

		friend class VertexShader;
		friend class Fragment;
		friend class Renderer;
	};

	DefaultVertexAttribute Lerp(const DefaultVertexAttribute& v1, const DefaultVertexAttribute& v2, double weight);
}

