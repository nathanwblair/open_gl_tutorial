#pragma once

#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "glm/trigonometric.hpp"
#include "glm/gtx/quaternion.hpp"
#include "glm/ext.hpp"
#include "Quaternion.h"

using glm::vec3;
using glm::quat;
using glm::mat4;


class Transform
{
public:
	vec3 position;
	vec3 scale;
	Quaternion rotation;
   
	Transform(vec3 _position = vec3(0), vec3 _scale = vec3(0), Quaternion _rotation = vec3(0, 0, 0))
	{
		position = _position;
		scale = _scale;
		rotation = _rotation;
	}
	~Transform();

	mat4 GetTransform()
	{
		return glm::scale(scale) * glm::mat4_cast(rotation.quaternion) * glm::translate(position);
	}
};

