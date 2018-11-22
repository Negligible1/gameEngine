#include "Component.h"
#include <GL/glew.h>
#include <vector>

namespace myengine
{
	class Triangle : public Component
	{
	public:
		void Draw();
		void Initialise();
		
	private:
		void SetPositions(); //maybe change to "load model"(?)
		void VAOShit();
		void Shader();

		GLuint programId; //shader
		GLuint vaoId; //VAO
		std::vector<GLfloat> positions;
		

	};
}