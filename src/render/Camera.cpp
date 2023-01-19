//
// Created by Alexander Winter on 2023-01-18.
//

#include <glm/ext/matrix_transform.hpp>
#include "render/Camera.h"

using namespace jello;

Camera::Camera() : position(0.0, 0.0, 0.0),
				   direction(0.0, 0.0, 1.0),
				   up(0.0, 1.0, 0.0) {

}

void Camera::setDirectionFromAngles(float yaw, float pitch) {
	direction.x = static_cast<float>(cos(glm::radians(yaw)) * cos(glm::radians(pitch)));
	direction.y = static_cast<float>(sin(glm::radians(pitch)));
	direction.z = static_cast<float>(sin(glm::radians(yaw)) * cos(glm::radians(pitch)));
	direction = glm::normalize(direction);
}

glm::vec3& Camera::getPosition() {
	return position;
}

glm::vec3 Camera::getPosition() const {
	return position;
}

glm::vec3& Camera::getDirection() {
	return direction;
}

glm::vec3 Camera::getDirection() const {
	return direction;
}

glm::vec3& Camera::getUp() {
	return up;
}

glm::vec3 Camera::getUp() const {
	return up;
}

glm::mat4 Camera::getView() const {
	return glm::lookAt(position,
	                   position + direction,
	                   up);
}

float Camera::getFieldOfView() const {
	return fieldOfView;
}

void Camera::setFieldOfView(float fieldOfView) {
	this->fieldOfView = fieldOfView;
}
