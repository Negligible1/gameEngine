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
	void MeshRenderer::Initialise(std::string _meshPath, std::string _texturePath, std::string _vertShaderPath, std::string _fragShaderPath)
	{
		_texture = std::make_shared<Material>();
		_texture->LoadShaders(_vertShaderPath, _fragShaderPath);
		_texture->SetDiffuseColour(glm::vec3(0.5, 0.5, 0.5));
		_texture->SetTexture(_texturePath);
		_texture->SetLightPosition(glm::vec3(10, 10, 0));

		_mesh = std::make_shared<Mesh>();
		_mesh->LoadOBJ(_meshPath);

		_position = glm::vec3(0.0f, 0.0f, 0.0f);
		_scale = glm::vec3(1.0f, 1.0f, 1.0f);
	}

	void MeshRenderer::Initialise()
	{
		_mesh = std::make_shared<Mesh>();
		_texture = std::make_shared<Material>();

		_position = glm::vec3(0.0f, 0.0f, 0.0f);
		_scale = glm::vec3(1.0f, 1.0f, 1.0f);
	}

	void MeshRenderer::Start()
	{

	}

	void MeshRenderer::Update()
	{
		_modelMatrix = glm::rotate(_modelMatrix, _rotation.y, glm::vec3(0, 1, 0));
		_invModelMatrix = glm::rotate(glm::mat4(1.0f), -_rotation.y, glm::vec3(0, 1, 0));
		_modelMatrix = glm::translate(glm::mat4(1.0f), _position);
		_modelMatrix = glm::scale(_modelMatrix, _scale);
	}

	void MeshRenderer::Draw()
	{
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


	void MeshRenderer::SetModel(std::string path)
	{
		_mesh->LoadOBJ(path);
	}

	void MeshRenderer::SetMaterial(std::string path)
	{
		_texture->SetTexture(path);
		_texture->SetLightPosition(glm::vec3(10, 10, 0));
		_texture->SetDiffuseColour(glm::vec3(0.5, 0.5, 0.5));
	}

	void MeshRenderer::SetShaders(std::string vertPath, std::string fragPath)
	{
		_texture->LoadShaders(vertPath, fragPath);
	}
}