#include "Camera.h"

namespace myengine
{
	void Camera::Initialise()
	{
		//Float value to be used to adjust the angle of the camera
		camAngleX = 0.0f;
		camAngleY = 0.0f;
		position = glm::vec3(0, 0, -10.0f);

		// Set up the viewing matrix
		// This represents the camera's orientation and position
		viewMatrix = glm::translate(glm::mat4(1.0f), position);

		// Set up a projection matrix
		projectionMatrix = glm::perspective(45.0f, 1.0f, 0.1f, 10000.0f);
	}

	void Camera::Start()
	{

	}

	void Camera::Update()
	{

		viewMatrix = glm::translate(glm::mat4(1.0f), position);
		viewMatrix = glm::rotate(viewMatrix, camAngleX, glm::vec3(1, 0, 0));
		viewMatrix = glm::rotate(viewMatrix, camAngleY, glm::vec3(0, 1, 0));
	}

	void Camera::Draw()
	{

	}

}