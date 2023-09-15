#include "ResourceManager.h"
#include "Render/Buffer.h"
#include "SRMath/SRMath.h"
#include "core.h"

#include <sstream>
#include <fstream>
#include <vector>

std::vector<std::string> SplitString(std::string srcString, char splitChar)
{
	std::istringstream tempStringStream(srcString);
	std::string token;
	std::vector<std::string> splitStrings;
	while (std::getline(tempStringStream, token, splitChar))
	{
		splitStrings.push_back(token);
	}
	return splitStrings;
}

SR::Model_Obj SR::LoadObjFromFile(std::string filePath)
{
	Model_Obj obj;
	obj.vb.reset(new VertexBuffer());
	obj.ib.reset(new IndexBuffer());
	std::ifstream objFileStream;
	objFileStream.open(filePath, std::ios::in);
	std::string line;
	if (!objFileStream.is_open())
	{
		SR_ASSERT(false, "Open .obj file Failed!")
	}
	std::vector<SR::Vector3f> positionData;
	std::vector<SR::Vector3f> normalData;
	std::vector<SR::Vector2f> uvData;
	struct Index
	{
		int posIndex;
		int norIndex;
		int uvIndex;
		int code = 0;
		bool operator==(const Index& i)
		{
			return posIndex == i.posIndex && norIndex == i.norIndex && uvIndex == i.uvIndex;
		}
	};
	std::vector<Index> indexData;
	struct Vertex
	{
		SR::Vector3f positionData;
		SR::Vector3f normalData;
		SR::Vector2f uvData;
	};
	std::vector<Vertex> vertexes; // 重组后的顶点数据
	int count = 0;
	int n = 0;
	while (std::getline(objFileStream, line))
	{
		if (line == "")
			continue;
		auto splitLine = SplitString(line, ' ');
		std::string attr = splitLine[0];

		if (attr == "#") // 注释
		{
			obj.information += splitLine[1] + "\n";
		}
		else if (attr == "o") // name
		{
			obj.name = splitLine[1];
		}
		else if(attr == "v") // position
		{
			float position1, position2, position3;
			position1 = atof(splitLine[1].c_str());
			position2 = atof(splitLine[2].c_str());
			position3 = atof(splitLine[3].c_str());
			positionData.push_back({ position1, position2, position3 });
		}
		else if(attr == "vn") // normal
		{
			float normal1, normal2, normal3;
			normal1 = atof(splitLine[1].c_str());
			normal2 = atof(splitLine[2].c_str());
			normal3 = atof(splitLine[3].c_str());
			normalData.push_back({ normal1, normal2, normal3 });
		}
		else if (attr == "vt") // uv
		{
			float uv1, uv2;
			uv1 = atof(splitLine[1].c_str());
			uv2 = atof(splitLine[2].c_str());
			uvData.push_back({ uv1, uv2 });
		}
		else if (attr == "f") // index
		{
			for (int i = 1; i <= 3; i++)
			{
				auto splitIndex = SplitString(splitLine[i], '/');
				int posIndex = atoi(splitIndex[0].c_str());
				int uvIndex = splitIndex.size() > 1 ? atoi(splitIndex[1].c_str()) : 0;
				int norIndex = splitIndex.size() > 2 ? atoi(splitIndex[2].c_str()) : 0;
				auto existed = std::find(indexData.begin(), indexData.end(), Index{ posIndex, norIndex, uvIndex });
				if (indexData.end() == existed)
				{
					indexData.push_back({ posIndex, norIndex, uvIndex, count++ });
					vertexes.push_back({ positionData[posIndex - 1], 
										(norIndex == 0) ? SR::Vector3f() : normalData[norIndex - 1],
										(uvIndex == 0) ? SR::Vector2f() : (uvData[uvIndex - 1])
									});
				}
				else
				{
					indexData.push_back(*existed);
				}
			}
		}
		else
		{
			std::cout << "unknow .obj attr: " << attr << std::endl;
		}
		n++;
	}
	SR_ASSERT(indexData.size(), "num of index is 0");

	int* indexes = new int[indexData.size()]; // 重组后的索引数据
	count = 0;
	for (auto& index : indexData)
	{
		indexes[count] = index.code;
		count++;
	}
	obj.ib->BufferData((uint32_t*)indexes, count);
	obj.vb->BufferData((void*)&vertexes[0], vertexes.size() * sizeof(Vertex));
	obj.vb->SetLayout({
		{ SR::BufferDataType::Float3, "vertexPosition" },
		{ SR::BufferDataType::Float3, "vertexNormal" },
		{ SR::BufferDataType::Float2, "vertexUV" }
	});
	std::cout << "load obj file successfully\n";
	return obj;
}
