#pragma once

#include "core.h"
#include "Render/RenderObject.h"
#include "Render/VertexShader.h"
#include "Render/FrameBuffer.h"
#include <memory>

namespace SR
{
	class Renderer;

	static Renderer* s_Instance = nullptr;

	class DLL_API Renderer
	{
	public:
		void Init(uint32_t width, uint32_t height);
		void ReSize(uint32_t width, uint32_t height);

		const std::shared_ptr<FrameBuffer> OnRender(RenderObject& obj, const VertexShader& vShader);

		static Renderer* Create()
		{
			if (SR::s_Instance != nullptr)
				delete SR::s_Instance;
			SR::s_Instance = new Renderer();
			return SR::s_Instance;
		}

		static Renderer* GetInstance()
		{
			return SR::s_Instance;
		}

	private:
		Renderer() { }

		void DrawLine(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2);

	private:
		std::shared_ptr<FrameBuffer> m_frameBuffer;
		bool m_isInit = false;
	};

}


