#include "Vector4u.h"

namespace SR
{
	Vector4u::Vector4u()
	{
		x = y = z = w = 0;
	}

	Vector4u::Vector4u(const uint32_t x_, const uint32_t y_, const uint32_t z_, const uint32_t w_)
	{
		x = x_;
		y = y_;
		z = z_;
		w = w_;
	}

	Vector4u::Vector4u(const Vector4f& v4f)
	{
		x = (uint32_t)v4f.x;
		y = (uint32_t)v4f.y;
		z = (uint32_t)v4f.z;
		w = (uint32_t)v4f.w;
	}

	uint32_t& Vector4u::operator[](unsigned int index)
	{
		switch (index)
		{
		case 0:
			return x;
		case 1:
			return y;
		case 2:
			return z;
		case 3:
			return w;
		default:
			assert(false);
		}
	}

	const uint32_t& Vector4u::operator[](unsigned int index) const
	{
		switch (index)
		{
		case 0:
			return x;
		case 1:
			return y;
		case 2:
			return z;
		case 3:
			return w;
		default:
			assert(false);
		}
	}

}
