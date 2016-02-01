#include "gl_core_4_4.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "glm/ext.hpp"
#include "Gizmos.h"

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

	while ( (glfwWindowShouldClose(window) == false)
		&& (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS))
	{		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST); // enables the depth buffer

		Gizmos::clear();

		Gizmos::addTransform(glm::mat4(1));

		glm::vec4 white(1);
		glm::vec4 black(0, 0, 0, 1);

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