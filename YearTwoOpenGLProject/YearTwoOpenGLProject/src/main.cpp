#define GLM_SWIZZLE_XYZW 

#include "gl_core_4_4.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "glm/trigonometric.hpp"
#include "glm/gtx/quaternion.hpp"
#include "glm/ext.hpp"
#include "Gizmos.h"
#include "FlyCamera.h"

#include "Planet.h"

void TestPlanet();

FlyCamera * GetCamera(GLFWwindow * window = nullptr);

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

	float prevTime = 0.0f;
	float currTime = NULL;
	float deltaTime = NULL;

	glClearColor(0.25f, 0.25f, 0.25f, 1);

	GetCamera(window)->SetSpeed(10.0f);

	while ( (glfwWindowShouldClose(window) == false)
		&& (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST); // enables the depth buffer

		Gizmos::clear();

		currTime = glfwGetTime();
		deltaTime = currTime - prevTime;
		prevTime = currTime;

		TestPlanet();
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


			//Gizmos::addSphere(glm::vec3(0), 2.0f, 10, 10, yellow);

			
		}

		GetCamera()->Update(deltaTime);
		Gizmos::draw(GetCamera()->GetProjectionView());
		
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	Gizmos::destroy();

	

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}


void TestPlanet()
{
	glm::vec4 yellow(255.0f, 255.0f, 0, 1);

	static Planet * sun = new Planet(nullptr, 0.0f, 2, yellow, 0);
	static Planet * planet = new Planet(sun, 5);
	static Planet * planet2 = new Planet(planet, 10.0f);

	sun->Update();
	sun->Draw();
	planet->Update();
	planet->Draw();
	planet2->Update();
	planet2->Draw();
}


FlyCamera * GetCamera(GLFWwindow * window)
{
	static FlyCamera * flyCamera = nullptr;

	if (flyCamera == nullptr)
	{
		flyCamera = new FlyCamera(window);

		flyCamera->SetLookAt(glm::vec3(10, 10, 10), glm::vec3(0));
		flyCamera->SetPerspective(glm::pi<float>() * 0.25f, 16 / 9.0f, 0.1f, 1000.0f);
	}

	return flyCamera;
}