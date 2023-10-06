#pragma once
#include "core.h"

namespace SR
{

	class Vector4f;
	class Vector4c;

	class DLL_API Texture
	{
	public:
		Texture();
		Texture(void *data, uint32_t width, uint32_t height, uint32_t channel);
		void BufferData(void* data, uint32_t width, uint32_t height, uint32_t channel);
		Vector4f tex(float u, float v) const;

	private:
		uint32_t m_width;
		uint32_t m_height;
		uint32_t m_channel; // RGB or RGBA
		unsigned char* m_data;
	};

}
