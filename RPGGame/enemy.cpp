#include "enemy.h"
#include "commonfunc.h"
#include "BaseObject.h"
#include <Windows.h>

Enemy::Enemy()
{
	x_pos_ = 0;
	y_pos_ = 0;
	x_speed_ = 0;
	y_speed_ = 0;
	frame_ = 0;
	status_ = WALK_DOWN;
	height_frame_ = 0;
	width_frame_ = 0;
	des_x_ = 0;
	des_y_ = 0;

	first_x_ = 0;
	first_y_ = 0;

	is_move = false;
}

Enemy::~Enemy()
{

}

bool Enemy::LoadImage(std::string path, SDL_Renderer* screen)
{
	bool ret = BaseObject::LoadImage(path, screen);

	if (ret == true)
	{
		width_frame_ = rect_.w;
		height_frame_ = rect_.h / 4;
	}

	return ret;
}

void Enemy::Make_Animation()
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

void Enemy::Show(SDL_Renderer* des)
{
	if (status_ == WALK_RIGHT)
	{
		LoadImage("img/player_right.png", des);
	}

	if (status_ == WALK_LEFT) LoadImage("img/player_left.png", des);
	if (status_ == WALK_UP) LoadImage("img/player_up.png", des);
	if (status_ == WALK_DOWN) LoadImage("img/player_down.png", des);
	if (is_move)
	{
		frame_++;
		x_pos_ += x_speed_;
		y_pos_ += y_speed_;
	}
	else frame_ = 0;
	if (frame_ > 3) frame_ = 0;

	rect_.x = x_pos_;
	rect_.y = y_pos_;

	SDL_Rect* current_clip = frame_clip_ + frame_;

	SDL_Rect renderQuad = { rect_.x, rect_.y, width_frame_, height_frame_ };

	SDL_RenderCopy(des, p_object_, current_clip, &renderQuad);
}

void Enemy::Make_Action(const int &dx, const int &dy, SDL_Renderer* screen)
{
		set_is_move(true);
		set_des_x(dx);
		set_des_y(dy);
		set_first_x(rect_.x);
		set_first_y(rect_.y);
		if (pow(des_x_ - first_x_, 2) + pow(des_y_ - first_y_, 2) < 2500) set_is_move(false);
		set_x_speed(int(8 * ((get_des_x() - get_first_x()) / sqrt(pow(get_des_x() - get_first_x(), 2) + pow(get_des_y() - get_first_y(), 2)))));
		set_y_speed(int(8 * ((get_des_y() - get_first_y()) / sqrt(pow(get_des_x() - get_first_x(), 2) + pow(get_des_y() - get_first_y(), 2)))));
}
