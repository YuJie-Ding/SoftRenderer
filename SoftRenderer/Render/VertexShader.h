#pragma once

#include "core.h"
#include "SRMath/SRMath.h"
#include "VertexAttribute.h"

namespace SR
{

	class DLL_API VertexShader
	{
	public:
		VertexShader() { }
		virtual DefaultVertexAttribute Execute(const DefaultVertexAttribute& in) const;
		void SetMVP(Matrix4x4f model_Mat, Matrix4x4f view_Mat, Matrix4x4f proj_Mat);

	protected:
		Matrix4x4f model_Mat = Matrix4x4f::Indentity();
		Matrix4x4f model_Mat_Inv = Matrix4x4f::Indentity();
		Matrix4x4f view_Mat = Matrix4x4f::Indentity();
		Matrix4x4f proj_Mat = Matrix4x4f::Indentity();
		Matrix4x4f MVP;
	};

}

