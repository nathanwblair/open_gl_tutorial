#include "Cameras/FlyCamera.h"

#include "GLFW/glfw3.h"


FlyCamera::FlyCamera(GLFWwindow * _window)
{
	window = _window;
}


FlyCamera::~FlyCamera()
{
}


void FlyCamera::Update(float deltaTime)
{
	UpdateRotation(deltaTime);
	UpdatePosition(deltaTime);
}


void FlyCamera::UpdateRotation(float deltaTime)
{
	double mouseX;
	double mouseY;

	glfwGetCursorPos(window, &mouseX, &mouseY);
	glm::vec2 mousePosition(mouseX, mouseY);

	auto deltaMouse = mousePosition - prevMousePosition;

	SetRotation(glm::vec3(0, 1, 0), (float)(deltaMouse.x * 0.001f));
	SetRotation(glm::vec3(1, 0, 0), (float)(deltaMouse.y * 0.001f));
	
	prevMousePosition = mousePosition;
}


void FlyCamera::UpdatePosition(float deltaTime)
{
	auto w = glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS;
	auto a = glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS;
	auto s = glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS;
	auto d = glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS;

	auto translateVector = glm::vec3(0);

	if (w)
	{
		translateVector.z -= speed * deltaTime;
	}
	if (a)
	{
		translateVector.x -= speed * deltaTime;
	}
	if (s)
	{
		translateVector.z += speed * deltaTime;
	}
	if (d)
	{
		translateVector.x += speed * deltaTime;
	}

	SetPosition(translateVector);
}


void FlyCamera::SetSpeed(float _speed)
{
	speed = _speed;
}