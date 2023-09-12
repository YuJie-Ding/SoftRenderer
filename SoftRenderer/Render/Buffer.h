#pragma once

#include "core.h"
#include <vector>

namespace SR
{
	enum class DLL_API BufferDataType
	{
		None = 0, Float, Float2, Float3, Float4, Mat4, Int, Int2, Int3, Int4, Bool
	};
	
	static uint32_t BufferDataTypeSize(BufferDataType type)
	{
		switch (type)
		{
			case BufferDataType::Float:    return 4;
			case BufferDataType::Float2:   return 4 * 2;
			case BufferDataType::Float3:   return 4 * 3;
			case BufferDataType::Float4:   return 4 * 4;
			case BufferDataType::Mat4:     return 4 * 4 * 4;
			case BufferDataType::Int:      return 4;
			case BufferDataType::Int2:     return 4 * 2;
			case BufferDataType::Int3:     return 4 * 3;
			case BufferDataType::Int4:     return 4 * 4;
			case BufferDataType::Bool:     return 1;
		}

		SR_ASSERT(false, "Unknown BufferDataType!");
		return 0;
	}

	class DLL_API BufferElement
	{
	public:
		std::string Name;
		BufferDataType Type;
		uint32_t Size;
		uint32_t Offset;
		bool Normalized;

		BufferElement() = delete;

		BufferElement(BufferDataType type, const std::string& name, bool normalized = false)
			: Name(name), Type(type), Size(BufferDataTypeSize(type)), Offset(0), Normalized(normalized)
		{
		}

		uint32_t GetComponentCount() const;
	};

	class DLL_API BufferLayout
	{
	public:
		BufferLayout() {}

		BufferLayout(const std::initializer_list<BufferElement>& elements)
			: m_Elements(elements)
		{
			CalculateOffsetsAndStride();
		}

		inline uint32_t GetStride() const { return m_Stride; }
		inline const std::vector<BufferElement>& GetElements() const { return m_Elements; }

		std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); }
		std::vector<BufferElement>::iterator end() { return m_Elements.end(); }
		std::vector<BufferElement>::const_iterator begin() const { return m_Elements.begin(); }
		std::vector<BufferElement>::const_iterator end() const { return m_Elements.end(); }
	private:
		void CalculateOffsetsAndStride();
	private:
		std::vector<BufferElement> m_Elements;
		uint32_t m_Stride = 0;
	};


	class DLL_API VertexBuffer
	{
	public:
		~VertexBuffer() = default;
		VertexBuffer(void* data = nullptr, uint32_t size = 0)
			: m_Layout({ }), m_size(size)
		{ 
			if (data == nullptr)
			{
				m_data = nullptr;
				return;
			}
			m_data = new char[size];
			memcpy(m_data, data, size);
		}

		const BufferLayout& GetLayout() const { return m_Layout; }
		void SetLayout(const BufferLayout& layout) { m_Layout = layout; }
		void BufferData(void* data, uint32_t size);
	private:
		BufferLayout m_Layout;
		void* m_data;
		uint32_t m_size;
	};


	class DLL_API IndexBuffer
	{
	public:
		~IndexBuffer() = default;
		IndexBuffer(void* data = nullptr, uint32_t count = 0)
			: m_Count(count)
		{ 
			if (data == nullptr)
			{
				m_data = nullptr;
				return;
			}
			m_data = new uint32_t[count];
			memcpy(m_data, data, count * sizeof(uint32_t));
		}

		uint32_t GetCount() const { return m_Count; }
		void BufferData(uint32_t* data, uint32_t count);
	private:
		uint32_t m_Count;
		uint32_t* m_data;
	};

}