#pragma once
#include <vector>
#include <queue>
#include "gl_core_4_4.h"
#include "GLFW/glfw3.h"
#include "Gizmos.h"
#include "Assets/Shader.h"

typedef unsigned int uint;

class Application
{
public:
	uint VAO;
	uint VBO;
	uint IBO;

	GLFWwindow * window;

	virtual bool Startup() = 0;
	virtual bool Update() = 0;
	virtual void Draw() = 0;

	bool BaseStartup();

	virtual bool BaseUpdate();

	virtual void BaseDraw();

	void Shutdown();

	void Run();
};