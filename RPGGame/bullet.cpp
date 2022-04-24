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