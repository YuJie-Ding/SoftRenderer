#pragma once

#include "core.h"
#include "Buffer.h"
#include "FrameBuffer.h"
#include "Translation.h"
#include <memory>

namespace SR
{

	class DLL_API Camera
	{
	public:
		Camera(Translation translation = { {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {1.0, 1.0, 1.0} },
			float aspect = 1, float FOV = 60.0, float near = 0.3, float far = 1000);

		void SetClearColor(char r, char g, char b, char a);
		void SetCenterClearColor(char r, char g, char b, char a);
		void ClearColor()
		{
			m_frameBuffer->ClearCenterColor();
		}

		void ClearZBuffer()
		{
			m_frameBuffer->ClearZBuffer();
		}

		std::shared_ptr<FrameBuffer> GetFrameBuffer();

	public:
		Translation m_translation;
		float aspect;
		float FOV;
		float m_near;
		float m_far;


	private:
		void SetFrameBuffer(uint32_t width, uint32_t height);
		std::shared_ptr<FrameBuffer> m_frameBuffer;

		friend class Renderer;
	};

}

