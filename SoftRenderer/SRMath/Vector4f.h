#pragma once

#include "core.h"
#include <string>

namespace SR
{
	class Vector3f;
	class Vector2f;
	class Matrix4x4f;

	class DLL_API Vector4f
	{
	public:
		Vector4f();
		Vector4f(const float x_, const float y_, const float z_, const float w_);
		Vector4f(const Vector2f& vec3, const float z_ = 0.0f, const float w_ = 0.0f);
		Vector4f(const Vector3f& vec3, const float w_ = 0.0f);
		~Vector4f() { }

		Vector4f operator+(const Vector4f& v) const;
		Vector4f operator-(const Vector4f& v) const;
		Vector4f operator*(const float k) const;
		Vector4f operator*(const Matrix4x4f& mat) const;
		Vector4f operator/(const float k) const;
		Vector4f& operator*=(const float k);

		Vector4f operator+() const;
		Vector4f operator-() const;

		float& operator[](unsigned int index);
		const float& operator[](unsigned int index) const;

		float Dot(const Vector4f& v) const;
		Vector4f Normalize() const;
		float Magnitude() const;

		std::string ToString() const;

	public:
		float x;
		float y;
		float z;
		float w;
	};

	float Dot(const Vector4f& v1, const Vector4f& v2);
}