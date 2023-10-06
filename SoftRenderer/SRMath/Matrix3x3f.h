#pragma once

#include "core.h"
#include "SRMath/Vector3f.h"
#include "SRMath/Vector4f.h"
#include "SRMath/SRMathConstant.h"

#include <string>

namespace SR
{
	class Matrix4x4f;

	class DLL_API Matrix3x3f
	{
	public:
		Matrix3x3f();
		Matrix3x3f(const float mat_[3][3]);
		Matrix3x3f(const Vector3f mat_[3]);
		Matrix3x3f(const Matrix4x4f& mat_);

		Vector3f operator*(const Vector3f& v) const;
		Matrix3x3f operator*(const float n) const;
		Vector3f& operator[](unsigned int index);
		const Vector3f operator[](unsigned int index) const;


		// 返回转置矩阵
		Matrix3x3f Transpose() const;
		// 返回逆矩阵
		Matrix3x3f Inverse() const;
		// 求行列式
		float Det() const;


	private:
		Vector3f mat[3];
	};

}
