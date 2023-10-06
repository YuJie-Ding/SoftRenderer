#include "Vector4c.h"
#include "Vector4f.h"
#include <iostream>

SR::Vector4c::Vector4c()
{
	r = g = b = a = 0;
}

SR::Vector4c::Vector4c(const SR::Vector4f& v)
{
	this->r = v.x < 0 ? 0 : std::min(v.x, 255.0f);
	this->g = v.y < 0 ? 0 : std::min(v.y, 255.0f);
	this->b = v.z < 0 ? 0 : std::min(v.z, 255.0f);
	this->a = v.w < 0 ? 0 : std::min(v.w, 255.0f);
}

SR::Vector4c::Vector4c(const unsigned char r_, const unsigned char g_, const unsigned char b_, const unsigned char a_)
{
	r = r_;
	g = g_;
	b = b_;
	a = a_;
}
