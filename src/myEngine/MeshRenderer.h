#include "Component.h"
#include "Mesh.h"
#include "Material.h"

#include <string>

namespace myengine
{
	class MeshRenderer : public Component
	{
	public:
		//Default Component functions
		void Initialise(std::string _meshPath, std::string _texturePath, std::string _vertShaderPath, std::string _fragShaderPath);
		void Initialise();
		void Start();
		void Update();
		void Draw();

		void SetModel(std::string path);
		void SetMaterial(std::string path);
		void SetShaders(std::string vertPath, std::string fragPath);

		void SetModel(std::shared_ptr<Mesh> mod) { _mesh = mod; }
		void SetMaterial(std::shared_ptr<Material> matt) { _texture = matt; }

		//Sets and Adjusts
		void SetPosition(float posX, float posY, float posZ) { _position.x = posX; _position.y = posY; _position.z = posZ; }
		void SetPosition(glm::vec3 value) { _position = value; }
		void AdjustPosition(float posX, float posY, float posZ) { _position.x += posX; _position.y += posY; _position.z += posZ; }
		void AdjustPosition(glm::vec3 adjustment) { _position += adjustment; /*_position.x += adjustment.x; _position.y += adjustment.y; _position.z += adjustment.z;*/ }
		void SetRotation(float rotX, float rotY, float rotZ) { _rotation.x = rotX; _rotation.y = rotY; _rotation.z = rotZ; }
		void SetScale(float scaleX, float scaleY, float scaleZ) { _scale.x = scaleX, _scale.y = scaleY, _scale.z = scaleZ; }
		void SetScale(glm::vec3 value) { _scale = value; }
		void SetDraw(bool b) { draw = b; }

		//Gets
		glm::vec3 GetPosition() { return _position; }
		glm::vec3 GetRotation() { return _rotation; }
		glm::vec3 GetScale() { return _scale; }

		glm::vec3 GetBoundingBoxMax() { return (_mesh->GetBoundingBoxMax() * _scale); }
		glm::vec3 GetBoundingBoxMin() { return (_mesh->GetBoundingBoxMin() * _scale); }

		std::shared_ptr<Mesh> getMesh() { return _mesh; }
		std::shared_ptr<Material> getMaterial() { return _texture; }

	private:
		//Pointers to this objects associated mesh and texture objects
		std::shared_ptr<Mesh> _mesh;
		std::shared_ptr<Material> _texture;

		// Matrix for the position and orientation of the game object
		glm::mat4 _modelMatrix;
		glm::mat4 _invModelMatrix;

		//Vec3s for pos, rot and scale of object
		glm::vec3 _position;
		glm::vec3 _rotation;
		glm::vec3 _scale;

		//bool determines whether mesh is draw or not
		bool draw;
	};

	
}