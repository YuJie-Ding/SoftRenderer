#pragma once

#include "core.h"
#include <string>

namespace SR
{
	class Vector4f;

	class DLL_API Vector4c
	{
	public:
		Vector4c();
		Vector4c(const Vector4f& v);
		Vector4c(const unsigned char r_, const unsigned char g_, const unsigned char b_, const unsigned char a_);
	public:
		unsigned char r;
		unsigned char g;
		unsigned char b;
		unsigned char a;
	};
}

