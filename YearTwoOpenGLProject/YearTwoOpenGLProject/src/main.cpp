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
	glm::mat4 * transform;
	glm::vec4 * color;
	float distanceFromSun;
	float size;
	float deltaRotation;

public:

	Planet(glm::vec3 _position=glm::vec3(0), glm::vec4 _color=glm::vec4(0), float _distanceFromSun = 3.0f, float _size = 0.5f, float _deltaRotation = 0.01f)
	{
		position = new glm::vec3(_position);
		color = new glm::vec4(_color);

		distanceFromSun = _distanceFromSun;
		size = _size;
		deltaRotation = _deltaRotation;
	}

	~Planet()
	{
		delete position;
		delete color;
	}

	void Draw()
	{
		*position = glm::rotate(*position, deltaRotation, glm::vec3(0));

		Gizmos::addSphere(*position, size, 25, 25, *color);
	}
};

int main()
{
	if (glfwInit() == false)
		return -1;

	GLFWwindow * window = glfwCreateWindow(1280, 720,
		"Computer Graphics",
		nullptr, nullptr);

	if (window == nullptr)
	{
		glfwTerminate();
		return -2;
	}

	glfwMakeContextCurrent(window);

	if (ogl_LoadFunctions() == ogl_LOAD_FAILED) 
	{
		glfwDestroyWindow(window);
		glfwTerminate();
		return -3;
	}

	Gizmos::create();

	auto view = glm::lookAt(glm::vec3(10, 10, 10), glm::vec3(0), glm::vec3(0, 1, 0));
	auto projection = glm::perspective(glm::pi<float>() * 0.25f,
		16.0f / 9.0f, 0.1f, 1000.0f);

	glClearColor(0.25f, 0.25f, 0.25f, 1);

	auto earth = new Planet();

	while ( (glfwWindowShouldClose(window) == false)
		&& (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST); // enables the depth buffer

		Gizmos::clear();

		Gizmos::addTransform(glm::mat4(1));

		glm::vec4 white(1);
		glm::vec4 black(0, 0, 0, 1);
		glm::vec4 yellow(255.0f, 255.0f, 0, 1);

		auto planetRotationPerFrame = 0.01f;

		auto color = black;
		for (int i = 0; i < 21; i++)
		{
			color = black;

			if (i == 10)
			{
				color = white;
			}

			Gizmos::addLine(glm::vec3(i - 10, 0, 10),
				glm::vec3(i - 10, 0, -10),
				color);


			Gizmos::addLine(glm::vec3(10, 0, i - 10),
				glm::vec3(-10, 0, i - 10),
				color);	


			Gizmos::addSphere(glm::vec3(0), 2.0f, 10, 10, yellow);

			
		}

		Gizmos::draw(projection * view);
		
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	Gizmos::destroy();

	

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}