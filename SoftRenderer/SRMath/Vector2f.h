#pragma once

namespace SR
{

	class Vector2f
	{
	public:
		Vector2f() = delete;
		Vector2f(const float x_, const float y_);
		~Vector2f() { }

		Vector2f operator+(const Vector2f& other) const;
		Vector2f operator-(const Vector2f& other) const;
		Vector2f operator*(const float k) const;
		Vector2f operator/(const float k) const;

		Vector2f operator+() const;
		Vector2f operator-() const;


		float Dot(const Vector2f& other) const;
		Vector2f Normalize() const;
		float Magnitude() const;


	private:
		float x;
		float y;
		float length;
	};

	float Dot(const Vector2f& v1, const Vector2f& v2);
}


