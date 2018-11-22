#include "MeshRenderer.h"
#include "Core.h"
#include "Camera.h"

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <memory>

//temp include
#include <iostream>

namespace myengine
{
	void MeshRenderer::Initialise(std::string _meshPath, std::string _texturePath)
	{
		_mesh = std::make_shared<Mesh>(_meshPath);
		_texture = std::make_shared<Material>(_texturePath);

		_position = glm::vec3(0.0f, 0.0f, 0.0f);
		_rotation = glm::vec3(0.0f, 0.0f, 0.0f);
		_scale = glm::vec3(1.0f, 1.0f, 1.0f);
	}

	void MeshRenderer::Start()
	{

	}

	void MeshRenderer::Update()
	{
		//_rotation += glm::vec3(0.0f, 0.1f, 0.0f);

		_modelMatrix = glm::rotate(_modelMatrix, _rotation.y, glm::vec3(0, 1, 0));
		_invModelMatrix = glm::rotate(glm::mat4(1.0f), -_rotation.y, glm::vec3(0, 1, 0));
		_modelMatrix = glm::translate(glm::mat4(1.0f), _position);
		_modelMatrix = glm::scale(_modelMatrix, _scale);
	}

	void MeshRenderer::Draw()
	{
		//getcore cmaera instead?
		glm::mat4 pMat = getCore()->getCamera()->getProjMtrx();
		glm::mat4 vMat = getCore()->getCamera()->getViewMatrx();

		if (_mesh != NULL)
		{
			if (_texture != NULL)
			{
				// Give all the matrices to the material
				// This makes sure they are sent to the shader
				_texture->SetMatrices(_modelMatrix, _invModelMatrix, vMat, pMat);
				// This activates the shader
				_texture->Apply();
			}

			// Sends the mesh data down the pipeline
			_mesh->Draw();

		}
	}
}