#pragma once
#ifndef GAME_OVER_MENU
#define GAME_OVER_MENU

#include "Button.h"

class GameBoard
{
public:
	BaseObject Back_Ground;
	TextObject Text1, Text2;
	Button back_to_main;
	Button exit;
	void set_type(int _type) { type = _type; }
	void Render(SDL_Renderer* des, TTF_Font* p_font);
	void Free();
private:
	int type;
};
#endif // !GAME_OVER_MENU
