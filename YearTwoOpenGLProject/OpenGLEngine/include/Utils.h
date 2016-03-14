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

Application * GetApplication(Application * _application=nullptr)
{
	static Application * application = nullptr;

	if (_application != nullptr)
	{
		application = _application;
	}

	return application;
}

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

	static uint SizeOf(Primitive primitiveType)
	{
		switch (primitiveType)
		{
		case GL::Primitive::Double:
			return sizeof(double);
			break;
		case GL::Primitive::Float:
			return sizeof(float);
			break;
		case GL::Primitive::Int:
			return sizeof(int);
			break;
		case GL::Primitive::UInt:
			return sizeof(uint);
			break;
		case GL::Primitive::Short:
			return sizeof(short);
			break;
		case GL::Primitive::Byte:
			return sizeof(char);
			break;
		case GL::Primitive::UByte:
			return sizeof(uchar);
			break;
		default:
			return 0;
			break;
		}
	}
};
