#include "Matrix4x4f.h"

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
				m[i][j] += mat[i][k] * m[k][j];
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
	Matrix4x4f m;
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

Matrix4x4f SR::Matrix4x4f::Translation(const Vector3f& vec)
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
	float rad = PI / 180.0f * angle;
	float sinA = sin(angle);
	float cosA = cos(angle);
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
