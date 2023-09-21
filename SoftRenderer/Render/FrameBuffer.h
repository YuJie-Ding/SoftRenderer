#pragma once
#include <cstdint>

namespace SR
{

	class FrameBuffer
	{
	public:
		FrameBuffer();
		FrameBuffer(uint32_t width, uint32_t height, float center_aspect);
		~FrameBuffer();

		const void* GetColorData() { return m_colorBuffer; }
		const void* GetCenterColorData() { return m_center_colorBuffer; }
		uint32_t GetWidth() { return m_width; }
		uint32_t GetHeight() { return m_height; }
		uint32_t GetCenterWidth() { return m_center_width; }
		uint32_t GetCenterHeight() { return m_center_height; }

	private:
		void ResetBuffer(uint32_t width, uint32_t height);
		void SetClearColor(char r, char g, char b, char a);
		void SetCenterClearColor(char r, char g, char b, char a);
		void ClearColor();
		void ClearCenterColor();
		void ClearZBuffer();
		void SetPixelColor(uint32_t x, uint32_t y, char r, char g, char b, char a);
		float GetZBuffer(uint32_t x, uint32_t y);
		void SetZBuffer(uint32_t x, uint32_t y, float value);

	private:
		char* m_center_colorBuffer; // 中心区域的颜色缓冲区
		char* m_colorBuffer;		// 全部区域的颜色缓冲区
		char* m_center_clearColorBuffer; // 用来清除中心区域颜色的颜色缓冲区
		float* m_zBuffer;			// 中心区域的深度缓冲区
		uint32_t m_width;			// 全部区域的宽度
		uint32_t m_height;			// 全部区域的高度
		float m_center_aspect;				// 中心区域宽高比
		uint32_t m_center_width;			// 中心区域的宽度
		uint32_t m_center_height;			// 中心区域的高度
		char m_clearColor[4] = { 40, 40, 40, 127 }; // 全部区域清除颜色
		char m_center_clearColor[4] = { (char)60, (char)60, (char)60, (char)127 }; // 中心区域的清除颜色

		friend class Renderer;
		friend class Camera;
	};

}

