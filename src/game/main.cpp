#include <myEngine/myengine.h>

#include <iostream>
#include <memory>
#include <string>

class TestScreen : public myengine::Component
{
public:
	void TestScreen::Initialise()
	{
		std::cout << "Initialise " << std::endl;
	}

	void TestScreen::Start()
	{
		std::cout << "Start" << std::endl;
	}

	void TestScreen::Update()
	{
		std::cout << "Update" << std::endl;
	}

	void TestScreen::Draw()
	{
		std::cout << "Draw" << std::endl;
	}
};

class Death : public myengine::Component
{
public:
	void Initialise(std::shared_ptr<myengine::MeshRenderer> m, std::shared_ptr<myengine::Sound> s)
	{
		mineM = m;
		mineS = s;
	}

	void Start()
	{
		
	}

	void Update()
	{
		if (getCore()->getKeyboard()->GetShift())
		{
			mineS->play();
		}

		if (getCore()->getKeyboard()->GetW())
		{
			mineM->AdjustPosition(0.1f, 0.0f, 0.0f);
		}
	}

	void Draw()
	{

	}

private:
	std::shared_ptr<myengine::MeshRenderer> mineM;
	std::shared_ptr<myengine::Sound> mineS;
};

int main()
{
	std::shared_ptr<myengine::Core> c = myengine::Core::initialise();
	std::shared_ptr<myengine::Entity> test = c->addEntity();
	//std::shared_ptr<TestScreen> testEnt = test->addComponent<TestScreen>();
	//std::shared_ptr<myengine::Triangle> tri = test->addComponent<myengine::Triangle>();

	std::shared_ptr<myengine::Sound> s = std::make_shared<myengine::Sound>("../Assets/Sounds/iBurn.ogg");
	//s->play();

	//std::shared_ptr<myengine::MeshRenderer> me = test->addComponent<myengine::MeshRenderer>("../Assets/Models/Box.obj", "../Assets/Textures/AsteroidTexture.bmp");
	std::shared_ptr<myengine::MeshRenderer> me = test->addComponent<myengine::MeshRenderer>();
	me->SetModel("../Assets/Models/Box.obj");
	me->SetMaterial("../Assets/Textures/AsteroidTexture.bmp");
	me->SetShaders("../Assets/Shaders/VertShader.txt", "../Assets/Shaders/FragShader.txt");

	std::shared_ptr<Death> blergh = test->addComponent<Death>(me, s);

	std::shared_ptr<myengine::Camera> cam = test->addComponent<myengine::Camera>();
	cam->cameraSetPosition(glm::vec3(0.0f, 0.0f, -10.0f));
	c->setCamera(cam);


	c->run();

	return 0;
}