﻿#include "Matrix4x4f.h"
#include "Matrix3x3f.h"

#include <assert.h>
#include <cmath>
#include <sstream>

using namespace SR;

SR::Matrix4x4f::Matrix4x4f()
{
	memset(mat, 0, sizeof(mat));
}

SR::Matrix4x4f::Matrix4x4f(const float mat_[4][4])
{
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			mat[i][j] = mat_[i][j];
}

SR::Matrix4x4f::Matrix4x4f(const Vector4f mat_[4])
{
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			mat[i][j] = mat_[i][j];
}

SR::Matrix4x4f::Matrix4x4f(const Matrix3x3f& mat_)
{
	memset(mat, 0, sizeof(mat));
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			mat[i][j] = mat_[i][j];
	mat[3][3] = 1;
}

Matrix4x4f SR::Matrix4x4f::operator+(const Matrix4x4f& m1) const
{
	Matrix4x4f m;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			m[i][j] = mat[i][j] + m1[i][j];
	return m;
}

Matrix4x4f SR::Matrix4x4f::operator-(const Matrix4x4f& m1) const
{
	Matrix4x4f m;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			m[i][j] = mat[i][j] - m1[i][j];
	return m;
}

Matrix4x4f SR::Matrix4x4f::operator*(const Matrix4x4f& m1) const
{
	Matrix4x4f m;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			for(int k = 0; k < 4; k++)
				m[i][j] += mat[i][k] * m1[k][j];
		}
	}
	return m;
}

Vector4f SR::Matrix4x4f::operator*(const Vector4f& v) const
{
	Vector4f vec;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			vec[i] += mat[i][j] * v[j];
		}
	}
	return vec;
}

Matrix4x4f SR::Matrix4x4f::operator*(const float n) const
{
	Matrix4x4f m = *this;
	for (int i = 0; i < 4; i++)
	{
		m[i] *= n;
	}
	return m;
}

Vector4f& SR::Matrix4x4f::operator[](unsigned int index)
{
	return mat[index];
}

const Vector4f SR::Matrix4x4f::operator[](unsigned int index) const
{
	return mat[index];
}

Matrix4x4f SR::Matrix4x4f::Transpose() const
{
	Matrix4x4f m;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			m[i][j] = mat[j][i];
		}
	}
	return m;
}


Matrix4x4f SR::Matrix4x4f::Indentity()
{
	Matrix4x4f m;
	m[0] = { 1.0, 0.0, 0.0, 0.0 };
	m[1] = { 0.0, 1.0, 0.0, 0.0 };
	m[2] = { 0.0, 0.0, 1.0, 0.0 };
	m[3] = { 0.0, 0.0, 0.0, 1.0 };
	return m;
}

Matrix4x4f SR::Matrix4x4f::Transform(const Vector3f& vec)
{
	Matrix4x4f m = Indentity();
	m[0][3] = vec.x;
	m[1][3] = vec.y;
	m[2][3] = vec.z;
	return m;
}

Matrix4x4f SR::Matrix4x4f::Rotation(float angle, Axis axis)
{
	Matrix4x4f m = Indentity();
	float rad = angle * PI / 180.0f;
	float sinA = sin(rad);
	float cosA = cos(rad);
	switch (axis)
	{
	case SR::Axis::Axis_X:
		m[1][1] = cosA;
		m[1][2] = sinA;
		m[2][1] = -sinA;
		m[2][2] = cosA;
		break;
	case SR::Axis::Axis_Y:
		m[0][0] = cosA;
		m[0][2] = sinA;
		m[2][0] = -sinA;
		m[2][2] = cosA;
		break;
	case SR::Axis::Axis_Z:
		m[0][0] = cosA;
		m[0][1] = -sinA;
		m[1][0] = sinA;
		m[1][1] = cosA;
		break;
	default:
		assert(0);
		break;
	}
	return m;
}

Matrix4x4f SR::Matrix4x4f::Scale(const Vector3f& vec)
{
	Matrix4x4f m;
	m[0][0] = vec.x;
	m[1][1] = vec.y;
	m[2][2] = vec.z;
	m[3][3] = 1.0f;
	return m;
}

std::string SR::Matrix4x4f::ToString() const
{
	std::ostringstream ostr;
	ostr << "--- --- Matrix4x4f START --- ---" << std::endl;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			ostr << mat[i][j] << " ";
		}
		ostr << std::endl;
	}
	ostr << "--- --- Matrix4x4f END --- ---" << std::endl;
	return ostr.str();
}

Matrix4x4f SR::Dot(const Matrix4x4f& mat1, const Matrix4x4f& mat2)
{
	return mat1 * mat2;
}

// 投影矩阵，做齐次除法后得到的NDC [0,1];
Matrix4x4f SR::GetProjMatrix(float aspect, float FOV, float near, float far)
{
	float tanFOV_2 = tan(FOV * PI / 360.0f);
	float b = -tanFOV_2 * near;
	float l = b * aspect;
	float t_b_inv = 1 / (-b * 2);
	float r_l_inv = t_b_inv / aspect;
	Matrix4x4f projMat;
	projMat[0][0] = near * r_l_inv;
	projMat[0][2] = -l * r_l_inv;
	projMat[1][1] = near * t_b_inv;
	projMat[1][2] = -b * t_b_inv;
	projMat[2][2] = far / (far - near);
	projMat[2][3] = near * far / (near - far);
	projMat[3][2] = 1.0f;
	return projMat;
}
