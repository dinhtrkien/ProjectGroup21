#include "Camera.h"

void Camera::init(Player player)
{
	position.x = (float)player.GetRect().x;
	position.y = (float)player.GetRect().y;

	scrRect.x = 0;
	scrRect.y = 0;
	scrRect.w = scrRect.h = 32;

	destRect.x = player.GetRect().x;
	destRect.y = player.GetRect().y;
	destRect.w = destRect.h = 64;
}



void Camera::update(Player player)
{
	
	viewbox.x = player.GetRect().x - SCREEN_WIDTH / 2;
	viewbox.y = player.GetRect().y - SCREEN_HEIGHT / 2;

	if (viewbox.x < 0) 
		viewbox.x = 0;
		
	if (viewbox.y < 0)
		viewbox.y = 0;

	if (viewbox.x > viewbox.w)
		viewbox.x = viewbox.w;
		
	if (viewbox.y > viewbox.h)
		viewbox.y = viewbox.h;


	destRect.x = (int)position.x - viewbox.x;
	destRect.y = (int)position.y - viewbox.y;

	
}

void Camera::draw(SDL_Renderer* renderer, SDL_Texture* tex, SDL_RendererFlip flip)
{
	SDL_RenderCopyEx(renderer, tex, &scrRect, &destRect, NULL, NULL, flip);
}











void Camera::setPosition(Player player)
{
	position.x = (float)player.GetRect().x;
	position.y = (float)player.GetRect().y;
}

void Camera::setScrRect()
{
	scrRect.x = 0;
	scrRect.y = 0;
	scrRect.w = scrRect.h = 32;
}

void Camera::setDestRect(Player player)
{
	destRect.x = player.GetRect().x;
	destRect.y = player.GetRect().y;
	destRect.w = destRect.h = 64;
}