#pragma once

#include "core.h"
#include "SRMath/SRMath.h"

namespace SR
{

	class DLL_API Vertex
	{
	private:
		Vector4f m_position;

	public:
		Vertex(const Vector4f& position = {0, 0, 0, 0},
				const Vector4f& normal = { 0, 0, 0, 0 },
				const Vector4f& uv = { 0, 0, 0, 0 },
				const Vector4f& color = { 0, 0, 0, 0 });
		Vertex(const Vertex& vertex);
		Vector4f position;
		Vector4f normal;
		Vector4f uv;
		Vector4f color;
		void Object2Clip_POS(const Vertex& in, const Matrix4x4f& MVP); // 将顶点坐标变换到裁剪空间
		friend class VertexShader;
		friend class Fragment;
		friend class Renderer;
		friend Vertex Lerp(const SR::Vertex& v1, const SR::Vertex& v2, double weight);
	};

	Vertex Lerp(const Vertex& v1, const Vertex& v2, double weight);

	class DLL_API VertexShader
	{
	public:
		VertexShader() { }
		virtual Vertex Execute(const Vertex& in) const;
		void SetMVP(Matrix4x4f model_Mat, Matrix4x4f view_Mat, Matrix4x4f proj_Mat);

	protected:
		Matrix4x4f model_Mat = Matrix4x4f::Indentity();
		Matrix4x4f model_Mat_Inv = Matrix4x4f::Indentity();
		Matrix4x4f view_Mat = Matrix4x4f::Indentity();
		Matrix4x4f proj_Mat = Matrix4x4f::Indentity();
		Matrix4x4f MVP;
	};

}

