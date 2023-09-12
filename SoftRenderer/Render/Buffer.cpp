#include "Buffer.h"

void SR::VertexBuffer::BufferData(void* data, uint32_t size)
{
	if (m_data != nullptr)
		delete[] m_data;
	m_data = new char[size];
	memcpy(m_data, data, size);
	m_size = size;
}

void SR::IndexBuffer::BufferData(uint32_t* data, uint32_t count)
{
	if (m_data != nullptr)
		delete[] m_data;
	m_data = new uint32_t[count];
	memcpy(m_data, data, count * sizeof(uint32_t));
	m_Count = count;
}

void SR::BufferLayout::CalculateOffsetsAndStride()
{
	uint32_t offset = 0;
	m_Stride = 0;
	for (auto& element : m_Elements)
	{
		element.Offset = offset;
		offset += element.Size;
		m_Stride += element.Size;
	}
}

uint32_t SR::BufferElement::GetComponentCount() const
{
	switch (Type)
	{
		case BufferDataType::Float:   return 1;
		case BufferDataType::Float2:  return 2;
		case BufferDataType::Float3:  return 3;
		case BufferDataType::Float4:  return 4;
		case BufferDataType::Mat4:    return 4 * 4;
		case BufferDataType::Int:     return 1;
		case BufferDataType::Int2:    return 2;
		case BufferDataType::Int3:    return 3;
		case BufferDataType::Int4:    return 4;
		case BufferDataType::Bool:    return 1;
	}

	SR_ASSERT(false, "Unknown BufferDataType!");
	return 0;
}
