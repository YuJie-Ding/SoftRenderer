#pragma once

#include "core.h"
#include "Render/RenderObject.h"
#include "Render/VertexShader.h"
#include "Render/VertexAttribute.h"
#include "Render/FrameBuffer.h"
#include "Render/FragmentShader.h"
#include "Render/Texture.h"
#include "Camera.h"
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

		const std::shared_ptr<FrameBuffer> OnRender(RenderObject& obj, VertexShader& vShader, FragmentShader& fShader);
		void SetCamera(std::shared_ptr<SR::Camera> camera)
		{
			m_Camera = camera;
		}

		std::shared_ptr<Camera> GetCamera()
		{
			return m_Camera;
		}

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
		Renderer()
			:m_Camera(nullptr)
		{ }

		Fragment** Rasterize(SR::DefaultVertexAttribute* v1, SR::DefaultVertexAttribute* v2, SR::DefaultVertexAttribute* v3,
			uint32_t*& fragsIndex_, uint32_t& row_);

	private:
		std::shared_ptr<Camera> m_Camera;
		bool m_isInit = false;
	};

	Vector4f GetWorldCameraPos();

}


