#pragma once
#include "CameraApplication.h"
#include "Planet.h"
#include "dynamic_enum\DynamicEnum.h"
#include "merge_structs\Merger.h"
#include "Assets/FBXMesh.h"

#include "Assets\GridMesh.h"

//#include "imgui.h"
//#include "imgui_impl_glfw_gl3.h"

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

	auto index = dynamicEnum.First("Size");
	assert(index == 0);

	dynamicEnum.Add("NormalTexture");
	dynamicEnum.Add("AlphaTexture");
	index = dynamicEnum.First("NormalTexture");
	assert(index == 4);

	index = dynamicEnum.LocalFind("Texture", "Normal");
	assert(index == 0);

	dynamicEnum.LocalGet("Texture", "Normal");
}


void TestRenderer()
{

}


class GridApplication
	: public CameraApplication
{
private:
	uint programID;
	GridMesh * grid;

	FBXMesh * mesh;

public:
	virtual bool Startup()
	{
//		ImGui_ImplGlfwGL3_Init(window, true);
		mesh = new FBXMesh("models/soulspear/soulspear.fbx");

		grid = new GridMesh("textures/cliff.tga");

		grid->Load();
		mesh->Load();

		return CameraApplication::Startup();
	}

	void Draw()
	{
		auto lightTransform = Transform();

		if (grid->boundingSphere.IsTouchingFrustumPlanes(mat4(1), vec3(0)))
			grid->Render(*flyCamera, lightTransform, lightTransform, true);
		if (mesh->boundingSphere.IsTouchingFrustumPlanes(mat4(1), vec3(0)))
			mesh->Render(*flyCamera, lightTransform, lightTransform, true);

		//ImVec4 clear_color = ImColor(114, 144, 154);

		//ImGui_ImplGlfwGL3_NewFrame();

		// Imgui test
		{
			// static float f = 0.0f;
			// ImGui::Text("Testing...");
		}

	}

	bool Update()
	{
		grid->Update(deltaTime);
		mesh->Update(deltaTime);

		return CameraApplication::Update();
	}

};