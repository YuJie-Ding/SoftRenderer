#pragma once
#include "core.h"

namespace SR
{

	class Vector4c;

	class DLL_API Texture
	{
	public:
		Texture();
		Texture(void *data, uint32_t width, uint32_t height, uint32_t colorNum);
		void BufferData(void* data, uint32_t width, uint32_t height, uint32_t colorNum);
		Vector4c tex(float u, float v) const;

	private:
		uint32_t m_width;
		uint32_t m_height;
		uint32_t m_colorNum; // RGB or RGBA
		unsigned char* m_data;
	};

}
