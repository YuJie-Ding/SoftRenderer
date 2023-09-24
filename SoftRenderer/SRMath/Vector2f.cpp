#include "Vector2f.h"
#include "Vector4f.h"
#include <assert.h>
#include <sstream>
#include <cmath>

SR::Vector2f::Vector2f()
{
    x = 0.0f;
    y = 0.0f;
}

SR::Vector2f::Vector2f(const float x_, const float y_)
{
    x = x_;
    y = y_;
}

SR::Vector2f::Vector2f(const Vector4f& v)
{
    x = v.x;
    y = v.y;
}

SR::Vector2f SR::Vector2f::operator+(const Vector2f& v) const
{
    return Vector2f(x + v.x, y + v.y);
}

SR::Vector2f SR::Vector2f::operator-(const Vector2f& v) const
{
    return Vector2f(x - v.x, x - v.y);
}

SR::Vector2f SR::Vector2f::operator*(const float k) const
{
    return Vector2f(x * k, y * k);
}

SR::Vector2f SR::Vector2f::operator/(const float k) const
{
    if (k == 0)
        assert(false);
    return Vector2f(x / k, y / k);
}

SR::Vector2f& SR::Vector2f::operator*=(const float k)
{
    x *= k;
    y *= k;
    return *this;
}

SR::Vector2f SR::Vector2f::operator+() const
{
    return *this;
}

SR::Vector2f SR::Vector2f::operator-() const
{
    return Vector2f(-x, -y);
}

float& SR::Vector2f::operator[](unsigned int index)
{
    switch (index)
    {
    case 0:
        return x;
    case 1:
        return y;
    default:
        assert(false);
    }
}

const float& SR::Vector2f::operator[](unsigned int index) const
{
    switch (index)
    {
    case 0:
        return x;
    case 1:
        return y;
    default:
        assert(false);
    }
}

float SR::Vector2f::Dot(const Vector2f& v) const
{
    return x * v.x + y * v.y;
}

SR::Vector2f SR::Vector2f::Normalize() const
{
    float length = Magnitude();
    if (length == 0.0)
        return Vector2f(0.0f, 0.0f);
    return Vector2f(x / length, y / length);
}

float SR::Vector2f::Magnitude() const
{
    return sqrt(x * x + y * y);
}

std::string SR::Vector2f::ToString()
{
    std::ostringstream ostr;
    ostr << "Vector3f(" << x << ", " << y << ")";
    return ostr.str();
}

float SR::Dot(const Vector2f& v1, const Vector2f& v2)
{
    return v1.Dot(v2);
}
