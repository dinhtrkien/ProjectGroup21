
#include <Windows.h>
#include "BaseObject.h"

BaseObject::BaseObject()
{
	p_object_ = NULL;
	rect_.x = 0;
	rect_.y = 0;
	rect_.w = 0; //chieu rong
	rect_.h = 0; //chieu cao
}

BaseObject::~BaseObject()
{
	Free();
}

bool BaseObject::LoadImage(std::string path, SDL_Renderer* screen)
{
	Free();
	SDL_Texture* new_texture = NULL;

	SDL_Surface* load_surface = IMG_Load(path.c_str());
	if (load_surface != NULL)
	{
		SDL_SetColorKey(load_surface, SDL_TRUE, SDL_MapRGB(load_surface->format, COLOR_KEY_R, COLOR_KEY_G, COLOR_KEY_B));
		new_texture = SDL_CreateTextureFromSurface(screen, load_surface); //luu giu thong tin tam anh
		if (new_texture != NULL)
		{
			rect_.w = load_surface->w;
			rect_.h = load_surface->h;

		}
		SDL_FreeSurface(load_surface);// khong can vi noi dung da chuyen qua new_texture
	}
	p_object_ = new_texture;
	return p_object_ != NULL; //mot doi tuong BaseObject da co duoc thong tin ve texture va kich thuoc cua tam anh
}

void BaseObject::Render(SDL_Renderer* des, const SDL_Rect* clip /*NULL*/, const double angle)
{
	SDL_Rect renderquad = { rect_.x, rect_.y, rect_.w, rect_.h }; // kich thuoc va vi tri

	//SDL_RenderCopy(des, p_object_, clip, &renderquad); // day thong so cua p_object_ sang des
	SDL_RenderCopyEx(des, p_object_, NULL, &renderquad, angle,NULL, SDL_FLIP_NONE); // angle la goc xoay, dung de render mui ten
}

void BaseObject::Free()
{
	if (p_object_ != NULL)
	{
		SDL_DestroyTexture(p_object_);
		p_object_ = NULL;
		rect_.w = 0;
		rect_.h = 0;
	}
}