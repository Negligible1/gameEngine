#include "Component.h"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLM/gtc/quaternion.hpp>

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
		
		void cameraSetPosition(glm::vec3 pos) { viewMatrix = glm::translate(glm::mat4(1.0f), pos); }
		
		void cameraSetRotation(float x, float y) { viewMatrix = glm::rotate(viewMatrix, x, glm::vec3(1, 0, 0));
		viewMatrix = glm::rotate(viewMatrix, y, glm::vec3(0, 1, 0)); }
		
		


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