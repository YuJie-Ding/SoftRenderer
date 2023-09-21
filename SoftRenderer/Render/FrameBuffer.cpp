#include "FrameBuffer.h"
#include <memory>
#include <iostream>
#include <windows.h>

SR::FrameBuffer::FrameBuffer()
{
	m_colorBuffer = nullptr;
	m_center_colorBuffer = nullptr;
	m_center_clearColorBuffer = nullptr;
	m_zBuffer = nullptr;
	m_width = 0;
	m_height = 0;
	m_center_width = 0;
	m_center_height = 0;
	SetClearColor(m_clearColor[0], m_clearColor[1], m_clearColor[2], m_clearColor[3]);
	SetCenterClearColor(m_center_clearColor[0], m_center_clearColor[1], m_center_clearColor[2], m_center_clearColor[3]);
}

SR::FrameBuffer::FrameBuffer(uint32_t width, uint32_t height, float center_aspect)
{
	m_width = width;
	m_height = height;
	m_center_aspect = center_aspect;
	float aspect = (float)width / height;
	if (aspect >= m_center_aspect)
	{
		m_center_height = height;
		m_center_width = m_center_aspect * height;
	}
	else
	{
		m_center_width = width;
		m_center_height = width / m_center_aspect;
	}
	m_colorBuffer = new char[width * height * 4];
	m_center_colorBuffer = new char[m_center_width * m_center_height * 4];
	m_center_clearColorBuffer = new char[m_center_width * m_center_height * 4];
	m_zBuffer = new float[m_center_width * m_center_height];
	SetClearColor(m_clearColor[0], m_clearColor[1], m_clearColor[2], m_clearColor[3]);
	SetCenterClearColor(m_center_clearColor[0], m_center_clearColor[1], m_center_clearColor[2], m_center_clearColor[3]);
}

SR::FrameBuffer::~FrameBuffer()
{
	if (m_colorBuffer != nullptr)
		delete[] m_colorBuffer;
	if (m_center_colorBuffer)
		delete[] m_center_colorBuffer;
	if (m_center_clearColorBuffer != nullptr)
		delete[] m_center_clearColorBuffer;
	if (m_zBuffer != nullptr)
		delete[] m_zBuffer;
}

void SR::FrameBuffer::ResetBuffer(uint32_t width, uint32_t height)
{
	if (m_colorBuffer != nullptr)
		delete[] m_colorBuffer;
	if (m_center_colorBuffer)
		delete[] m_center_colorBuffer;
	if (m_center_clearColorBuffer != nullptr)
		delete[] m_center_clearColorBuffer;
	if (m_zBuffer != nullptr)
		delete[] m_zBuffer;
	m_width = width;
	m_height = height;
	float aspect = (float)width / height;
	if (aspect > m_center_aspect)
	{
		m_center_height = height;
		m_center_width = m_center_aspect * height;
	}
	else
	{
		m_center_width = width;
		m_center_height = m_center_aspect / width;
	}
	m_colorBuffer = new char[width * height * 4];
	m_center_colorBuffer = new char[m_center_width * m_center_height * 4];
	m_center_clearColorBuffer = new char[m_center_width * m_center_height * 4];
	m_zBuffer = new float[m_center_width * m_center_height];
}

void SR::FrameBuffer::SetClearColor(char r, char g, char b, char a)
{
	m_clearColor[0] = r;
	m_clearColor[1] = g;
	m_clearColor[2] = b;
	m_clearColor[3] = a;
}

void SR::FrameBuffer::SetCenterClearColor(char r, char g, char b, char a)
{
	m_center_clearColor[0] = r;
	m_center_clearColor[1] = g;
	m_center_clearColor[2] = b;
	m_center_clearColor[3] = a;
	uint32_t pos;
	for (uint32_t i = 0; i < m_center_height; i++)
	{
		for (uint32_t j = 0; j < m_center_width; j++)
		{
			pos = (i * m_center_width + j) * 4;
			m_center_clearColorBuffer[pos] = m_center_clearColor[2];
			m_center_clearColorBuffer[pos + 1] = m_center_clearColor[1];
			m_center_clearColorBuffer[pos + 2] = m_center_clearColor[0];
			m_center_clearColorBuffer[pos + 3] = m_center_clearColor[3];
		}
	}
}

void SR::FrameBuffer::ClearColor()
{
	uint32_t pos;
	for (uint32_t i = 0; i < m_height; i++)
	{
		for (uint32_t j = 0; j < m_width; j++)
		{
			pos = (i * m_width + j) * 4;
			m_colorBuffer[pos] = m_clearColor[2];
			m_colorBuffer[pos + 1] = m_clearColor[1];
			m_colorBuffer[pos + 2] = m_clearColor[0];
			m_colorBuffer[pos + 3] = m_clearColor[3];
		}
	}
}

void SR::FrameBuffer::ClearCenterColor()
{
	memcpy(m_center_colorBuffer, m_center_clearColorBuffer, m_center_width * m_center_height * 4);
}

void SR::FrameBuffer::ClearZBuffer()
{
	std::fill(m_zBuffer, m_zBuffer + m_center_width * m_center_height, 1.0f);
}

void SR::FrameBuffer::SetPixelColor(uint32_t x, uint32_t y, char r, char g, char b, char a)
{
	uint32_t pos = (y * m_center_width + x) * 4;
	m_center_colorBuffer[pos] = b;
	m_center_colorBuffer[pos + 1] = g;
	m_center_colorBuffer[pos + 2] = r;
	m_center_colorBuffer[pos + 3] = a;
}

float SR::FrameBuffer::GetZBuffer(uint32_t x, uint32_t y)
{
	uint32_t pos = (y * m_center_width + x);
	return m_zBuffer[pos];
}

void SR::FrameBuffer::SetZBuffer(uint32_t x, uint32_t y, float value)
{
	uint32_t pos = (y * m_center_width + x);
	m_zBuffer[pos] = value;
}
