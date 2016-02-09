#include "CameraApplication.h"

void TestPlanet();


int main()
{
	Application * application = new CameraApplication();
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