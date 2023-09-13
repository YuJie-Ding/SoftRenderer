#include "Vector2f.h"
#include "Vector3f.h"
#include <assert.h>
#include <cmath>
#include <sstream>

SR::Vector3f::Vector3f()
{
    x = 0.0f;
    y = 0.0f;
    z = 0.0f;
}

SR::Vector3f::Vector3f(const float x_, const float y_, const float z_)
{
    x = x_;
    y = y_;
    z = z_;
}

SR::Vector3f::Vector3f(const Vector2f& vec2, const float z_)
{
    x = vec2.x;
    y = vec2.y;
    z = z_;
}

SR::Vector3f SR::Vector3f::operator+(const Vector3f& v) const
{
    return Vector3f(x + v.x, y + v.y, z + v.z);
}

SR::Vector3f SR::Vector3f::operator-(const Vector3f& v) const
{
    return Vector3f(x - v.x, x - v.y, z - v.z);
}

SR::Vector3f SR::Vector3f::operator*(const float k) const
{
    return Vector3f(x * k, y * k, z * k);
}

SR::Vector3f SR::Vector3f::operator/(const float k) const
{
    if (k == 0)
        assert(false);
    return Vector3f(x / k, y / k, z / k);
}

SR::Vector3f& SR::Vector3f::operator*=(const float k)
{
    x *= k;
    y *= k;
    z *= k;
    return *this;
}

SR::Vector3f& SR::Vector3f::operator=(const Vector3f& v)
{
    if (&v == this)
        return *this;
    x = v.x;
    y = v.y;
    z = v.z;
    return *this;
}

SR::Vector3f SR::Vector3f::operator+() const
{
    return *this;
}

SR::Vector3f SR::Vector3f::operator-() const
{
    return Vector3f(-x, -y, -z);
}

float& SR::Vector3f::operator[](unsigned int index)
{
    switch (index)
    {
    case 0:
        return x;
    case 1:
        return y;
    case 2:
        return z;
    default:
        assert(false);
    }
}

const float& SR::Vector3f::operator[](unsigned int index) const
{
    switch (index)
    {
    case 0:
        return x;
    case 1:
        return y;
    case 2:
        return z;
    default:
        assert(false);
    }
}

float SR::Vector3f::Dot(const Vector3f& v) const
{
    return x * v.x + y * v.y + z * v.z;
}

SR::Vector3f SR::Vector3f::Product(const Vector3f& v) const
{
    return Vector3f(y * v.z + z * v.y, x * v.z - z * v.x, x * v.y + y * v.x);
}

SR::Vector3f SR::Vector3f::Normalize() const
{
    float length = Magnitude();
    if (length == 0.0)
        return Vector3f(0.0f, 0.0f, 0.0f);
    return Vector3f(x / length, y / length, z / length);
}

float SR::Vector3f::Magnitude() const
{
    return sqrt(x * x + y * y + z * z);
}

std::string SR::Vector3f::ToString()
{
    std::ostringstream ostr;
    ostr << "Vector3f(" << x << ", " << y << ", " << z << ")";
    return ostr.str();
}

float SR::Dot(const Vector3f& v1, const Vector3f& v2)
{
    return v1.Dot(v2);
}

SR::Vector3f SR::Product(const Vector3f& v1, const Vector3f& v2)
{
    return v1.Product(v2);
}
