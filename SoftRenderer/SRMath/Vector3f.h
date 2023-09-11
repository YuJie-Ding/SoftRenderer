#pragma once
#include "core.h"
#include <string>

namespace SR
{
	class Vector2f;

	class DLL_API Vector3f
	{
	public:
		Vector3f() = delete;
		Vector3f(const float x_, const float y_, const float z_);
		Vector3f(const Vector2f& vec2, const float z_);
		~Vector3f() { }

		Vector3f operator+(const Vector3f& v) const;
		Vector3f operator-(const Vector3f& v) const;
		Vector3f operator*(const float k) const;
		Vector3f operator/(const float k) const;
		Vector3f& operator*=(const float k);

		Vector3f operator+() const;
		Vector3f operator-() const;

		float& operator[](unsigned int index);
		const float& operator[](unsigned int index) const;

		float Dot(const Vector3f& v) const;
		Vector3f Product(const Vector3f& v) const;
		Vector3f Normalize() const;
		float Magnitude() const;

		std::string ToString();

	public:
		float x;
		float y;
		float z;
	};

	float Dot(const Vector3f& v1, const Vector3f& v2);
	Vector3f Product(const Vector3f& v1, const Vector3f& v2);

}


