#pragma once

#include "Transform.h"

namespace glr
{
	class Camera
	{
	public:
		Camera(glm::vec3& position = glm::vec3(0.0f, 0.0f, 3.0f));
		Transform transform;

		float FOV = 90.f;

		/// <summary>
		/// Set FOV of camera
		/// </summary>
		/// <param name="new_fov">new FOV</param>
		void set_fov(float new_fov);
		glm::mat4 get_view_transform();
		void update();
	private:
		
	};
}