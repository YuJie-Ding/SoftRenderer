#pragma once

#include "core.h"
#include <string>

namespace SR
{
	class DLL_API Vector4f
	{
	public:
		Vector4f() = delete;
		Vector4f(const float x_, const float y_, const float z_, const float w_);
		~Vector4f() { }

		Vector4f operator+(const Vector4f& v) const;
		Vector4f operator-(const Vector4f& v) const;
		Vector4f operator*(const float k) const;
		Vector4f operator/(const float k) const;

		Vector4f operator+() const;
		Vector4f operator-() const;


		float Dot(const Vector4f& v) const;
		Vector4f Normalize() const;
		float Magnitude() const;

		std::string ToString();

	public:
		float x;
		float y;
		float z;
		float w;
	};

	float Dot(const Vector4f& v1, const Vector4f& v2);
}