#include "Collision.h"

namespace myengine
{
	bool Collision::CollidedXYZ(glm::vec3 Ob1Pos, glm::vec3 Ob1Max, glm::vec3 Ob1Min, glm::vec3 Ob2Pos, glm::vec3 Ob2Max, glm::vec3 Ob2Min)
	{
		bool collided = false;

		float Ob1MaxX = Ob1Pos.x + Ob1Max.x;
		float Ob1MinX = Ob1Pos.x + Ob1Min.x;

		float Ob1MaxY = Ob1Pos.y + Ob1Max.y;
		float Ob1MinY = Ob1Pos.y + Ob1Min.y;

		float Ob1MaxZ = Ob1Pos.z + Ob1Max.z;
		float Ob1MinZ = Ob1Pos.z + Ob1Min.z;

		float Ob2MaxX = Ob2Pos.x + Ob2Max.x;
		float Ob2MinX = Ob2Pos.x + Ob2Min.x;

		float Ob2MaxY = Ob2Pos.y + Ob2Max.y;
		float Ob2MinY = Ob2Pos.y + Ob2Min.y;

		float Ob2MaxZ = Ob2Pos.z + Ob2Max.z;
		float Ob2MinZ = Ob2Pos.z + Ob2Min.z;

		//Checks collision along the X axis
		if (CheckIntersect(Ob1MaxX, Ob1MinX, Ob2MaxX, Ob2MinX))
		{
			//Checks collision o the Y axis only if collision exists on X
			if (CheckIntersect(Ob1MaxY, Ob1MinY, Ob2MaxY, Ob2MinY))
			{
				//Checks collision on Z axis only if previous two are true
				if (CheckIntersect(Ob1MaxZ, Ob1MinZ, Ob2MaxZ, Ob2MinZ))
				{
					//If all are true a collision exists
					collided = true;
				}
			}
		}

		return collided;
	}

	bool Collision::CollidedXY(glm::vec3 Ob1Pos, glm::vec3 Ob1Max, glm::vec3 Ob1Min, glm::vec3 Ob2Pos, glm::vec3 Ob2Max, glm::vec3 Ob2Min)
	{
		bool collided = false;

		float Ob1MaxX = Ob1Pos.x + Ob1Max.x;
		float Ob1MinX = Ob1Pos.x + Ob1Min.x;

		float Ob1MaxY = Ob1Pos.y + Ob1Max.y;
		float Ob1MinY = Ob1Pos.y + Ob1Min.y;

		float Ob1MaxZ = Ob1Pos.z + Ob1Max.z;
		float Ob1MinZ = Ob1Pos.z + Ob1Min.z;

		float Ob2MaxX = Ob2Pos.x + Ob2Max.x;
		float Ob2MinX = Ob2Pos.x + Ob2Min.x;

		float Ob2MaxY = Ob2Pos.y + Ob2Max.y;
		float Ob2MinY = Ob2Pos.y + Ob2Min.y;

		float Ob2MaxZ = Ob2Pos.z + Ob2Max.z;
		float Ob2MinZ = Ob2Pos.z + Ob2Min.z;

		//Checks collision along the X axis
		if (CheckIntersect(Ob1MaxX, Ob1MinX, Ob2MaxX, Ob2MinX))
		{
			//Checks collision o the Y axis only if collision exists on X
			if (CheckIntersect(Ob1MaxY, Ob1MinY, Ob2MaxY, Ob2MinY))
			{
				//If all are true a collision exists
				collided = true;

			}
		}

		return collided;
	}

	bool Collision::CheckIntersect(float aMax, float aMin, float bMax, float bMin)
	{
		bool intersect = false;

		//A simple AABB collision detection, sets intersect to true if conditions are true, other intersect will be false
		if (aMax <= bMax && aMax >= bMin)
		{
			intersect = true;
		}
		else if (aMin <= bMax && aMin >= bMin)
		{
			intersect = true;
		}

		return intersect;
	}
}