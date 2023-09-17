#include "FrameBuffer.h"
#include <memory>
#include <iostream>
#include <windows.h>

SR::FrameBuffer::FrameBuffer()
{
	m_colorBuffer = nullptr;
	m_clearColorBuffer = nullptr;
	m_zBuffer = nullptr;
	m_width = 0;
	m_height = 0;
	SetClearColor(m_clearColor[0], m_clearColor[1], m_clearColor[2], m_clearColor[3]);
}

SR::FrameBuffer::FrameBuffer(uint32_t width, uint32_t height)
{
	m_width = width;
	m_height = height;
	m_colorBuffer = new char[width * height * 4];
	m_clearColorBuffer = new char[m_width * m_height * 4];
	m_zBuffer = new float[width * height];
	SetClearColor(m_clearColor[0], m_clearColor[1], m_clearColor[2], m_clearColor[3]);
}

SR::FrameBuffer::~FrameBuffer()
{
	if (m_colorBuffer != nullptr)
		delete[] m_colorBuffer;
	if (m_clearColorBuffer)
		delete[] m_clearColorBuffer;
	if (m_zBuffer != nullptr)
		delete[] m_zBuffer;
}

void SR::FrameBuffer::ResetBuffer(uint32_t width, uint32_t height)
{
	if (m_clearColorBuffer)
		delete[] m_clearColorBuffer;
	if (m_colorBuffer != nullptr)
		delete[] m_colorBuffer;
	if (m_zBuffer != nullptr)
		delete[] m_zBuffer;
	m_width = width;
	m_height = height;
	m_colorBuffer = new char[width * height * 4];
	m_clearColorBuffer = new char[m_width * m_height * 4];
	m_zBuffer = new float[width * height];
}

void SR::FrameBuffer::SetClearColor(char r, char g, char b, char a)
{
	m_clearColor[0] = r;
	m_clearColor[1] = g;
	m_clearColor[2] = b;
	m_clearColor[3] = a;
	uint32_t pos;
	for (uint32_t i = 0; i < m_height; i++)
	{
		for (uint32_t j = 0; j < m_width; j++)
		{
			pos = (i * m_width + j) * 4;
			m_clearColorBuffer[pos] = m_clearColor[2];
			m_clearColorBuffer[pos + 1] = m_clearColor[1];
			m_clearColorBuffer[pos + 2] = m_clearColor[0];
			m_clearColorBuffer[pos + 3] = m_clearColor[3];
		}
	}
}

void SR::FrameBuffer::ClearColor()
{
	memcpy(m_colorBuffer, m_clearColorBuffer, m_width * m_height * 4);
}

void SR::FrameBuffer::ClearZBuffer()
{
	for (uint32_t i = 0; i < m_height; i++)
	{
		for (uint32_t j = 0; j < m_width; j++)
		{
			m_zBuffer[i * m_width + j] = 0.0f;
		}
	}
}

void SR::FrameBuffer::SetPixelColor(uint32_t x, uint32_t y, char r, char g, char b, char a)
{
	uint32_t pos = (y * m_width + x) * 4;
	m_colorBuffer[pos] = b;
	m_colorBuffer[pos + 1] = g;
	m_colorBuffer[pos + 2] = r;
	m_colorBuffer[pos + 3] = a;
}

void SR::FrameBuffer::SetZBuffer(uint32_t x, uint32_t y, float value)
{
	uint32_t pos = (y * m_width + x) * 4;
	m_zBuffer[pos] = value;
}
