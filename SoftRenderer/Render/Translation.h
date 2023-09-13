#pragma once

#include "core.h"
#include "SRMath/Vector3f.h"

namespace SR
{

	class DLL_API Translation
	{
	public:
		Translation();
		Translation(Vector3f position, Vector3f rotation, Vector3f scaling);

		Translation& operator=(const Translation& t);

		//void Move();
		//void Rotate();
		//void Scale();

	public:
		Vector3f m_position;
		Vector3f m_rotation;
		Vector3f m_scaling;
	};

}

