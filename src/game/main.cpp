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
	std::shared_ptr<TestScreen> testEnt = test->addComponent<TestScreen>();


	c->run();

	return 0;
}