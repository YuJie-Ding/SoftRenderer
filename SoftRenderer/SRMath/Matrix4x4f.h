#pragma once

#include "core.h"
#include "SRMath/Vector3f.h"
#include "SRMath/Vector4f.h"
#include "SRMath/SRMathConstant.h"

#include <string>


namespace SR
{
	class DLL_API Matrix4x4f
	{
	public:
		Matrix4x4f();
		Matrix4x4f(const float mat_[4][4]);
		Matrix4x4f(const Vector4f mat_[4]);

		Matrix4x4f operator+(const Matrix4x4f& m1) const;
		Matrix4x4f operator-(const Matrix4x4f& m1) const;

		Matrix4x4f operator*(const Matrix4x4f& m1) const;
		Vector4f operator*(const Vector4f& v) const;
		Matrix4x4f operator*(const float n) const;
		Vector4f& operator[](unsigned int index);
		const Vector4f operator[](unsigned int index) const;


		// 返回转置矩阵
		Matrix4x4f Transpose() const;
		
		// 返回单位矩阵
		static Matrix4x4f Indentity();
		// 返回平移矩阵
		static Matrix4x4f Translation(const Vector3f& vec);
		// 返回旋转矩阵
		static Matrix4x4f Rotation(float angle, Axis axis);
		// 返回缩放矩阵
		static Matrix4x4f Scale(const Vector3f& vec);

		std::string ToString() const;

	private:
		Vector4f mat[4];
	};

	Matrix4x4f Dot(const Matrix4x4f& mat1, const Matrix4x4f& mat2);

}

