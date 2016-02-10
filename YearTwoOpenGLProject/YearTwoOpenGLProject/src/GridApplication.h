#pragma once
#include "CameraApplication.h"

class Grid;

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
	}

	bool Update()
	{
		return true;
	}

};