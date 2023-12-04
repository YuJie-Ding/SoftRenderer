#include "VertexShader.h"

void SR::VertexShader::SetMVP(Matrix4x4f model_Mat, Matrix4x4f view_Mat, Matrix4x4f proj_Mat)
{
	this->model_Mat = model_Mat;
	this->view_Mat = view_Mat;
	this->proj_Mat = proj_Mat;
	this->model_Mat_Inv = Matrix3x3f(model_Mat).Inverse();
	MVP = proj_Mat * view_Mat * model_Mat;
}

SR::DefaultVertexAttribute SR::VertexShader::Execute(const DefaultVertexAttribute& in) const
{
	DefaultVertexAttribute out;
	out.position = in.position;
	out.normal = Matrix3x3f(model_Mat_Inv).Transpose() * Vector3f(in.normal);
	out.normal = in.normal;
	out.uv = in.uv;

	out.Object2Clip_POS(in, MVP);
	return out;
}