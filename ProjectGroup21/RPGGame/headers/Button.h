#pragma once
#ifndef BUTTON_H
#define BUTTON_H

#include "commonfunc.h"
#include "TextObject.h"
#include "BaseObject.h"
#include "mouse.h"
#include "Collision.h"

class Button
{
public:
	BaseObject background;
	TextObject Content;
	void SetText(std::string txt) { text = txt; }
	void SetRect(const SDL_Rect &_rect) { rect_ = _rect; }
	void SetButtonColor(Uint8 red, Uint8 green, Uint8 blue);
	void Render(SDL_Renderer* des, TTF_Font* p_font);
	bool MouseOver(SDL_Event events, Mouse clone);
	bool OnClick(SDL_Event events, Mouse clone);
	void Free();
private:
	SDL_Rect rect_;
	std::string text;
};
#endif // !BUTTON_H
