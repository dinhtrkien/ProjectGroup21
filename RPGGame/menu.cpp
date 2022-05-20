#include "menu.h"

void GameBoard::RenderMainMenu(SDL_Renderer* des, TTF_Font* p_font)
{
	game_title.SetText("ARENA   OF   ARCHER");
	game_title.LoadFromRenderText(p_font, des);
	game_title.SetTextColor(255, 0, 0);
	game_title.SetTextSize(250, 70);
	game_title.RenderText(des, 500, 50, NULL);

	mainmenu_play.SetText("PLAY");
	mainmenu_play.SetRect({ 100, 200, 63 ,30 });
	mainmenu_play.Render(des, p_font);

	mainmenu_continue.SetText("CONTINUE");
	mainmenu_continue.SetRect({ 100,265,63,30 });
	mainmenu_continue.Render(des, p_font);

	mainmenu_exit.SetText("EXIT");
	mainmenu_exit.SetRect({ 100, 330 , 63 , 30 });
	mainmenu_exit.Render(des, p_font);
}
void GameBoard::MainMenuFree() 
{
	mainmenu_background.Free();
	game_title.free();
	mainmenu_play.Free();
	mainmenu_exit.Free();
	mainmenu_continue.Free();
}

void GameBoard::RenderGamePaused(SDL_Renderer* des, TTF_Font* p_font)
{
	gamepaused_text.SetText("GAME PAUSED");
	gamepaused_text.LoadFromRenderText(p_font, des);
	gamepaused_text.SetTextColor(0, 0, 0);
	gamepaused_text.SetTextSize(250, 70);
	gamepaused_text.RenderText(des, 500, 50, NULL);

	gamepaused_resume.SetText("RESUME");
	gamepaused_resume.SetRect({ 550, 200, 60 ,30 });
	gamepaused_resume.Render(des, p_font);

	gamepaused_backtomain.SetText("MENU");
	gamepaused_backtomain.SetRect({ 550,265,60,30 });
	gamepaused_backtomain.Render(des, p_font);

	gamepaused_exit.SetText("EXIT");
	gamepaused_exit.SetRect({ 550, 330 , 60 , 30 });
	gamepaused_exit.Render(des, p_font);
}

void GameBoard::GamePausedFree()
{
	paused_background.Free();
	gamepaused_text.free();
	gamepaused_backtomain.Free();
	gamepaused_exit.Free();
	gamepaused_resume.Free();
}

void GameBoard::RenderGameOver(SDL_Renderer* des, TTF_Font* p_font)
{
	gameover_text.SetText("GAME   OVER    !");
	gameover_text.LoadFromRenderText(p_font, des);
	gameover_text.SetTextColor(255, 0, 0);
	gameover_text.SetTextSize(250, 70);
	gameover_text.RenderText(des, 500, 50, NULL);

	gameover_backtomain.SetText("MENU");
	gameover_backtomain.SetRect({ 550, 200, 60 ,30 });
	gameover_backtomain.Render(des, p_font);

	gameover_exit.SetText("EXIT");
	gameover_exit.SetRect({ 550,265,60,30 });
	gameover_exit.Render(des, p_font);
}

void GameBoard::GameOverFree()
{
	gameover_background.Free();
	gameover_text.free();
	gameover_backtomain.Free();
	gameover_exit.Free();
}



