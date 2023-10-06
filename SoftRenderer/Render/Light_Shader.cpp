#include "Light_Shader.h"
#include "Renderer.h"
#include "Render/Texture.h"

namespace SR
{
	Vertex Light_VShader::Execute(const Vertex& in) const
	{
		Vertex out;
		out.position = model_Mat * in.position;
		Matrix3x3f model_Mat_Inv3x3 = model_Mat_Inv;
		Matrix3x3f model_Mat_Inv3x3_T = model_Mat_Inv3x3.Transpose();
		out.normal = model_Mat_Inv3x3 * Vector3f(in.normal);
		out.color = in.color;
		out.uv = in.uv;

		out.Object2Clip_POS(in, MVP);
		return out;
	}

	Fragment Light_FShader::Execute(const Fragment& in) const
	{
		Fragment frag;
		Vector4f texColor;
		Vector4f color;
		texColor = m_texture1->tex(in.uv.x, in.uv.y);

		Vector3f worldNormal = Vector3f(in.normal).Normalize();
		Vector3f worldLithtDir = Vector3f{ 0.0, 0.0, 0.0 }.Normalize();
		Vector3f viewDir = (GetWorldCameraPos() - in.position).Normalize();
		Vector3f halfDir = (worldLithtDir + viewDir).Normalize();

		Vector3f lightColor = Vector3f(1.0, 1.0, 1.0);
		Vector3f diffuseColor = Vector3f(0.5, 0.5, 0.5);


		Vector3f specular = lightColor * pow(std::max(0.0f, Dot(worldNormal, halfDir)), 20);
		Vector3f diffuse;
		float a = Dot(worldNormal, viewDir);
		diffuse.x = lightColor.x * diffuseColor.x * a * texColor.x;
		diffuse.y = lightColor.y * diffuseColor.y * a * texColor.y;
		diffuse.z = lightColor.z * diffuseColor.z * a * texColor.z;
		Vector3f ambient = texColor * 0.2;

		color = ambient + diffuse + specular;
		color = color * 255;
		frag.color = color;

		return frag;
	}
}