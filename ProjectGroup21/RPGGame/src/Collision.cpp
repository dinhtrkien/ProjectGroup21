#include "Collision.h"
#include <math.h>

bool Collision::AABB(const SDL_Rect& recA, const SDL_Rect& recB)
{
	if (recA.x + recA.w >= recB.x &&
		recB.x + recB.w >= recA.x &&
		recA.y + recA.h >= recB.y &&
		recB.y + recB.h >= recA.y)
		return true;

	return false;
}

float Collision::Distance(const SDL_Rect& recA, const SDL_Rect& recB)
{
	return (float)sqrt((recA.x - recB.x)*(recA.x - recB.x) + (recA.y - recB.y)*(recA.y - recB.y));
}