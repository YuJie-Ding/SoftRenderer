#pragma once

#include "core.h"
#include "SRMath/SRMath.h"
#include "VertexShader.h"
#include "SRMath/Vector4c.h"

namespace SR
{
	class Texture;
	class Vector4c;

	class DLL_API Fragment
	{
	private:
		Vector4f m_position;

	public:
		Vector4f position;
		Vector4f normal;
		Vector4f uv;
		Vector4c color;

	public:
		Fragment(const Vector4f& position = { 0, 0, 0, 0 },
			const Vector4f& normal = { 0, 0, 0, 0 },
			const Vector4f& uv = { 0, 0, 0, 0 },
			const Vector4c& color = { 0, 0, 0, 0 });
		Fragment(const DefaultVertexAttribute& vertex);



		friend class Renderer;
		friend class FragmentShader;
	};


	class DLL_API FragmentShader
	{
	public:
		FragmentShader()
		: m_texture1(nullptr), m_texture2(nullptr), m_texture3(nullptr), m_texture4(nullptr), m_CubeTexture(nullptr)
		{ }

		virtual Fragment Execute(const Fragment& in) const;		
		
		void SetTexture(Texture* tex)
		{
			m_texture1 = tex;
		}

		const Texture* GetTexture() const
		{
			return m_texture1;
		}

	protected:
		Texture* m_texture1;
		Texture* m_texture2;
		Texture* m_texture3;
		Texture* m_texture4;
		Texture* m_CubeTexture;
	};

}

