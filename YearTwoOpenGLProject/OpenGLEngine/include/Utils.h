#pragma once
#define GLM_SWIZZLE_XYZW 
#include "gl_core_4_4.h"
#include "GLFW/glfw3.h"
#include "Application.h"

typedef unsigned int uint;
typedef unsigned char uchar;

#define NAME(type) typeid(type).name()

Application * GetApplication(Application * _application=nullptr)
{
	static Application * application = nullptr;

	if (_application != nullptr)
	{
		application = _application;
	}

	return application;
}
