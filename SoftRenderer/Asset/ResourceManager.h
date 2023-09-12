#pragma once
#include "core.h"
#include <memory>
#include <string>


namespace SR
{

	class DLL_API VertexBuffer;
	class DLL_API IndexBuffer;

	struct DLL_API Model_Obj
	{
		std::string name;
		std::shared_ptr<VertexBuffer> vb;
		std::shared_ptr<IndexBuffer> ib;
		std::string information;
	};

	DLL_API Model_Obj LoadObjFromFile(std::string filePath);
}