#pragma once
#include "CameraApplication.h"
#include "Planet.h"

class Grid;

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

class GridApplication
	: public CameraApplication
{
private:
	uint programID;
	Grid * grid;

public:
	void Draw()
	{
		//grid->Draw();
		TestPlanet();
	}

	bool Update()
	{
		return CameraApplication::Update();
	}

};