#include "Component.h"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLM/gtc/quaternion.hpp>

#ifndef MYENGINE_CAMERA_H
#define MYENGINE_CAMERA_H

namespace myengine
{
	class Camera : public Component
	{
		public:
		void Initialise(); //Obtain or create proj and view matrix here(?)
		void Start();
		void Update(); 
		void Draw(); //Don't need this(?)


		glm::mat4 getProjMtrx() { return projectionMatrix; }
		glm::mat4 getViewMatrx() { return viewMatrix; }
		
		void cameraSetPosition(glm::vec3 pos) { position = pos; }
		void cameraSetPosition(float x, float y, float z) { position.x = x; position.y = y; position.z = z; }
		void cameraAdjustPosition(float x, float y, float z) { position.x += x; position.y += y; position.z += z; }
		void cameraAdjustPosition(glm::vec3 adjustment) { position += adjustment; }
		
		void cameraSetRotation(float x, float y) { camAngleX = x; camAngleY = y; }

		
		


		//Functions to attach camera to another Component and to perform all transform/rotate operations on the camera as well(?)
		//Maybe add this functionality to Component class instead of too the Camera due to issues with template <typename T>

		private:
		glm::mat4 projectionMatrix;
		glm::mat4 viewMatrix;
		glm::quat camOrientation;
		glm::vec3 position;
		float camAngleX;
		float camAngleY;
	};
}

#endif // !MYENGINE_CAMERA_H