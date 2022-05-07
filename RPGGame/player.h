#pragma once
#ifndef PLAYER_H_
#define PLAYER_H_

#include "commonfunc.h"
#include "BaseObject.h"
#include "bullet.h"
#include <vector>

#define PLAYER_SPEED 20;

class Player : public BaseObject
{
public:
	Player();
	~Player();

	enum WalkType
	{
		WALK_RIGHT = 0,
		WALK_LEFT = 1,
		WALK_UP = 2,
		WALK_DOWN = 3,
	};

	bool LoadImage(std::string path, SDL_Renderer* screen);
	void Show(SDL_Renderer* des);
	void HandleInputAction(SDL_Event events, SDL_Renderer* screen);
	void Main_Set_clip();
	void SetMapXY(const int map_x, const int map_y)
	{
		map_x_ = map_x;
		map_y_ = map_y;
	}

	void set_bullet_list(std::vector<Bullet*> bullet_list)
	{
		p_bullet_list_ = bullet_list;
	}
	std::vector<Bullet*> get_bullet_list() const { return p_bullet_list_; }
	void HandleBullet(SDL_Renderer* des);

	void Free_Bullet(const int& i)
	{
		Bullet* clone = p_bullet_list_[i];
		p_bullet_list_.erase(p_bullet_list_.begin(), p_bullet_list_.begin() + i);
		if (clone != NULL)
		{
			delete clone;
			clone = NULL;
		}
	}

	void set_hp_(int _hp) { hp = _hp; }
	int get_hp_() const { return hp; }
private:
	std::vector<Bullet*> p_bullet_list_;
	float x_speed_;
	float y_speed_;

	float x_pos_;
	float y_pos_;

	int width_frame_;
	int height_frame_;

	int map_x_;
	int map_y_;

	SDL_Rect frame_clip_[4];
	//SDL_Rect* frame_clip_ = new SDL_Rect[4];

	Input input_type_;
	int frame_; // luu chi so frame la 1 hay 2 hay 3
	int status_; // trang thai tien hoac lui

	int hp;
};
#endif // !MAIN_OBJECT_H_