#include "Camera.h"

glr::Camera::Camera(glm::vec3& position)
{
	transform.position = position;
}

void glr::Camera::set_fov(float new_fov)
{
	FOV = new_fov;
}

glm::mat4 glr::Camera::get_view_transform()
{
	return transform.get_view_matrix();
}

void glr::Camera::update()
{
	// idk do something i guess?
}
