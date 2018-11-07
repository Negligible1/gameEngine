#include <myEngine/myengine.h>
#include <iostream>
#include <memory>

int main()
{

	
	std::shared_ptr<myengine::Core> c = myengine::Core::initialise();



	c->run();

	return 0;
}