#pragma once
#include "GLFW/glfw3.h"
#include "Camera.h"

class FlyCamera : public Camera
{
	float speed;
	glm::vec3 up;

	GLFWwindow * window;

	glm::vec2 prevMousePosition;

public:
	FlyCamera(GLFWwindow * window=nullptr);
	~FlyCamera();

	void Update(float deltaTime);
	void UpdateRotation(float deltaTime);
	void UpdatePosition(float deltaTime);

	void SetSpeed(float speed);
};

