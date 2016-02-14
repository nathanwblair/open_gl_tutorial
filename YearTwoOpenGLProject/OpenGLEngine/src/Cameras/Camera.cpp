#include <iostream>
#include "Cameras/Camera.h"

void Camera::UpdateProjectionViewTransform()
{
	projectionViewTransform = projectionTransform * viewTransform;
}


void Camera::SetPerspective(float FOV, float aspectRatio, float _near, float _far)
{
	projectionTransform = glm::perspective(FOV, aspectRatio, _near, _far);

	UpdateProjectionViewTransform();
}


void Camera::SetLookAt(glm::vec3 from, glm::vec3 to)
{
	viewTransform = glm::lookAt(from, to, glm::vec3(0, 1, 0));

	worldTransform = glm::inverse(viewTransform);

	UpdateProjectionViewTransform();
}


void Camera::SetPosition(glm::vec3 position)
{
	worldTransform = glm::translate(worldTransform, position);
	viewTransform = glm::inverse(worldTransform);

	UpdateProjectionViewTransform();
}


void Camera::SetRotation(glm::vec3 axis, float speed)
{
	worldTransform = glm::rotate(worldTransform, speed, axis);
	viewTransform = glm::inverse(worldTransform);

	UpdateProjectionViewTransform();
}


glm::mat4& Camera::GetWorldTransform()
{
	return worldTransform;
}


glm::mat4& Camera::GetView()
{
	return viewTransform;
}


glm::mat4& Camera::GetProjection()
{
	return projectionTransform;
}


glm::mat4& Camera::GetProjectionView()
{
	return projectionViewTransform;
}