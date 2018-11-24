#include <myEngine/myengine.h>

#include <iostream>
#include <memory>
#include <string>

//A dummy class to demonstrate engine use
class Dummy : public myengine::Component
{
public:
	//Set up stuff here
	void Initialise() {}
	//Set up that require other things to be initialised goes here
	void Start() {}
	//This is called every frame, place update code here
	void Update() {}
	//This is called every draw
	void Draw() {}
private:

};

class Player : public myengine::Component
{
public:
	void Initialise(std::shared_ptr<myengine::MeshRenderer> _me)
	{
		isDead = false;
		me = _me;
		deathTimer = 0.0f;
	}

	void Start()
	{

	}

	void Update()
	{
		if (isDead)
		{
			me->SetDraw(false);
			deathTimer += getCore()->getEnviroment()->getDeltaTimeS();

			if (deathTimer == 5.0f)
			{
				isDead = true;
				me->SetDraw(true);
				deathTimer = 0.0f;
			}
		}
		else
		{
			if (getCore()->getKeyboard()->GetW())
			{
				//Move up
				me->AdjustPosition(0, (1 * getCore()->getEnviroment()->getDeltaTimeS()), 0);
			}

			if (getCore()->getKeyboard()->GetA())
			{
				//Move left
				me->AdjustPosition((-1 * getCore()->getEnviroment()->getDeltaTimeS()), 0, 0);
			}

			if (getCore()->getKeyboard()->GetS())
			{
				//Move down
				me->AdjustPosition(0, (-1 * getCore()->getEnviroment()->getDeltaTimeS()), 0);
			}

			if (getCore()->getKeyboard()->GetD())
			{
				//Move right
				me->AdjustPosition((1 * getCore()->getEnviroment()->getDeltaTimeS()), 0, 0);
			}
		}
	}

	void Draw() {}

	void SetDead(bool dead)
	{

	}

private:
	bool isDead;
	float deathTimer;
	std::shared_ptr<myengine::MeshRenderer> me;
};

class Obstacle : public myengine::Component
{
public:
	void Initialise()
	{
		//Starting positioin
	}

	void Start()
	{

	}

	void Update()
	{
		//Move down, once off screen teleport to top and start again
	}
	
	void Draw()
	{

	}

private:

};

class Collideables : public myengine::Component
{
public:

	void Update()
	{

		for each (std::shared_ptr<myengine::MeshRenderer> var in o)
		{
			if (getCore()->getCollision()->Collided(p->GetPosition(), p->getMesh()->GetBoundingBoxMax(), p->getMesh()->GetBoundingBoxMin(),
				var->GetPosition(), var->getMesh()->GetBoundingBoxMax(), var->getMesh()->GetBoundingBoxMin()))
			{
				player->SetDead(true);
			}
		}
	}

private:
	std::shared_ptr<Player> player;
	std::shared_ptr<myengine::MeshRenderer> p;
	std::vector<std::shared_ptr<myengine::MeshRenderer>> o;
};

int main()
{
	std::shared_ptr<myengine::Core> c = myengine::Core::initialise();
	//We'll add general items to general, the definition of what that is is purposefully left loose
	std::shared_ptr<myengine::Entity> general = c->addEntity();

	//Initialise sky
	//This is just a plane for us to place a texture on to simulate a sky or background
	std::shared_ptr<myengine::MeshRenderer> skyBox = general->addComponent<myengine::MeshRenderer>();
	skyBox->SetModel("../Assets/Models/Plane.obj");
	skyBox->SetMaterial("../Assets/Textures/Sky.bmp");
	skyBox->SetShaders("../Assets/Shaders/VertShader.txt", "../Assets/Shaders/FragShader.txt");
	skyBox->SetPosition(0.0f, 0.0f, -40);
	skyBox->SetScale(60, 60, 1);
	
	//Initialise player
	//Within this entity we will include most if not all player components
	std::shared_ptr<myengine::Entity> player = c->addEntity();
	std::shared_ptr<myengine::MeshRenderer> me = player->addComponent<myengine::MeshRenderer>();
	me->SetModel("../Assets/Models/Box.obj");
	me->SetMaterial("../Assets/Textures/Red.bmp");
	me->SetShaders("../Assets/Shaders/VertShader.txt", "../Assets/Shaders/FragShader.txt");

	std::shared_ptr<Player> p = player->addComponent<Player>(me);

	//Initialise obstacles
	//Within this entity we will include most if not all obstacle components
	std::shared_ptr<myengine::Entity> obstacles = c->addEntity();

	std::shared_ptr<myengine::MeshRenderer> me2 = obstacles->addComponent<myengine::MeshRenderer>();
	me2->SetModel("../Assets/Models/Asteroid.obj");
	me2->SetMaterial("../Assets/Textures/AsteroidTexture.bmp");
	me2->SetShaders("../Assets/Shaders/VertShader.txt", "../Assets/Shaders/FragShader.txt");
	me2->SetScale(0.03, 0.05, 0.05);
	me2->AdjustPosition(2, 0, 0);

	//Initialise bgm
	//Here we initialise our background music
	std::shared_ptr<myengine::Sound> s = std::make_shared<myengine::Sound>("../Assets/Sounds/iBurn.ogg");
	s->play();

	std::shared_ptr<myengine::Camera> cam = general->addComponent<myengine::Camera>();
	cam->cameraSetPosition(glm::vec3(0.0f, 0.0f, -10.0f));
	c->setCamera(cam);

	c->run();

	return 0;
}