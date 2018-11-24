#include <glm/glm.hpp>

#ifndef MYENGINE_COLLISION_H
#define MYENGINE_COLLISION_H


namespace myengine
{

	class Collision
	{
	public:
		bool Collided(glm::vec3 Ob1Pos, glm::vec3 Ob1Max, glm::vec3 Ob1Min, glm::vec3 Ob2Pos, glm::vec3 Ob2Max, glm::vec3 Ob2Min);
	private:
		bool CheckIntersect(float a , float b, float c, float d);
	};

}


#endif // !MYENGINE_COLLISION_H