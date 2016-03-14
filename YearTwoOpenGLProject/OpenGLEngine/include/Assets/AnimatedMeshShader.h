#pragma once
#include "Utils.h"

#include "MeshShader.h"

#include "MathTypes/Transform.h"
#include "Cameras/Camera.h"

class AnimatedMeshShader
	: public MeshShader
{
public:
	AnimatedMeshShader(string _path = "skinning.shader")
		: MeshShader(_path)
	{
	}


	virtual void InitializeUniforms() override
	{
		MeshShader::InitializeUniforms();

		PrepareUniform("Bones");
	}


	void UpdateBones(glm::mat4 * bones, int numBones)
	{
		SetArrayUniform<glm::mat4>("Bones", bones, numBones);
	}
};

