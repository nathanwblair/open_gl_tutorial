#pragma once
#include "Utils.h"
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
public:
	Grid()
	{
		
	}

	void GenerateGrid(uint rows, uint columns)
	{
		Vertex * AO_Verticies = new Vertex[rows * columns];

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

				AO_Verticies[index].position = newPosition;
				AO_Verticies[index].color = vec4(newColor, 1);
			}
		}

		auto AUI_Indicies = new uint[(rows - 1) * (columns - 1) * 6];

		uint index = 0;
		for (uint row = 0; row < rows; row++)
		{
			for (uint column = 0; column < columns; columns++)
			{
				// Triangle 1
				AUI_Indicies[index++] = row * columns + column;
				AUI_Indicies[index++] = (row + 1) * columns + column;
				AUI_Indicies[index++] = (row + 1) * columns + (column + 1);

				// Triangle 2
				AUI_Indicies[index++] = row * columns + column;
				AUI_Indicies[index++] = (row + 1) * columns + (column + 1);
				AUI_Indicies[index++] = row * columns + (column + 1);
			}
		}


		auto application = (GridApplication*)GetApplication();

		// Generate VBO & IBO
		glGenBuffers(1, &(application->VBO));
		glGenBuffers(1, &application->IBO);

		glGenVertexArrays(1, &application->VAO);

		glBindBuffer(GL_ARRAY_BUFFER, application->VBO);
		glBufferData(GL_ARRAY_BUFFER, (rows * columns) * sizeof(Vertex), AO_Verticies, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);

		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(vec4)));

		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, application->IBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, (rows - 1) * (columns - 1) * 6 * sizeof(uint), AUI_Indicies, GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	   

		delete[] AO_Verticies;
	}

	void Draw()
	{

	}
};