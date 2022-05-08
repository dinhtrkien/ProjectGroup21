#ifndef COLLISION_H
#define COLLISION_H

#include "SDL.h"

class Collision
{
public:
	static bool AABB(const SDL_Rect& recA, const SDL_Rect& recB);
	
};

#endif // COLLISION_H
