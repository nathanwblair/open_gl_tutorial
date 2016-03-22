#pragma once
#include "Utils.h"
#include "Shader.h"

#include "MathTypes/Transform.h"
#include "Cameras/Camera.h"

class MeshShader
	: public Shader
{
public:
	MeshShader(string _path="default.shader");

	void InitializeUniforms() override;

	void UpdateUniforms(Camera& camera, Transform& lightTransform, Transform& transform);

	void InitializeAttributes();
};

