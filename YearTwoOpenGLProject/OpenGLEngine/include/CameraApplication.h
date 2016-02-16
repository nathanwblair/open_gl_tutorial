#pragma once
#include "Cameras/FlyCamera.h"
#include "Application.h"

class CameraApplication :
	public Application
{
private:
	FlyCamera * flyCamera;

	float prevTime;
public:
	float deltaTime;

	CameraApplication()
	{

	}
	~CameraApplication()
	{

	}


	virtual bool Startup()
	{
		prevTime = 0.0f;
		deltaTime = 0.0f;

		flyCamera = new FlyCamera(window);

		flyCamera->SetLookAt(glm::vec3(10, 10, 10), glm::vec3(0));
		flyCamera->SetPerspective(glm::pi<float>() * 0.25f, 16 / 9.0f, 0.1f, 1000.0f);
		flyCamera->SetSpeed(10.0f);

		return true;
	}

	virtual bool Update()
	{
		auto currTime = (float)glfwGetTime();
		deltaTime = currTime - prevTime;
		prevTime = currTime;

		flyCamera->Update(deltaTime);

		return true;
	}

	void BaseDraw()
	{
		Draw();
		Gizmos::draw(flyCamera->GetProjectionView());
	}
};

