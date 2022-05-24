#include <Windows.h>
#include "bullet.h"


Bullet::Bullet()

{
	x_speed_ = 0;
	y_speed_ = 0;
	is_move_ = false;
	des_x_ = 0;
	des_y_ = 0;
	first_x_ = 0;
	first_y_ = 0;
	bullet_range = 0;
}

Bullet::~Bullet()
{

}

void Bullet::HandleMove(const int& x_border, const int& y_border)
{
	rect_.x += x_speed_;
	rect_.y += y_speed_;
	if (rect_.x>x_border||rect_.x<=0||rect_.y>y_border||rect_.y<=0|| sqrt(pow(rect_.x - first_x_,2) + pow(rect_.y - first_y_, 2))>bullet_range)
	{
		is_move_ = false;
	} // neu dan cham thanh hoac quang duong ban ra lon hon bullet_range thi cho dung lai
}

bool Bullet::CheckMapCollision(Map& map_data)
{

	int x1 = 0;
	int x2 = 0;

	int y1 = 0;
	int y2 = 0;

	//Check va cham voi tile
		//Ckeck theo chieu ngang

	int height_min = rect_.h < TILE_SIZE ? rect_.h : TILE_SIZE;

	x1 = (int)(rect_.x + x_speed_) / TILE_SIZE;
	x2 = (int)(rect_.x + x_speed_ + rect_.w - 1) / TILE_SIZE;

	y1 = (int)(rect_.y) / TILE_SIZE;
	y2 = (int)(rect_.y + height_min) / TILE_SIZE;

	if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
	{
		if (x_speed_ < 0)
		{
			if (map_data.tile[y1][x1] != GRASS_TILE || map_data.tile[y2][x1] != GRASS_TILE)
			{
				is_move_ = false;
				return true;
			}
		}
		else if (x_speed_ > 0)
		{
			if (map_data.tile[y1][x2] != GRASS_TILE || map_data.tile[y2][x2] != GRASS_TILE)
			{
				is_move_ = false;
				return true;
			}
		}
	}

	//Check theo chieu doc

	int width_min = rect_.w < TILE_SIZE ? rect_.w : TILE_SIZE;

	x1 = (int)(rect_.x) / TILE_SIZE;
	x2 = (int)(rect_.x + width_min) / TILE_SIZE;

	y1 = (int)(rect_.y + y_speed_) / TILE_SIZE;
	y2 = (int)(rect_.y + y_speed_ + rect_.h) / TILE_SIZE;

	if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
	{
		if (y_speed_ > 0)
		{
			if (map_data.tile[y2][x1] != GRASS_TILE || map_data.tile[y2][x2] != GRASS_TILE)
			{
				is_move_ = false;
				return true;
			}
		}
		else if (y_speed_ < 0)
		{
			if (map_data.tile[y1][x1] != GRASS_TILE || map_data.tile[y1][x2] != GRASS_TILE)
			{
				is_move_ = false;
				return true;
			}
		}
	}
	return false;
}