#include "Game_Over_Menu.h"

void GameBoard::Render(SDL_Renderer* des, TTF_Font* p_font)
{
	if (type == 1)
	{
		Text1.SetText("GAME OVER");
		Text1.LoadFromRenderText(p_font, des);
		Text1.SetTextColor(0, 0, 0);
		Text1.RenderText(des, 50, 50, NULL);

		back_to_main.SetText("MENU");
		back_to_main.SetRect({ 50,190,50,30 });
		back_to_main.Render(des, p_font);

		exit.SetText("EXIT");
		exit.SetRect({ 500,90,50,30 });
		exit.Render(des, p_font);
	}
}

void GameBoard::Free()
{
	Back_Ground.Free();
	Text1.free();
	Text2.free();
	back_to_main.Free();
	exit.Free();
}