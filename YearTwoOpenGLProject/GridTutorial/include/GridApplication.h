#pragma once
#include "CameraApplication.h"
#include "Planet.h"
#include "dynamic_enum\DynamicEnum.h"
#include "merge_structs\Merger.h"

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

void TestMergeStruct()
{
	struct MeshVertex
	{
		float a;
		float b;
	};

	struct CableVertex
	{
		float c;
		float d;
	};

	auto merger = Merge<MeshVertex, CableVertex>(MeshVertex(), CableVertex()).result;
}

void TestEnum()
{
	DynamicEnum dynamicEnum = DynamicEnum();

	auto a = dynamicEnum.Find("test");
	assert(a == -1);

	dynamicEnum.Add("Size");
	dynamicEnum.Add("Position");
	dynamicEnum.Add("Weight");
	dynamicEnum.Add("Color");

	a = dynamicEnum.Get("Color");
	assert(a == 3);

	dynamicEnum.Set("Colour", dynamicEnum.Get("Color"));
	a = dynamicEnum.Get("Colour");
	assert(a == 3);

	a = dynamicEnum.Get("test");
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
		TestPlanet();
		TestMergeStruct();
	}

	bool Update()
	{
		return CameraApplication::Update();
	}

};