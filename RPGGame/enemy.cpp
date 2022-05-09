#include "enemy.h"
#include "commonfunc.h"
#include "BaseObject.h"
#include <Windows.h>

Enemy::Enemy()
{
	x_pos_ = rand() % 1000;
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
	hp = 20;
	Max_hp = 20;
}

Enemy::~Enemy()
{
	e_bullet_list_.clear();
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

void Enemy::Make_Action(const int &dx, const int &dy, SDL_Renderer* screen, std::vector<Enemy*> enemy_list)
{
		set_is_move(true);
		set_des_x(dx);
		set_des_y(dy);
		set_first_x(rect_.x);
		set_first_y(rect_.y);
		if (pow(des_x_ - first_x_, 2) + pow(des_y_ - first_y_, 2) <= 90000) {
				set_is_move(false);
		}
		
			set_x_speed(int(8 * ((get_des_x() - get_first_x()) / sqrt(pow(get_des_x() - get_first_x(), 2) + pow(get_des_y() - get_first_y(), 2)))));
			set_y_speed(int(8 * ((get_des_y() - get_first_y()) / sqrt(pow(get_des_x() - get_first_x(), 2) + pow(get_des_y() - get_first_y(), 2)))));
}

void Enemy::SetupBullet(SDL_Renderer* screen, const int& dx, const int& dy)
{
	Bullet* p_bullet = e_bullet_list_[0];
	p_bullet->SetRect(rect_.x+32, rect_.y+32);
	p_bullet->set_is_move(true); // dan duoc ban
	p_bullet->set_bullet_range(500);
	p_bullet->set_des_x(dx);
	p_bullet->set_des_y(dy);
	p_bullet->set_first_x(this->rect_.x);
	p_bullet->set_first_y(this->rect_.y);
	p_bullet->set_x_speed(int(20 * ((p_bullet->get_des_x() - p_bullet->get_first_x()) / sqrt(pow(p_bullet->get_des_x() - p_bullet->get_first_x(), 2) + pow(p_bullet->get_des_y() - p_bullet->get_first_y(), 2)))));
	p_bullet->set_y_speed(int(20 * (p_bullet->get_des_y() - p_bullet->get_first_y()) / sqrt(pow(p_bullet->get_des_x() - p_bullet->get_first_x(), 2) + pow(p_bullet->get_des_y() - p_bullet->get_first_y(), 2))));
	p_bullet->set_direct_angle(atan2(double(-this->rect_.y + dy), double(-this->rect_.x + dx)) * 180 / M_PI); // set huong ban cho mui ten
	e_bullet_list_[0] = p_bullet;
}

void Enemy::HandleBullet(SDL_Renderer* des)
{
	for (int i = 0; i < e_bullet_list_.size(); i++)
	{
		Bullet* p_bullet = e_bullet_list_[i];
		if (p_bullet != NULL)
		{
			if (p_bullet->get_is_move() == true)
			{
				p_bullet->HandleMove(SCREEN_WIDTH, SCREEN_HEIGHT);
				p_bullet->Render(des, NULL, p_bullet->get_direct_angle());
			}
			else
			{
				p_bullet->set_is_move(true);
				p_bullet->SetRect(rect_.x, rect_.y);
			}
		}
	}
}
