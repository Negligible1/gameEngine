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
		recov = false;
		me = _me;
		deathTimer = 0.0f;
		speed = 5;
	}

	void Start()
	{

	}

	void Update()
	{
		if (isDead)
		{
			if (!recov)
			{
				me->SetDraw(false);
				deathTimer += getCore()->getEnviroment()->getDeltaTimeS();

				if (deathTimer >= 2.0f)
				{
					me->SetDraw(true);
					recov = true;
					deathTimer = 0.0f;
				}
			}
			else
			{
				recoveryTimer += getCore()->getEnviroment()->getDeltaTimeS();
				if (recoveryTimer >= 1.0f)
				{
					isDead = false;
					recov = false;
					recoveryTimer = 0.0f;
				}
				MovementFunction();
			}
		}
		else
		{
			MovementFunction();
		}
	}

	void Draw() {}

	void SetDead(bool dead)
	{
		isDead = dead;
	}

	bool GetDead() { return isDead; }

	void MovementFunction()
	{
		if (getCore()->getKeyboard()->GetW())
		{
			//Move up
			me->AdjustPosition(0, (speed * getCore()->getEnviroment()->getDeltaTimeS()), 0);
		}

		if (getCore()->getKeyboard()->GetA())
		{
			//Move left
			me->AdjustPosition((-speed * getCore()->getEnviroment()->getDeltaTimeS()), 0, 0);
		}

		if (getCore()->getKeyboard()->GetS())
		{
			//Move down
			me->AdjustPosition(0, (-speed * getCore()->getEnviroment()->getDeltaTimeS()), 0);
		}

		if (getCore()->getKeyboard()->GetD())
		{
			//Move right
			me->AdjustPosition((speed * getCore()->getEnviroment()->getDeltaTimeS()), 0, 0);
		}
	}

private:
	bool isDead;
	bool recov;
	float recoveryTimer;
	float deathTimer;
	int speed;
	std::shared_ptr<myengine::MeshRenderer> me;
};

class Obstacles : public myengine::Component
{
public:
	void Initialise(std::vector<std::shared_ptr<myengine::MeshRenderer>> _obVec)
	{
		obVec = _obVec;
		speed = 2;

		//Set initial positions of objects

		for each (std::shared_ptr<myengine::MeshRenderer> var in obVec)
		{
			float randX = -7.0f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (7.0f - -7.0f)));
			float randY = 14.0f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (37.0f - 14.0f)));

			var->SetPosition(randX, randY, 0.0f);
		}
	}

	void Start()
	{

	}

	void Update()
	{
		for each (std::shared_ptr<myengine::MeshRenderer> var in obVec)
		{
			if (var->GetPosition().y <= -7.0f)
			{
				var->AdjustPosition(0.0f, 14, 0.0f);
				glm::vec3 oobTL(-7, 7, 0);
				glm::vec3 oobBR(7, -7, 0);
			}
			else
			{
				var->AdjustPosition(0.0f, -(speed * getCore()->getEnviroment()->getDeltaTimeS()), 0.0f);
			}
		}
	}
	
	void Draw()
	{

	}

private:
	std::vector<std::shared_ptr<myengine::MeshRenderer>> obVec;
	int speed;

};

class Collideables : public myengine::Component
{
public:

	void Initialise(std::shared_ptr<Player> _p, std::shared_ptr<myengine::MeshRenderer> _pMesh, std::vector<std::shared_ptr<myengine::MeshRenderer>> _o)
	{
		player = _p;
		p = _pMesh;
		o = _o;
	}

	void Update()
	{
		//if the player is not dead
		if (!player->GetDead())
		{
			//for each element in the vector
			for each (std::shared_ptr<myengine::MeshRenderer> var in o)
			{
				//Perform an XY collision check
				if (getCore()->getCollision()->CollidedXY(p->GetPosition(), p->GetBoundingBoxMax(), p->GetBoundingBoxMin(),
					var->GetPosition(), var->GetBoundingBoxMax(), var->GetBoundingBoxMin()))
				{
					//Which if valid kills the player
					player->SetDead(true);
				}
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
	//We start by initialising the core
	std::shared_ptr<myengine::Core> c = myengine::Core::initialise();

	//We'll add general items to this entity
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
	me->SetScale(0.5, 0.5, 0.5);

	std::shared_ptr<Player> p = player->addComponent<Player>(me);


	//Initialise obstacles
	//Within this entity we will include most if not all obstacle components
	std::shared_ptr<myengine::Entity> obstacles = c->addEntity();

	std::shared_ptr<myengine::MeshRenderer> obLoad = obstacles->addComponent<myengine::MeshRenderer>();
	obLoad->SetModel("../Assets/Models/Asteroid.obj");
	obLoad->SetMaterial("../Assets/Textures/AsteroidTexture.bmp");
	obLoad->SetShaders("../Assets/Shaders/VertShader.txt", "../Assets/Shaders/FragShader.txt");
	obLoad->SetPosition(-100, 0, 0);

	std::vector<std::shared_ptr<myengine::MeshRenderer>> obVec;

	int Num = 100;
	for (size_t i = 0; i < Num; i++)
	{
		obVec.push_back(obstacles->addComponent<myengine::MeshRenderer>());
		obVec.at(i)->SetModel(obLoad->getMesh());
		obVec.at(i)->SetMaterial(obLoad->getMaterial());
		obVec.at(i)->SetScale(0.03, 0.05, 0.05);
		obVec.at(i)->AdjustPosition(2, 0, 0);
	}

	std::shared_ptr<Obstacles> ob = obstacles->addComponent<Obstacles>(obVec);

	

	//Initialise bgm
	//Here we initialise our background music, this does not current loop so a long music piece has been chosen to hopefully outlast play time
	std::shared_ptr<myengine::Sound> s = std::make_shared<myengine::Sound>("../Assets/Sounds/bensound-dubstep.ogg");

	//Initialise first and only camera
	//Initialise into general
	std::shared_ptr<myengine::Camera> cam = general->addComponent<myengine::Camera>();
	cam->cameraSetPosition(glm::vec3(0.0f, 0.0f, -10.0f));
	c->setCamera(cam);

	//Initialise collideables
	//This contains and grants access to objects in the scene that will collide and therefore have collision checks
	std::shared_ptr<Collideables> colliderables = general->addComponent<Collideables>(p, me, obVec);

	
	s->play();
	c->run();

	return 0;
}