#pragma once

#include "Utils.h"

using glm::vec3;
using glm::quat;
using glm::mat4;


class BoundingSphere
{
public:
	vec3 center;
	float radius;

	BoundingSphere();

	void Fit(const vector<glm::vec3>& points);

	vector<glm::vec4> GetFrustumPlanes(glm::mat4& transform);

	bool IsTouchingFrustumPlanes(glm::mat4& transform, glm::vec3 positionOfBoundingSphere);
};

