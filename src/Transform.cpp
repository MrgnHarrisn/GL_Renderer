#include "Transform.h"

void glr::Transform::look_at(const glm::vec3& target, const glm::vec3& worldUp)
{
    const glm::vec3 toTarget = glm::normalize(target - position);

    // Handle degenerate cases (looking straight up/down)
    if (glm::length(toTarget) < 0.0001f) return;

    // Calculate new orthonormal basis
    const glm::vec3 newRight = glm::normalize(glm::cross(worldUp, toTarget));
    const glm::vec3 newUp = glm::normalize(glm::cross(toTarget, newRight));

    // Construct rotation matrix from basis vectors
    const glm::mat3 rotationMatrix = glm::mat3(newRight, newUp, toTarget);

    // Convert to quaternion and update orientation
    orientation = glm::quat_cast(rotationMatrix);
    update_vectors();
}

void glr::Transform::rotate(const glm::vec3& axis, float angle_radians)
{
    const glm::quat rotation = glm::angleAxis(angle_radians, axis);
    orientation = rotation * orientation; // Global space rotation
    update_vectors();
}

void glr::Transform::rotate_around(const glm::vec3& point, const glm::vec3& axis, float angle_radians)
{
    // Calculate direction vector from center to position
    glm::vec3 toPosition = position - point;

    // Create rotation quaternion
    const glm::quat rotation = glm::angleAxis(angle_radians, axis);

    // Rotate direction vector and update position
    toPosition = rotation * toPosition;
    position = point + toPosition;

    // Apply rotation to orientation
    orientation = rotation * orientation;
    update_vectors();
}

void glr::Transform::set_position(const glm::vec3& new_position)
{
    position = new_position;
}

glm::mat4 glr::Transform::get_matrix() const
{
    glm::mat4 translation = glm::translate(glm::mat4(1.0f), position);
    glm::mat4 rotation = glm::mat4_cast(orientation);
    return translation * rotation;
}

glm::mat4 glr::Transform::get_view_matrix() const
{
    return glm::lookAt(position, position + forward, up);
}

void glr::Transform::update_vectors()
{
    const glm::mat3 rotationMatrix = glm::mat3_cast(orientation);
    forward = rotationMatrix * glm::vec3(0.0f, 0.0f, 1.0f);
    up = rotationMatrix * glm::vec3(0.0f, 1.0f, 0.0f);
    right = rotationMatrix * glm::vec3(1.0f, 0.0f, 0.0f);
}

