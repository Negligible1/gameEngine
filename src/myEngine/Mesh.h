/// \file Mesh.h
/// \brief Contains mesh information
/// \author Leigh McLoughlin
/// \todo nothing for now

#ifndef __MESH__
#define __MESH__

//File includes
#include "Component.h"
#include <GLM/glm.hpp>
#include <GL/glew.h>
#include <string>

namespace myengine
{
	// For loading a mesh from OBJ file and keeping a reference for it
	class Mesh
	{
	public:
		Mesh(std::string path);
		~Mesh();

		// OBJ file must be triangulated
		void LoadOBJ(std::string filename);

		// Draws the mesh - must have shaders applied for this to display!
		void Draw();

		glm::vec3 GetBoundingBoxMax() { return _boundingBoxMax; }
		glm::vec3 GetBoundingBoxMin() { return _boundingBoxMin; }

	protected:

		// OpenGL Vertex Array Object
		GLuint _VAO;

		// Number of vertices in the mesh
		unsigned int _numVertices;

		//Bounding box variables
		glm::vec3 _boundingBoxMax;
		glm::vec3 _boundingBoxMin;


	};
}


#endif
