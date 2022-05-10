#ifndef CAMERA_H_
#define CAMERA_H_

#include "SDL.h"
#include "Vector2D.h"
#include "commonfunc.h"
#include "player.h"
#include "Point.h"

class Camera
{
private:

	SDL_Rect destRect , scrRect;
	Vector2D position;
	SDL_Rect viewbox;

public:
	
	
	void setPosition(Player player);
	void setScrRect();
	void setDestRect(Player player);

	void init(Player player);
	void update(Player player);
	void draw(SDL_Renderer* renderer ,SDL_Texture* tex, SDL_RendererFlip flip);
};



#endif // CAMERA_H_