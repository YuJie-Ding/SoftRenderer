#include "VertexShader.h"

void SR::VertexShader::SetMVP(Matrix4x4f model_Mat, Matrix4x4f view_Mat, Matrix4x4f proj_Mat)
{
	this->model_Mat = model_Mat;
	this->view_Mat = view_Mat;
	this->proj_Mat = proj_Mat;
	MVP = proj_Mat * view_Mat * model_Mat;
}

SR::Vertex SR::VertexShader::Execute(const Vertex& in) const
{
	Vertex out;
	out.position = MVP * in.position;
	//out.normal = MVP * in.normal;
	return out;
}
