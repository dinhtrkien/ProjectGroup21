#include "TextObject.h"

TextObject::TextObject()
{
	texture_ = NULL;
	text_color_.r = 255;
	text_color_.g = 255;
	text_color_.b = 255;
}
TextObject::~TextObject()
{

}

bool TextObject::LoadFromRenderText(TTF_Font* font, SDL_Renderer* screen)
{
	free();
	SDL_Surface *text_surface = TTF_RenderText_Solid(font, text_.c_str(), text_color_);
	if (text_surface)
	{
		texture_ = SDL_CreateTextureFromSurface(screen, text_surface);
		width_ = text_surface->w;
		height_ = text_surface->h;

		SDL_FreeSurface(text_surface);
	}
	return texture_;
}

void TextObject::free()
{
	if (texture_ != NULL)
	{
		SDL_DestroyTexture(texture_);
		texture_ = NULL;
	}
}

void TextObject::SetTextColor(Uint8 red, Uint8 green, Uint8 blue)
{
	text_color_.r = red;
	text_color_.g = green;
	text_color_.b = blue;
}

void TextObject::RenderText(SDL_Renderer* screen, int x_pos, int y_pos, SDL_Rect* clip)
{
	SDL_Rect renderQuad{ x_pos, y_pos, width_, height_ };
	if (clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}
	SDL_RenderCopy(screen, texture_, clip, &renderQuad);
}


