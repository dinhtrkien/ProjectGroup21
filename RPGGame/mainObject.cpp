#include <windows.h>
#include "mainObject.h"
#include <vector>

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
	std::vector<Bullet*> p_bullet_list_;
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
	if (input_type_.left_ == 1 || input_type_.right_ == 1 || input_type_.down_ == 1 || input_type_.up_ == 1)
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
		const Uint8* state = SDL_GetKeyboardState(NULL);
		if (state[SDL_SCANCODE_D]&&state[SDL_SCANCODE_W])
		{
			status_ = WALK_RIGHT;
			input_type_.right_ = 1;
			input_type_.left_ = 0;
			input_type_.down_ = 0;
			input_type_.up_ = 1;
		} else
		if (state[SDL_SCANCODE_D] && state[SDL_SCANCODE_S])
		{
			status_ = WALK_RIGHT;
			input_type_.right_ = 1;
			input_type_.left_ = 0;
			input_type_.down_ = 1;
			input_type_.up_ = 0;
		} else
		if (state[SDL_SCANCODE_A] && state[SDL_SCANCODE_W])
		{
			status_ = WALK_LEFT;
			input_type_.right_ = 0;
			input_type_.left_ = 1;
			input_type_.down_ = 0;
			input_type_.up_ = 1;
		} else
		if (state[SDL_SCANCODE_A] && state[SDL_SCANCODE_S])
		{
			status_ = WALK_LEFT;
			input_type_.right_ = 0;
			input_type_.left_ = 1;
			input_type_.down_ = 1;
			input_type_.up_ = 0;
		}
		else
		{
			if (state[SDL_SCANCODE_D])
			{
				status_ = WALK_RIGHT;
				input_type_.right_ = 1;
				input_type_.left_ = 0;
				input_type_.down_ = 0;
				input_type_.up_ = 0;
			}
			else
			{
				input_type_.right_ = 0;
			}
			if (state[SDL_SCANCODE_A])
			{
				status_ = WALK_LEFT;
				input_type_.right_ = 0;
				input_type_.left_ = 1;
				input_type_.down_ = 0;
				input_type_.up_ = 0;
			}
			else input_type_.left_ = 0;
			if (state[SDL_SCANCODE_W])
			{
				status_ = WALK_UP;
				input_type_.right_ = 0;
				input_type_.left_ = 0;
				input_type_.down_ = 0;
				input_type_.up_ = 1;
			}
			else input_type_.up_ = 0;
			if (state[SDL_SCANCODE_S])
			{
				status_ = WALK_DOWN;
				input_type_.right_ = 0;
				input_type_.left_ = 0;
				input_type_.down_ = 1;
				input_type_.up_ = 0;
			}
			else input_type_.down_ = 0;
		}
	if (events.type == SDL_MOUSEBUTTONDOWN)
	{
		if (events.button.button == SDL_BUTTON_LEFT)
		{
			Bullet* p_bullet = new Bullet();
			p_bullet->LoadImage("img/bullet.png", screen);
			p_bullet->SetRect(this->rect_.x, this->rect_.y); // lay vi tri render
			p_bullet->set_is_move(true); // dan duoc ban
			Uint32 Button;
			int dx, dy;
			SDL_PumpEvents();
			Button = SDL_GetMouseState(&dx, &dy);
			p_bullet->set_bullet_range(300);
			p_bullet->set_des_x(dx);
			p_bullet->set_des_y(dy);
			p_bullet->set_first_x(this->rect_.x);
			p_bullet->set_first_y(this->rect_.y);
			p_bullet->set_x_speed( int(50 *((p_bullet->get_des_x() - p_bullet->get_first_x()) / sqrt(pow(p_bullet->get_des_x() - p_bullet->get_first_x(), 2) + pow(p_bullet->get_des_y() - p_bullet->get_first_y(), 2)))));
			p_bullet->set_y_speed(int(50* (p_bullet->get_des_y() - p_bullet->get_first_y()) / sqrt(pow(p_bullet->get_des_x() - p_bullet->get_first_x(), 2) + pow(p_bullet->get_des_y() - p_bullet->get_first_y(), 2))));
			p_bullet->set_direct_angle(atan2(double(-this->rect_.y + dy), double(-this->rect_.x + dx)) * 180 / M_PI); // set huong ban cho mui ten
			p_bullet_list_.push_back(p_bullet);
		}
	}
}

void MainObject::HandleBullet(SDL_Renderer* des)
{
	for (int i=0;i<p_bullet_list_.size();i++)
	{
		Bullet* p_bullet = p_bullet_list_[i];
		if (p_bullet != NULL)
		{
			if (p_bullet->get_is_move() == true)
			{
				p_bullet->HandleMove(SCREEN_WIDTH, SCREEN_HEIGHT);
				p_bullet->Render(des, NULL, p_bullet->get_direct_angle());
			}
			else
			{
				p_bullet_list_.erase(p_bullet_list_.begin(), p_bullet_list_.begin()+i);
				p_bullet = NULL;
				if (p_bullet != NULL)
				{
					delete p_bullet;
				}
			}
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
