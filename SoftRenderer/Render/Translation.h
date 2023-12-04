#pragma once

#include "core.h"
#include "SRMath/Vector3f.h"

namespace SR
{

	class DLL_API Transform
	{
	public:
		Transform();
		Transform(Vector3f position, Vector3f rotation, Vector3f scaling);

		Transform& operator=(const Transform& t);

	public:
		Vector3f m_position;
		Vector3f m_rotation;
		Vector3f m_scaling;
	};

}

