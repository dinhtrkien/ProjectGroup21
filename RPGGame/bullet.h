#pragma once
#ifndef BULLET_H
#define BULLET_H

#include "commonfunc.h"
#include "BaseObject.h"

class Bullet : public BaseObject
{
public:
	Bullet();
	~Bullet();

	void set_x_speed(const int& xVal) { x_speed_ = xVal; } // cai dat van toc theo phuong x
	void set_y_speed(const int& yVal) { y_speed_ = yVal; } // cai dat van toc theo phuong y
	int get_x_speed() const { return x_speed_; } // lay van toc theo phuong x
	int get_y_speed() const { return y_speed_; } // lay van toc theo phuong y

	void set_is_move(const bool& isMove) { is_move_ = isMove; } // cai dat trang thai di chuyen: true-> dan duoc ban/ false->dan khong ban
	bool get_is_move() const {return is_move_;} // lay trang thai vien dan

	void set_first_x(const int& desx) { first_x_ = desx; } // dat toa do diem den theo x
	int get_first_x() const { return first_x_; } // lay toa do diem den theo x

	void set_first_y(const int& desy) { first_y_ = desy; } // dat toa do diem den theo y
	int get_first_y() const { return first_y_; } // lay toa do diem den theo y

	void set_des_x(const int& desx) { des_x_ = desx; } // dat toa do diem den theo x
	int get_des_x() const { return des_x_; } // lay toa do diem den theo x

	void set_des_y(const int& desy) { des_y_ = desy; } // dat toa do diem den theo y
	int get_des_y() const { return des_y_; } // lay toa do diem den theo y

	void set_direct_angle(const double& angle) { direct_angle = angle; } // 
	double get_direct_angle() const { return direct_angle; }

	void set_bullet_range(const int& range) { bullet_range = range; }
	int get_bullet_range() const { return bullet_range; }

	void HandleMove(const int& x_border, const int& y_border);
private:
	double direct_angle;
	int x_speed_;// van toc theo x
	int y_speed_;// van toc theo y
	int first_x_; // toa do diem dau
	int first_y_;// toa do diem dau
	int des_x_;// toa do dich vien dan
	int des_y_;// toa do dich vien dan
	bool is_move_; // trang thai vien dan
	int bullet_range; // tam xa cua vien dan
};

#endif // !BULLET_H
