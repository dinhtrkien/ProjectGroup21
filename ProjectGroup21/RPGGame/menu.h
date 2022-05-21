#pragma once
#ifndef MENU_H_
#define OMENU_H_

#include "Button.h"

class GameBoard
{
public:

	//main menu

	BaseObject mainmenu_background;
	TextObject game_title;
	Button mainmenu_play;
	Button mainmenu_exit;
	Button mainmenu_continue;

	void RenderMainMenu(SDL_Renderer* des, TTF_Font* p_font);
	void MainMenuFree();

	//game over menu

	BaseObject gameover_background;
	TextObject gameover_text;
	Button gameover_backtomain;
	Button gameover_exit;

	void RenderGameOver(SDL_Renderer* des, TTF_Font* p_font);
	void GameOverFree();

	//game paused menu

	BaseObject paused_background;
	TextObject gamepaused_text;
	Button gamepaused_backtomain;
	Button gamepaused_exit;
	Button gamepaused_resume;

	void RenderGamePaused(SDL_Renderer* des, TTF_Font* p_font);
	void GamePausedFree();
};
#endif // !MENU_H_
