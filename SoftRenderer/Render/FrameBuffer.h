#pragma once
#include <cstdint>

namespace SR
{

	class FrameBuffer
	{
	public:
		FrameBuffer();
		FrameBuffer(uint32_t width, uint32_t height);
		~FrameBuffer();

		void ResetBuffer(uint32_t width, uint32_t height);
		void SetClearColor(char r, char g, char b, char a);
		void ClearColor();
		void ClearZBuffer();
		void SetPixelColor(uint32_t x, uint32_t y, char r, char g, char b, char a);
		void SetZBuffer(uint32_t x, uint32_t y, float value);
		uint32_t GetWidth() { return m_width; }
		uint32_t GetHeight() { return m_height; }
		const void* GetColorData() { return m_colorBuffer; }

	private:
		char* m_colorBuffer;
		float* m_zBuffer;
		uint32_t m_width;
		uint32_t m_height;
		char m_clearColor[4] = { 40, 40, 40, 127 };
	};

}

