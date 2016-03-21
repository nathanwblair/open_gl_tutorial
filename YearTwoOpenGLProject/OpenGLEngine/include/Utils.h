#pragma once
#define GLM_SWIZZLE_XYZW 
#include "gl_core_4_4.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "glm/trigonometric.hpp"
#include "glm/gtx/quaternion.hpp"
#include "glm/ext.hpp"
#include <vector>
#include <string>

class Application;

using std::string;
using std::vector;

typedef unsigned int uint;
typedef unsigned char uchar;

#define NAME(type) typeid(type).name()

Application * GetApplication(Application * _application=nullptr);

struct GL
{
	enum class Primitive
	{
		Double = GL_DOUBLE,
		Float = GL_FLOAT,
		Int = GL_INT,
		UInt = GL_UNSIGNED_INT,
		Short = GL_SHORT,
		Byte = GL_BYTE,
		UByte = GL_UNSIGNED_BYTE
	};

	static uint SizeOf(Primitive primitiveType);
};
