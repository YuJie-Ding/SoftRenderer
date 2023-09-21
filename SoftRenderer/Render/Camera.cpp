#include "Camera.h"

SR::Camera::Camera(Translation translation, float aspect, float FOV, float near, float far)
	:m_translation(translation), aspect(aspect), FOV(FOV), m_near(near), m_far(far)
{
	m_frameBuffer = nullptr;
}

void SR::Camera::SetClearColor(char r, char g, char b, char a)
{
	m_frameBuffer->SetClearColor(r, g, b, a);
}

void SR::Camera::SetCenterClearColor(char r, char g, char b, char a)
{
	m_frameBuffer->SetCenterClearColor(r, g, b, a);
}

void SR::Camera::SetFrameBuffer(uint32_t width, uint32_t height)
{
	m_frameBuffer.reset(new FrameBuffer(width, height, aspect));
}

std::shared_ptr<SR::FrameBuffer> SR::Camera::GetFrameBuffer()
{
	return m_frameBuffer;
}
