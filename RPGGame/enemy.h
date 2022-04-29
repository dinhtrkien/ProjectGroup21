#pragma once
#ifndef ENEMY_H
#define ENEMY_H

#include <Windows.h>
#include "commonfunc.h"
#include "BaseObject.h"
#include "player.h"

class Enemy :public BaseObject
{
public:
	Enemy();
	~Enemy();
	enum WalkType
	{
		WALK_RIGHT = 0,
		WALK_LEFT = 1,
		WALK_UP = 2,
		WALK_DOWN = 3,
	};

	void set_is_move(const bool& isMove) { is_move = isMove; } // cai dat trang thai di chuyen: true-> dan duoc ban/ false->dan khong ban
	bool get_is_move() const { return is_move; } // lay trang thai vien dan

	void set_x_speed(const int& xVal) { x_speed_ = xVal; } // cai dat van toc theo phuong x
	void set_y_speed(const int& yVal) { y_speed_ = yVal; } // cai dat van toc theo phuong y
	int get_x_speed() const { return x_speed_; } // lay van toc theo phuong x
	int get_y_speed() const { return y_speed_; } // lay van toc theo phuong y

	void set_first_x(const int& desx) { first_x_ = desx; } // dat toa do diem den theo x
	int get_first_x() const { return first_x_; } // lay toa do diem den theo x

	void set_first_y(const int& desy) { first_y_ = desy; } // dat toa do diem den theo y
	int get_first_y() const { return first_y_; } // lay toa do diem den theo y

	void set_des_x(const int& desx) { des_x_ = desx; } // dat toa do diem den theo x
	int get_des_x() const { return des_x_; } // lay toa do diem den theo x

	void set_des_y(const int& desy) { des_y_ = desy; } // dat toa do diem den theo y
	int get_des_y() const { return des_y_; } // lay toa do diem den theo y
	bool LoadImage(std::string path, SDL_Renderer* screen);
	void Show(SDL_Renderer* des);
	void Make_Action(const int &dx, const int &dy, SDL_Renderer* screen);
	void Make_Animation();

	
private:
	int x_pos_;
	int y_pos_;
	int x_speed_;
	int y_speed_;
	int width_frame_;
	int height_frame_;
	SDL_Rect frame_clip_[4];
	Input input_type_;
	int frame_; // luu chi so frame la 1 hay 2 hay 3
	int status_; // trang thai tien hoac lui

	int first_x_;
	int first_y_;
	
	int des_x_;
	int des_y_;

	bool is_move;
};

#endif // !ENEMY_H
