#include "GridApplication.h"
#include "Utils.h"
#include <string>

void TestPlanet();


int main()
{
	Application * application = new GridApplication();

	GetApplication(application)->Run();
}

