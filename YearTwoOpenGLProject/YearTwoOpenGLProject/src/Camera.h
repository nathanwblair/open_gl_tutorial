#pragma once

#include "glm/glm.hpp"
#include "glm/ext.hpp"

class Camera
{
	glm::mat4 worldTransform;
	glm::mat4 viewTransform;

	glm::mat4 projectionTransform;
	glm::mat4 projectionViewTransform;

	void UpdateProjectionViewTransform();

public:
	virtual void Update(float deltaTime) = NULL;

	void SetPerspective(float FOV, float aspectRatio, float _near, float _far);

	void SetLookAt(glm::vec3 from, glm::vec3 to);

	void SetPosition(glm::vec3 position);

	void SetRotation(glm::vec3 axis, float speed);
	
	glm::mat4& GetWorldTransform();
			 
	glm::mat4& GetView();
			 
	glm::mat4& GetProjection();
			 
	glm::mat4& GetProjectionView();
};

