#pragma once
#define GLM_SWIZZLE_XYZW 
#include "gl_core_4_4.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "glm/trigonometric.hpp"
#include "glm/gtx/quaternion.hpp"
#include "glm/ext.hpp"
#include "Gizmos.h"

using glm::vec4;
using glm::vec3;
using glm::mat4;

typedef unsigned int uint;

struct Vertex {
	glm::vec4 position;
	glm::vec4 color;
};

class Grid
{
	Grid()
	{

	}

	void GenerateGrid(uint rows, uint columns)
	{
		Vertex * AOVerticies = new Vertex[rows * columns];

		for (uint row = 0; row < rows; row++)
		{
			for (uint column = 0; column < columns; columns++)
			{

				auto newPosition = vec4((float)column, 0, (float)row, 1);
				auto newColor = vec3(
									sinf( 
										(column / (float)(columns - 1)) 
										* ( row / (float)(rows - 1))));

				auto index = row * columns + column;

				AOVerticies[index].position = newPosition;
				AOVerticies[index].color = vec4(newColor, 1);
			}
		}

		glGenBuffers(1, &m_VBO);


		delete[] AOVerticies;
	}

	void Draw()
	{

	}
};