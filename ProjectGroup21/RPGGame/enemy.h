#ifndef ENEMY_H
#define ENEMY_H

#include <Windows.h>
#include "commonfunc.h"
#include "BaseObject.h"
#include "player.h"
#include "bullet.h"

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

	void set_width_frame(const int& w) { width_frame_ = w; }
	void set_height_frame(const int& h) { height_frame_ = h; }

	int get_width_frame() const { return width_frame_; }
	int get_height_frame() const { return height_frame_; }

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

	void set_x_pos(const int& _x) { x_pos_ = _x; }
	void set_y_pos(const int& _x) { y_pos_ = _x; }
	bool LoadImage(std::string path, SDL_Renderer* screen);
	void Show(SDL_Renderer* des);
	void Make_Action(const int &dx, const int &dy, SDL_Renderer* screen, std::vector<Enemy*> enemy_list);
	void Make_Animation();

	void set_bullet_list(std::vector<Bullet*> bullet_list)
	{
		e_bullet_list_ = bullet_list;
	}
	std::vector<Bullet*> get_bullet_list() const { return e_bullet_list_; }
	
	void SetupBullet(SDL_Renderer* screen, const int& dx, const int& dy);
	void HandleBullet(SDL_Renderer* des);

	void LoadBullet(SDL_Renderer* screen)
	{
		Bullet* p_bullet = new Bullet();
		p_bullet->LoadImage("img/bullet12.png", screen);
		p_bullet->SetRect(rect_.x+32, rect_.y+32);
		e_bullet_list_.push_back(p_bullet);

	}

	void set_hp(const int& _hp) { hp = _hp; }
	int get_hp() { return hp; }

	void set_Max_hp(const int& _hp) { Max_hp = _hp; }
	int get_Max_hp() { return Max_hp; }

	void set_damage(const int& _damage) { damage = _damage; }
	int get_damage() { return damage; }

	void Export(std::string file_path)
	{
		std::ofstream p_data(file_path);
		if (p_data)
		{
			p_data << x_speed_ << std::endl;
			p_data << y_speed_ << std::endl;
			p_data << x_pos_ << std::endl;
			p_data << y_pos_ << std::endl;
			p_data << status_ << std::endl;
			p_data << hp << std::endl;
			p_data << Max_hp << std::endl;
			p_data << damage << std::endl;
			p_data.close();
		}
	}

private:
	std::vector<Bullet*> e_bullet_list_;
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

	int hp;
	int Max_hp;
	int damage;
};

#endif // !ENEMY_H
