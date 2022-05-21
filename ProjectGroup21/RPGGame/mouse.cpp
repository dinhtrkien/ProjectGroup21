#include <Windows.h>
#include "mouse.h"

Mouse::Mouse()
{
	p_object_ = NULL;
	rect_.x = 0;
	rect_.y = 0;
	rect_.w = 0; //chieu rong
	rect_.h = 0; //chieu cao
	SDL_ShowCursor(false);
}

Mouse::~Mouse()
{

}

void Mouse::update()
{
	SDL_GetMouseState(&rect_.x, &rect_.y);
}

void Mouse::DrawMouse(SDL_Renderer* des)
{
	LoadImage("img/mouse.png", des);
	Render(des);
}
