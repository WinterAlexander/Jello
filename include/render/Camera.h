//
// Created by Alexander Winter on 2023-01-18.
//

#ifndef JELLO_CAMERA_H
#define JELLO_CAMERA_H

#include <glm/vec3.hpp>
#include <glm/fwd.hpp>

namespace jello {
	class Camera;
}

/**
 * A camera object which looks into a 3D scene
 */
class jello::Camera {
private:
	glm::vec3 position;
	glm::vec3 direction;
	glm::vec3 up;

public:
	Camera();

	glm::vec3& getPosition();

	/**
	 * @return current position of the camera
	 */
	glm::vec3 getPosition() const;

	glm::vec3& getDirection();

	/**
	 * @return direction the camera is currently looking in
	 */
	glm::vec3 getDirection() const;

	glm::vec3& getUp();

	/**
	 * @return vector pointing directly above the camera
	 */
	glm::vec3 getUp() const;

	/**
	 * @return transform view matrice for the view of the camera
	 */
	glm::mat4 getView() const;
};


#endif //JELLO_CAMERA_H
