#include "Assets/MeshShader.h"

MeshShader::MeshShader(string _path) : Shader(_path) 
{
}

void MeshShader::InitializeUniforms() {
	vector<string> locationUniforms = {
			"Projection",
			"View",
			"Model",
			"ProjectionView",
			"ProjectionViewModel",
			"CameraPosition",
			"LightDirection"
	};

	vector<string> textureUniforms = {
			"DiffuseTexture",
			"AmbientTexture",
			"GlowTexture",
			"SpecularTexture",
			"GlossTexture",
			"NormalTexture",
			"AlphaTexture",
			"DisplacementTexture"
	};

	PrepareUniforms(locationUniforms);
	PrepareUniforms(textureUniforms);

	for (int index = 0; index < (int)textureUniforms.size(); index++)
	{
		SetUniform<int>(textureUniforms[index], index);
	}
}

void MeshShader::UpdateUniforms(Camera& camera, Transform& lightTransform, Transform& transform) {
	SetUniform<glm::mat4>("Model", transform.GetTransform());
	SetUniform<glm::mat4>("Projection", camera.GetProjection());
	SetUniform<glm::mat4>("View", camera.GetView());
	SetUniform<glm::mat4>("ProjectionView", camera.GetProjectionView());
	SetUniform<glm::vec3>("CameraPosition", camera.GetPosition());

	auto lightDirection = lightTransform.GetTransform() * glm::vec4(1, 0, 0, 0);
	SetUniform<glm::vec4>("LightDirection", lightDirection);

	SetUniform<int>("SpecPower", 14);
}

void MeshShader::InitializeAttributes() {
	SetAttribute<glm::vec4>("position");
	SetAttribute<glm::vec2>("texCoord");
	//SetAttribute<glm::vec4>("position");
	//SetAttribute<glm::vec4>("colour");
	//SetAttribute<glm::vec4>("normal");
	//SetAttribute<glm::vec4>("tangent");
	//SetAttribute<glm::vec4>("binormal");
	//SetAttribute<glm::vec4>("indices");
	//SetAttribute<glm::vec4>("weights");
	//SetAttribute<glm::vec2>("texCoord1");
	//SetAttribute<glm::vec2>("texCoord2");
}