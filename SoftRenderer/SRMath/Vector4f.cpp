#include "Vector4f.h"
#include <assert.h>
#include <cmath>
#include <sstream>

SR::Vector4f::Vector4f(const float x_, const float y_, const float z_, const float w_)
{
	x = x_;
	y = y_;
	z = z_;
	w = w_;
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

SR::Vector4f SR::Vector4f::operator/(const float k) const
{
	if (k == 0)
		assert(false);
	return Vector4f(x / k, y / k, z / k, w / k);
}

SR::Vector4f SR::Vector4f::operator+() const
{
	return *this;
}

SR::Vector4f SR::Vector4f::operator-() const
{
	return Vector4f(-x, -y, -z, -w);
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

std::string SR::Vector4f::ToString()
{
	std::ostringstream ostr;
	ostr << "Vector4f(" << x << ", " << y << ", " << z << ", " << w << ")";
	return ostr.str();
}

float SR::Dot(const Vector4f& v1, const Vector4f& v2)
{
	return v1.Dot(v2);
}
