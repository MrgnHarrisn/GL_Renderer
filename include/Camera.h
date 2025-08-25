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
		void setFov(float new_fov);

		/// <summary>
		/// Get's the transform matrix
		/// </summary>
		/// <returns></returns>
		glm::mat4 getTransformMatrix();

		/// <summary>
		/// 
		/// </summary>
		void update();
	private:
		
	};
}