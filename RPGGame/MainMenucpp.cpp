#include "MainMenu.h"

void Board::Render(SDL_Renderer* des, TTF_Font* p_font)
{
	new_game.SetText("NEW GAME");
	new_game.SetRect({ 50,50,50,30 });
	new_game.Render(des, p_font);

	continued_game.SetText("CONTINUE");
	continued_game.SetRect({ 50,90,50,30 });
	continued_game.Render(des, p_font);

	exit.SetText("EXIT");
	exit.SetRect({ 50,130,50,30 });
	exit.Render(des, p_font);
}

void Board::Free()
{
	new_game.Free();
	continued_game.Free();
	exit.Free();
	rect_ = { 0,0,0,0 };
}