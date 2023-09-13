#pragma once
#include "core.h"
#include <string>

namespace SR
{

	class DLL_API Vector2f
	{
	public:
		Vector2f();
		Vector2f(const float x_, const float y_);
		~Vector2f() { }

		Vector2f operator+(const Vector2f& v) const;
		Vector2f operator-(const Vector2f& v) const;
		Vector2f operator*(const float k) const;
		Vector2f operator/(const float k) const;
		Vector2f& operator*=(const float k);

		Vector2f operator+() const;
		Vector2f operator-() const;

		float& operator[](unsigned int index);
		const float& operator[](unsigned int index) const;

		float Dot(const Vector2f& v) const;
		Vector2f Normalize() const;
		float Magnitude() const;

		std::string ToString();

	public:
		float x;
		float y;
	};

	float Dot(const Vector2f& v1, const Vector2f& v2);
}


