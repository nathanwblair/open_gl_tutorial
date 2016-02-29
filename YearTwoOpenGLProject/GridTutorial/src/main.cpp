#include "GridApplication.h"
#include "Utils.h"
#include "Rendering/RenderData.h"
#include "Assets/Mesh.h"
#include <string>

void TestPlanet();


int main()
{
	Application * application = new GridApplication();

	GetApplication(application)->Run();
}

