#include "Texture.h"
#include "SRMath/Vector4c.h"


SR::Texture::Texture()
{
    m_width = m_height = 0;
    m_data = nullptr;
    m_colorNum = 0;
}

SR::Texture::Texture(void* data, uint32_t width, uint32_t height, uint32_t colorNum)
{
    m_data = new unsigned char[width * height * colorNum];
    memcpy(m_data, data, width * height * colorNum);
    m_width = width;
    m_height = height;
    m_colorNum = colorNum;
}

void SR::Texture::BufferData(void* data, uint32_t width, uint32_t height, uint32_t colorNum)
{
    if (m_data != nullptr)
        delete[] m_data;
    m_data = new unsigned char[width * height * colorNum];
    memcpy(m_data, data, width * height * colorNum);
    m_width = width;
    m_height = height;
    m_colorNum = colorNum;
}

SR::Vector4c SR::Texture::tex(float u, float v) const
{
    Vector4c color;
    u = u < 0 ? 0 : u - (int)(u);
    v = v < 0 ? 0 : v - (int)(v);
    uint32_t w = u * m_width;
    uint32_t h = v * m_height;
    uint32_t pos = (h * m_width + w) * m_colorNum;
    color.r = m_colorNum <= 0 ? 0 : m_data[pos + 2];
    color.g = m_colorNum <= 1 ? 0 : m_data[pos + 1];
    color.b = m_colorNum <= 2 ? 0 : m_data[pos + 0];
    color.a = m_colorNum <= 3 ? 0 : m_data[pos + 3];
    return color;
}
