#pragma once
#include "CameraApplication.h"

#include "Grid.h"

class GridApplication
	: public CameraApplication
{
private:
	Grid * grid;

public:
	void Draw()
	{
		grid->Draw();
	}

};