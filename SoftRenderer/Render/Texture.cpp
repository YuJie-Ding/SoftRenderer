#include "Texture.h"
#include "SRMath/Vector4f.h"


SR::Texture::Texture()
{
    m_width = m_height = 0;
    m_data = nullptr;
    m_channel = 0;
}

SR::Texture::Texture(void* data, uint32_t width, uint32_t height, uint32_t channel)
{
    m_data = new unsigned char[width * height * channel];
    memcpy(m_data, data, width * height * channel);
    m_width = width;
    m_height = height;
    m_channel = channel;
}

void SR::Texture::BufferData(void* data, uint32_t width, uint32_t height, uint32_t channel)
{
    if (m_data != nullptr)
        delete[] m_data;
    m_data = new unsigned char[width * height * channel];
    memcpy(m_data, data, width * height * channel);
    m_width = width;
    m_height = height;
    m_channel = channel;
}

SR::Vector4f SR::Texture::tex(float u, float v) const
{
    Vector4f color;
    u = u < 0 ? 0 : u - (int)(u);
    v = v < 0 ? 0 : v - (int)(v);
    uint32_t w = u * m_width;
    uint32_t h = v * m_height;
    uint32_t pos = (h * m_width + w) * m_channel;
    color.x = m_channel <= 0 ? 0 : m_data[pos + 2] / 255.0;
    color.y = m_channel <= 1 ? 0 : m_data[pos + 1] / 255.0;
    color.z = m_channel <= 2 ? 0 : m_data[pos + 0] / 255.0;
    color.w = m_channel <= 3 ? 0 : m_data[pos + 3] / 255.0;
    return color;
}
