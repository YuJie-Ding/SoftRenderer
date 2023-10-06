#include "Vector2f.h"
#include "Vector3f.h"
#include "Vector4f.h"
#include "Vector4c.h"
#include "Matrix4x4f.h"
#include <assert.h>
#include <cmath>
#include <sstream>

SR::Vector4f::Vector4f()
{
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
	w = 0.0f;
}

SR::Vector4f::Vector4f(const float x_, const float y_, const float z_, const float w_)
{
	x = x_;
	y = y_;
	z = z_;
	w = w_;
}

SR::Vector4f::Vector4f(const Vector2f& vec3, const float z_, const float w_)
{
	x = vec3.x;
	y = vec3.y;
	z = z_;
	w = w_;
}

SR::Vector4f::Vector4f(const Vector3f& vec3, const float w_)
{
	x = vec3.x;
	y = vec3.y;
	z = vec3.z;
	w = w_;
}

SR::Vector4f::Vector4f(const Vector4c& v)
{
	this->x = v.r;
	this->y = v.g;
	this->z = v.b;
	this->w = v.a;
}

SR::Vector4f SR::Vector4f::operator+(float n) const
{
	return Vector4f(x + n, y + n, z + n, w + n);
}

SR::Vector4f SR::Vector4f::operator+(const Vector4f& v) const
{
	return Vector4f(x + v.x, y + v.y, z + v.z, w + v.w);
}

SR::Vector4f SR::Vector4f::operator-(const Vector4f& v) const
{
	return Vector4f(x - v.x, x - v.y, z - v.z, w - v.w);
}

SR::Vector4f SR::Vector4f::operator*(const float k) const
{
	return Vector4f(x * k, y * k, z * k, w * k);
}

// 注意：和线性代数中定义的乘法不同
SR::Vector4f SR::Vector4f::operator*(const Matrix4x4f& mat) const
{
	assert(false);
	return mat.Transpose() * (*this);
}

SR::Vector4f SR::Vector4f::operator/(const float k) const
{
	if (k == 0)
		assert(false);
	return Vector4f(x / k, y / k, z / k, w / k);
}

SR::Vector4f& SR::Vector4f::operator*=(const float k) 
{
	x *= k;
	y *= k;
	z *= k;
	w *= k;
	return *this;
}

SR::Vector4f SR::Vector4f::operator+() const
{
	return *this;
}

SR::Vector4f SR::Vector4f::operator-() const
{
	return Vector4f(-x, -y, -z, -w);
}

float& SR::Vector4f::operator[](unsigned int index)
{
	switch (index)
	{
	case 0:
		return x;
	case 1:
		return y;
	case 2:
		return z;
	case 3:
		return w;
	default:
		assert(false);
	}
}

const float& SR::Vector4f::operator[](unsigned int index) const
{
	switch (index)
	{
	case 0:
		return x;
	case 1:
		return y;
	case 2:
		return z;
	case 3:
		return w;
	default:
		assert(false);
	}
}

float SR::Vector4f::Dot(const Vector4f& v) const
{
	return x * v.x + y * v.y + z * v.z + w * v.w;
}

SR::Vector4f SR::Vector4f::Normalize() const
{
	float length = Magnitude();
	if (length == 0.0)
		return Vector4f(0.0f, 0.0f, 0.0f, 0.0f);
	return Vector4f(x / length, y / length, z / length, w / length);
}

float SR::Vector4f::Magnitude() const
{
	return sqrt(x * x + y * y + z * z + w * w);
}

std::string SR::Vector4f::ToString() const
{
	std::ostringstream ostr;
	ostr << "Vector4f(" << x << ", " << y << ", " << z << ", " << w << ")";
	return ostr.str();
}

float SR::Dot(const Vector4f& v1, const Vector4f& v2)
{
	return v1.Dot(v2);
}

SR::Vector4f SR::Lerp(const Vector4f& v1, const Vector4f& v2, double weight)
{
	return v1 * (1 - weight) + v2 * weight;
}
