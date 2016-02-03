#pragma once
#include "glm/gtx/quaternion.hpp"
using glm::quat;

class Quaternion :
	public glm::quat
{
public:
	Quaternion();
	~Quaternion();
};

