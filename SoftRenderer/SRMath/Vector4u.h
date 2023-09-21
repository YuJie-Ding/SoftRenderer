#pragma once

#include "core.h"
#include <string>
#include "Vector4f.h"

namespace SR
{
	class Vector4u
	{
	public:
		Vector4u();
		Vector4u(const uint32_t x_, const uint32_t y_, const uint32_t z_, const uint32_t w_);
		Vector4u(const Vector4f& v4f);
		//Vector4u(const Vector2f& vec3, const float z_ = 0.0f, const float w_ = 0.0f);
		//Vector4u(const Vector3f& vec3, const float w_ = 0.0f);
		~Vector4u() { }

		//Vector4u operator+(const Vector4u& v) const;
		//Vector4u operator-(const Vector4u& v) const;
		//Vector4u operator*(const float k) const;
		//Vector4u operator/(const float k) const;
		//Vector4u& operator*=(const float k);

		//Vector4u operator+() const;
		//Vector4u operator-() const;

		uint32_t& operator[](unsigned int index);
		const uint32_t& operator[](unsigned int index) const;

		//float Dot(const Vector4u& v) const;
		//Vector4u Normalize() const;
		//float Magnitude() const;

		//std::string ToString() const;

	public:
		uint32_t x;
		uint32_t y;
		uint32_t z;
		uint32_t w;
	};


}

