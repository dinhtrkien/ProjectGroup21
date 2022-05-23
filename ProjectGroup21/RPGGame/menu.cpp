#include "menu.h"

void GameBoard::RenderMainMenu(SDL_Renderer* des, TTF_Font* p_font)
{
	game_title.SetText("ARENA   OF   ARCHER");
	game_title.LoadFromRenderText(p_font, des);
	game_title.SetTextColor(255, 0, 0);
	game_title.SetTextSize(300, 80);
	game_title.RenderText(des, 590, 50, NULL);

	mainmenu_play.SetText("PLAY");
	mainmenu_play.SetRect({ 100, 200, 80 ,30 });
	mainmenu_play.Render(des, p_font);

	mainmenu_continue.SetText("CONTINUE");
	mainmenu_continue.SetRect({ 100,265,135,30 });
	mainmenu_continue.Render(des, p_font);

	mainmenu_help.SetText("HELP");
	mainmenu_help.SetRect({ 100, 330, 80 ,30 });
	mainmenu_help.Render(des, p_font);

	mainmenu_exit.SetText("EXIT");
	mainmenu_exit.SetRect({ 100, 395 , 80 , 30 });
	mainmenu_exit.Render(des, p_font);
}
void GameBoard::MainMenuFree() 
{
	mainmenu_background.Free();
	mainmenu_help.Free();
	game_title.free();
	mainmenu_play.Free();
	mainmenu_exit.Free();
	mainmenu_continue.Free();
}

void GameBoard::RenderGamePaused(SDL_Renderer* des, TTF_Font* p_font)
{
	gamepaused_text.SetText("GAME   PAUSED");
	gamepaused_text.LoadFromRenderText(p_font, des);
	gamepaused_text.SetTextColor(0, 0, 0);
	gamepaused_text.SetTextSize(300, 80);
	gamepaused_text.RenderText(des, 590, 50, NULL);

	gamepaused_resume.SetText("RESUME");
	gamepaused_resume.SetRect({ 660, 200, 90 ,30 });
	gamepaused_resume.Render(des, p_font);

	gamepaused_backtomain.SetText("MENU");
	gamepaused_backtomain.SetRect({ 660,265,80,30 });
	gamepaused_backtomain.Render(des, p_font);

	gamepaused_exit.SetText("EXIT");
	gamepaused_exit.SetRect({ 660, 330 , 80 , 30 });
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

void GameBoard::RenderGameOver(SDL_Renderer* des, TTF_Font* p_font, int ys, int hs)
{
	gameover_text.SetText("GAME   OVER  !");
	gameover_text.LoadFromRenderText(p_font, des);
	gameover_text.SetTextColor(255, 0, 0);
	gameover_text.SetTextSize(300, 80);
	gameover_text.RenderText(des, 590, 50, NULL);

	gameover_backtomain.SetText("MENU");
	gameover_backtomain.SetRect({ 660, 350, 80 ,30 });
	gameover_backtomain.Render(des, p_font);

	gameover_exit.SetText("EXIT");
	gameover_exit.SetRect({ 660,415,80,30 });
	gameover_exit.Render(des, p_font);

	your_score.SetText("YOUR   SCORE :   " + std::to_string(ys));
	your_score.LoadFromRenderText(p_font, des);
	your_score.SetTextColor(255, 0, 0);
	your_score.RenderText(des, 620, 170, NULL);

	high_score.SetText("HIGH   SCORE :   " + std::to_string(hs));
	high_score.LoadFromRenderText(p_font, des);
	high_score.SetTextColor(255, 0, 0);
	high_score.RenderText(des, 620, 220, NULL);
}

void GameBoard::GameOverFree()
{
	your_score.free();
	high_score.free();
	gameover_background.Free();
	gameover_text.free();
	gameover_backtomain.Free();
	gameover_exit.Free();
}

void GameBoard::RenderHelpMenu(SDL_Renderer* des, TTF_Font* p_font, string path)
{
	help_background.LoadImageW(path, des);
	help_background.Render(des, NULL);

	help_backtomain.SetText("<  BACK  TO  MENU");
	help_backtomain.SetRect({ 10 , 15 , 250 , 25 });
	help_backtomain.Render(des, p_font);
}

void GameBoard::HelpMenuFree()
{
	help_background.Free();
	help_backtomain.Free();
}



