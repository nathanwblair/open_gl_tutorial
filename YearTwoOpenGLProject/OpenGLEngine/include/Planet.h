#pragma once
#define GLM_SWIZZLE_XYZW 
#include "gl_core_4_4.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "glm/trigonometric.hpp"
#include "glm/gtx/quaternion.hpp"
#include "glm/ext.hpp"
#include "Gizmos.h"

class Planet
{
	Planet * parent;

	glm::vec4 * color;

	float distanceFromSun;
	float size;

public:
	float rotationSpeed;
	glm::vec3 * position;

	Planet(Planet * _parent = nullptr, float _distanceFromSun = 3.0f, float _size = 0.5f, glm::vec4 _color = glm::vec4(0), float _rotationSpeed = 0.5f)
	{
		rotationSpeed = _rotationSpeed;
		position = new glm::vec3(1);
		color = new glm::vec4(_color);

		distanceFromSun = _distanceFromSun;
		size = _size;

		SetParent(_parent);
	}

	~Planet()
	{
		delete position;
		delete color;
	}

	void SetParent(Planet * _parent)
	{
		parent = _parent;

		if (parent != nullptr)
		{
			rotationSpeed = (parent->rotationSpeed + 1.0f) * 0.5f;

			distanceFromSun /= (parent->distanceFromSun + 1.0f);
		}
	}

	void Update()
	{
		auto zRotation = cosf((float)glfwGetTime() * rotationSpeed);
		auto xRotation = sinf((float)glfwGetTime() * rotationSpeed);

		auto localPosition = (glm::vec3(distanceFromSun, 0, distanceFromSun) * glm::vec3(xRotation, 0, zRotation));

		if (parent != nullptr)
			*position = *(parent->position) + localPosition;
		else
			*position = localPosition;
	}

	void Draw()
	{
		Gizmos::addSphere(*position, size, 25, 25, *color);
	}
};

