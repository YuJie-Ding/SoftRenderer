#include "VertexShader.h"

SR::Vertex SR::VertexShader::Execute(const Vertex& in) const
{
	Vertex out;
	Matrix4x4f MVP =  proj_Mat * view_Mat * model_Mat;
	out.position = MVP * in.position;
	out.normal = MVP * in.normal;
	return out;
}
