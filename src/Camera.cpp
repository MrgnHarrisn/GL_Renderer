#include "Camera.h"

glr::Camera::Camera(glm::vec3& position)
{
	transform.position = position;
}

void glr::Camera::setFov(float new_fov)
{
	FOV = new_fov;
}

glm::mat4 glr::Camera::getTransformMatrix()
{
	return transform.getViewMatrix();
}

void glr::Camera::update()
{
	// idk do something i guess?
}
