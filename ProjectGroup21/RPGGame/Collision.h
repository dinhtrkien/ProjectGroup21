#ifndef COLLISION_H_
#define COLLISION_H_

#include "SDL.h"

class Collision
{
public:
	static bool AABB(const SDL_Rect& recA, const SDL_Rect& recB);


	static float Distance(const SDL_Rect& recA, const SDL_Rect& recB);
	
};

#endif // COLLISION_H_
