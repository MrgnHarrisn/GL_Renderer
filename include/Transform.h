#pragma once
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

namespace glr
{
    class Transform
    {
    public:
        glm::vec3 position      = glm::vec3(0.0f);
        glm::quat orientation   = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);

        // Direction vectors
        glm::vec3 forward       = glm::vec3(0.0f, 0.0f, 1.0f);
        glm::vec3 up            = glm::vec3(0.0f, 1.0f, 0.0f);
        glm::vec3 right         = glm::vec3(1.0f, 0.0f, 0.0f);
        glm::vec3 scale         = glm::vec3(1.f, 1.f, 1.f);

        /// <summary>
        /// Look at a specified point
        /// </summary>
        /// <param name="target">Point to look at</param>
        /// <param name="worldUp">Reference up direction (default: Y-up)</param>
        void lookAt(const glm::vec3& target, const glm::vec3& worldUp = glm::vec3(0.0f, 1.0f, 0.0f));

        /// <summary>
        /// Rotate around an axis
        /// </summary>
        /// <param name="axis">Rotation axis (world space)</param>
        /// <param name="angle_radians">Rotation angle in radians</param>
        void rotate(const glm::vec3& axis, float angle_radians);

        /// <summary>
        /// Rotate around a point
        /// </summary>
        /// <param name="point">Center point to rotate around</param>
        /// <param name="axis">Rotation axis (world space)</param>
        /// <param name="angle_radians">Rotation angle in radians</param>
        void rotateAround(const glm::vec3& point, const glm::vec3& axis, float angle_radians);

        /// <summary>
        /// Scale up/down the transform
        /// </summary>
        /// <param name="new_scale">New scale of each axis</param>
        void setScale(glm::vec3& new_scale);

        /// <summary>
        /// Set position in global coordinates
        /// </summary>
        void setPosition(const glm::vec3& new_position);

        /// <summary>
        /// Get transformation matrix
        /// </summary>
        glm::mat4 getMatrix() const;

        /// <summary>
        /// Get view matrix
        /// </summary>
        /// <returns></returns>
        glm::mat4 getViewMatrix() const;

    private:
        /// <summary>
        /// Update direction vectors from quaternion orientation
        /// </summary>
        void update_vectors();
    };
}