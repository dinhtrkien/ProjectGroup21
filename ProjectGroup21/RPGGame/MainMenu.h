#pragma once
#ifndef MAIN_MENU_H
#define MAIN_MENU_H
#include "Button.h"

class Board
{
public:
	BaseObject Back_Ground;
	Button new_game;
	Button continued_game;
	Button exit;
	void Render(SDL_Renderer* des, TTF_Font* p_font);
	void Free();
private:
	SDL_Rect rect_;
};

#endif // !MAIN_MENU_H
