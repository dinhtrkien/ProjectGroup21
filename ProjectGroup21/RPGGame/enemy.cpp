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
		width_frame_ = rect_.w/3;
		height_frame_ = rect_.h;
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

		frame_clip_[1].x = width_frame_;
		frame_clip_[1].y = 0;
		frame_clip_[1].w = width_frame_;
		frame_clip_[1].h = height_frame_;

		frame_clip_[2].x = width_frame_ * 2;
		frame_clip_[2].y = 0;
		frame_clip_[2].w = width_frame_;
		frame_clip_[2].h = height_frame_;
	}
}

void Enemy::Show(SDL_Renderer* des)
{
	if (status_ == WALK_RIGHT)
	{
		LoadImage("enemy_right.png", des);
	}

	if (status_ == WALK_LEFT) LoadImage("img/enemy_left.png", des);
	if (status_ == WALK_UP) LoadImage("img/enemy_up.png", des);
	if (status_ == WALK_DOWN) LoadImage("img/enemy_down.png", des);
	if (is_move)
	{
		frame_++;
		x_pos_ += x_speed_;
		y_pos_ += y_speed_;
	}
	else frame_ = 0;
	if (frame_ > 2) frame_ = 0;

	rect_.x = x_pos_;
	rect_.y = y_pos_;

	SDL_Rect* current_clip = frame_clip_ + frame_;

	SDL_Rect renderQuad = { rect_.x, rect_.y, width_frame_, height_frame_ };

	SDL_RenderCopy(des, p_object_, current_clip, &renderQuad);

}

void Enemy::Make_Action(const int& dx, const int& dy, SDL_Renderer* screen, std::vector<Enemy*> enemy_list)
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
	p_bullet->SetRect(rect_.x + 32, rect_.y + 32);
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

void Enemy::CheckMapCollision(Map& map_data)
{
	x_val_ = 0;
	y_val_ = 0;

	if (is_move)
	{
		x_val_ += x_speed_;
		x_val_ += y_speed_;
	}

	int x1 = 0;
	int x2 = 0;

	int y1 = 0;
	int y2 = 0;

	//Check va cham voi tile
		//Ckeck theo chieu doc

	int height_min = height_frame_ < TILE_SIZE ? height_frame_ : TILE_SIZE;

	x1 = (int)(x_pos_ + x_val_) / TILE_SIZE;
	x2 = (int)(x_pos_ + x_val_ + width_frame_ - 1) / TILE_SIZE;

	y1 = (int)y_pos_ / TILE_SIZE;
	y2 = (int)(y_pos_ + height_min) / TILE_SIZE;

	if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
	{
		if (x_val_ < 0)
		{
			if (map_data.tile[y1][x1] != GRASS_TILE || map_data.tile[y2][x1] != GRASS_TILE)
			{
				x_pos_ = (float)(x1 + 1) * TILE_SIZE;
				x_val_ = 0;
			}
		}
		else if (x_val_ > 0)
		{
			if (map_data.tile[y1][x2] != GRASS_TILE || map_data.tile[y2][x2] != GRASS_TILE)
			{
				x_pos_ = (float)x2 * TILE_SIZE;
				x_pos_ -= (width_frame_ + 1);
				x_val_ = 0;
			}
		}
	}

	//Check theo chieu ngang

	int width_min = width_frame_ < TILE_SIZE ? width_frame_ : TILE_SIZE;

	x1 = (int)(x_pos_) / TILE_SIZE;
	x2 = (int)(x_pos_ + width_min) / TILE_SIZE;

	y1 = (int)(y_pos_ + y_val_) / TILE_SIZE;
	y2 = (int)(y_pos_ + y_val_ + height_frame_) / TILE_SIZE;

	if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
	{
		if (y_val_ > 0)
		{
			if (map_data.tile[y2][x1] != GRASS_TILE || map_data.tile[y2][x2] != GRASS_TILE)
			{
				y_pos_ = (float)y2 * TILE_SIZE;
				y_pos_ -= (height_frame_ + 1);
				y_val_ = 0;
			}
		}
		else if (y_val_ < 0)
		{
			if (map_data.tile[y1][x1] != GRASS_TILE || map_data.tile[y1][x2] != GRASS_TILE)
			{
				y_pos_ = (float)(y1 + 1) * TILE_SIZE;
				y_val_ = 0;
			}
		}
	}

	//Check va cham voi ria map
	if (x_pos_ < 0)
		x_pos_ = 0;
	if (x_pos_ + width_frame_ > map_data.max_x_)
		x_pos_ = (float)(map_data.max_x_ - width_frame_ - 1);
	if (y_pos_ < 0)
		y_pos_ = 0;
	if (y_pos_ + height_frame_ > map_data.max_y_)
		y_pos_ = (float)(map_data.max_y_ - height_frame_ - 1);
}