#include "Application.h"
#include "FBXFile.h"

bool Application::BaseStartup() 
{
	if (glfwInit() == false)
		return false;

	window = glfwCreateWindow(1280, 720,
	                          "Computer Graphics",
	                          nullptr, nullptr);

	if (window == nullptr)
	{
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(window);

	if (ogl_LoadFunctions() == ogl_LOAD_FAILED)
	{
		glfwDestroyWindow(window);
		glfwTerminate();
		return false;
	}

	Gizmos::create();

	glClearColor(0.25f, 0.25f, 0.25f, 1);

	return Startup();
}

bool Application::BaseUpdate()
{
	auto isEscapeKeyPressed = (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS);

	auto canWindowClose = glfwWindowShouldClose(window);

	if (isEscapeKeyPressed && canWindowClose)
	{
		return false;
	}
	else
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST); // enables the depth buffer

		Gizmos::clear();
		auto result = Update();
		BaseDraw();

		glfwSwapBuffers(window);
		glfwPollEvents();

		return result;
	}
}

void  Application::BaseDraw()
{
	Draw();
}

void Application::Shutdown() 
{
	Gizmos::destroy();

	if (window)
	{
		glfwDestroyWindow(window);
		window = nullptr;
	}

	glfwTerminate();
}

void Application::Run() {
	if (!BaseStartup())
	{
		return;
	}

	while (BaseUpdate())
	{
		//Update
	}
}