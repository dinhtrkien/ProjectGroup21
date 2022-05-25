#include "explosion.h"
#include <math.h>

Explosion::Explosion()
{
	frame_ = 0;
	width_frame_ = 0;
	height_frame_ = 0;
	angle = 0;
	for (int i = 0; i < 5; i++)
		frame_clip_[i] = { 0,0,0,0 };
}

Explosion::~Explosion()
{

}

bool Explosion::LoadImage(std::string path, SDL_Renderer* screen)
{
	bool ret = BaseObject::LoadImage(path, screen);

	if (ret == true)
	{
		width_frame_ = rect_.w/5;
		height_frame_ = rect_.h;
	}

	return ret;
}

void Explosion::Set_Clip()
{
	if (width_frame_ > 0 && height_frame_ > 0)
	{
		frame_clip_[0].x = 0;
		frame_clip_[0].y = 0;
		frame_clip_[0].w = width_frame_;
		frame_clip_[0].h = height_frame_;

		frame_clip_[1].x = width_frame_;
		frame_clip_[1].y = 0;
		frame_clip_[1].w = width_frame_;
		frame_clip_[1].h = height_frame_;

		frame_clip_[2].x = width_frame_ * 2;
		frame_clip_[2].y = 0;
		frame_clip_[2].w = width_frame_;
		frame_clip_[2].h = height_frame_;

		frame_clip_[3].x = width_frame_*3;
		frame_clip_[3].y = 0;
		frame_clip_[3].w = width_frame_;
		frame_clip_[3].h = height_frame_;

		frame_clip_[4].x = width_frame_*4;
		frame_clip_[4].y = 0;
		frame_clip_[4].w = width_frame_;
		frame_clip_[4].h = height_frame_;

	}
}

void Explosion::Show(SDL_Renderer* des)
{	
		SDL_Rect* current_clip = frame_clip_ + frame_;

		SDL_Rect renderQuad = { rect_.x, rect_.y, width_frame_, height_frame_ };

		SDL_RenderCopyEx(des, p_object_, current_clip, &renderQuad,angle,NULL,SDL_FLIP_NONE);
}