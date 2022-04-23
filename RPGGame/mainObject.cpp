#include <windows.h>
#include "mainObject.h"

MainObject::MainObject()
{
	this->frame_ = 0;
	this->x_val_ = 0;
	this->y_val_ = 0;
	this->x_pos_ = 0;
	this->y_pos_ = 0;
	this->map_x_ = 0;
	this->map_y_ = 0;
	this->width_frame_ = 0;
	this->height_frame_ = 0;
	this->status_ = -1;
	this->input_type_.left_ = 0;
	this->input_type_.right_ = 0;
	this->input_type_.down_ = 0;
	this->input_type_.up_ = 0;
	for (int i = 0; i < 4; i++)
	{
		this->frame_clip_[i].x = 0;
		this->frame_clip_[i].y = 0;
	}
}

MainObject::~MainObject()
{
	Free();
}

bool MainObject::LoadImage(std::string path, SDL_Renderer* screen)
{
	bool ret = BaseObject::LoadImage(path, screen);

	if (ret == true)
	{
		width_frame_ = rect_.w;
		height_frame_ = rect_.h / 4;
	}

	return ret;
}

void MainObject::Main_Set_clip()
{
	if (width_frame_ > 0 && height_frame_ > 0)
	{
		frame_clip_[0].x = 0;
		frame_clip_[0].y = 0;
		frame_clip_[0].w = width_frame_;
		frame_clip_[0].h = height_frame_;

		frame_clip_[1].x = 0;
		frame_clip_[1].y = height_frame_;
		frame_clip_[1].w = width_frame_;
		frame_clip_[1].h = height_frame_;

		frame_clip_[2].x = 0;
		frame_clip_[2].y = height_frame_ * 2;
		frame_clip_[2].w = width_frame_;
		frame_clip_[2].h = height_frame_;

		frame_clip_[3].x = 0;
		frame_clip_[3].y = height_frame_ * 3;
		frame_clip_[3].w = width_frame_;
		frame_clip_[3].h = height_frame_;

	}
}

void MainObject::Show(SDL_Renderer* des)
{
	if (status_ == WALK_RIGHT)
	{
		LoadImage("img/player_right.png", des);
	}

	if (status_ == WALK_LEFT) LoadImage("img/player_left.png", des);
	if (status_ == WALK_UP) LoadImage("img/player_up.png", des);
	if (status_ == WALK_DOWN) LoadImage("img/player_down.png", des);
	if (input_type_.left_ == 1 || input_type_.right_ == 1 || input_type_.down_ == 1||input_type_.up_==1)
		{
			frame_++;

			if (input_type_.left_ == 1) x_pos_ -= PLAYER_SPEED;
			if (input_type_.right_ == 1) x_pos_ += PLAYER_SPEED;
			if (input_type_.down_ == 1) y_pos_ += PLAYER_SPEED;
			if (input_type_.up_ == 1) y_pos_ -= PLAYER_SPEED;
		}
		else frame_ = 0;
	if (frame_ > 3) frame_ = 0;


	rect_.x = int(x_pos_)-map_x_;
	rect_.y = int(y_pos_)-map_y_;

	SDL_Rect* current_clip = frame_clip_+frame_;

	SDL_Rect renderQuad = { rect_.x, rect_.y, width_frame_, height_frame_ };

	SDL_RenderCopy(des, p_object_, current_clip, &renderQuad);
}

void MainObject::HandleInputAction(SDL_Event events, SDL_Renderer* screen)
{
	if (events.type == SDL_KEYDOWN)
	{
		switch (events.key.keysym.sym)
		{
		case SDLK_d:
		{
			status_ = WALK_RIGHT;
			input_type_.right_ = 1;
			input_type_.left_ = 0;
			input_type_.down_ = 0;
			input_type_.up_ = 0;


		} break;
		case SDLK_a:
		{
			status_ = WALK_LEFT;
			input_type_.left_ = 1;
			input_type_.right_ = 0;
			input_type_.down_ = 0;
			input_type_.up_ = 0;

		} break;
		case SDLK_w:
		{
			status_ = WALK_UP;
			input_type_.up_ = 1;
			input_type_.left_ = 0;
			input_type_.right_ = 0;
			input_type_.down_ = 0;

		} break;
		case SDLK_s:
		{
			status_ = WALK_DOWN;
			input_type_.down_ = 1;
			input_type_.left_ = 0;
			input_type_.right_ = 0;

			input_type_.up_ = 0;

		} break;
		default: break;
		}
	}
	else if (events.type == SDL_KEYUP)
	{
		switch (events.key.keysym.sym)
		{
		case SDLK_d:
		{
			input_type_.right_ = 0;

		} break;
		case SDLK_a:
		{
			input_type_.left_ = 0;

		} break;
		case SDLK_w:
		{
			input_type_.up_ = 0;

		} break;
		case SDLK_s:
		{
			input_type_.down_ = 0;

		} break;
		default: break;
		}
	}
}

void MainObject::DoPlayer(Map& map_data)
{
	if (input_type_.left_ == 1) x_val_ -= PLAYER_SPEED;
	if (input_type_.right_ == 1) x_val_ += PLAYER_SPEED;
	if (input_type_.down_ == 1) y_val_ += PLAYER_SPEED;
	if (input_type_.up_ == 1) y_val_ -= PLAYER_SPEED;
	CenterEntityOnMap(map_data);
}

void MainObject::CenterEntityOnMap(Map& map_data)
{
	map_data.start_x_ = x_pos_ - (SCREEN_WIDTH / 2);
	if (map_data.start_x_ < 0)
	{
		map_data.start_x_ = 0;
	}
	else if (map_data.start_x_ + SCREEN_WIDTH >= map_data.max_x_)
	{
		map_data.start_x_ = map_data.max_x_ - SCREEN_WIDTH;
	}

	map_data.start_y_ = y_pos_ - (SCREEN_HEIGHT / 2);
	if (map_data.start_y_ < 0)
	{
		map_data.start_y_ = 0;
	}
	else if (map_data.start_y_ + SCREEN_HEIGHT >= map_data.max_y_)
	{
		map_data.start_y_ = map_data.max_y_ - SCREEN_HEIGHT;
	}
}

void MainObject::CheckToMap(Map& map_data)
{
	return;
}
