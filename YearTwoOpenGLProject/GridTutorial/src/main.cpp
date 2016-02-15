#include "GridApplication.h"
#include "Utils.h"

void TestPlanet();


int main()
{
	Application * application = new GridApplication();

	GetApplication(application)->Run();
}

