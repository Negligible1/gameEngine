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


int main()
{
	std::shared_ptr<myengine::Core> c = myengine::Core::initialise();
	std::shared_ptr<myengine::Entity> test = c->addEntity();
	//std::shared_ptr<TestScreen> testEnt = test->addComponent<TestScreen>();
	//std::shared_ptr<myengine::Triangle> tri = test->addComponent<myengine::Triangle>();

	std::shared_ptr<myengine::MeshRenderer> me = test->addComponent<myengine::MeshRenderer>("../Assets/Models/Box.obj", "../Assets/Textures/Blue.bmp");
	std::shared_ptr<myengine::Camera> cam = test->addComponent<myengine::Camera>();
	c->setCamera(cam); 



	c->run();

	return 0;
}