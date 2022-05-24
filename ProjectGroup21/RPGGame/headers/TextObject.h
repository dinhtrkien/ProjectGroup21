#pragma once
#ifndef TEXT_OBJECT_H_
#define TEXT_OBJECT_H_

#include "commonfunc.h"
#include <string.h>

using std::string;

class TextObject 
{

public:

	TextObject();
	~TextObject();

	bool LoadFromRenderText(TTF_Font* font, SDL_Renderer* screen);
	void RenderText(SDL_Renderer* screen, int x_pos, int y_pos, SDL_Rect* clip);
	void free();

	void SetTextColor(Uint8 red, Uint8 green, Uint8 blue);
	void SetTextSize(int w, int h);
	
	int GetWidth () const { return width_; }
	int GetHeight () const { return height_; }
	string GetText () const { return text_; }
	
	void SetText(string _text) { text_ = _text; }

private:
	string text_;
	SDL_Color text_color_;
	SDL_Texture* texture_;
	int width_;
	int height_;
};



#endif // !TEXT_OBJECT_H

