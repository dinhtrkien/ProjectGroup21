#pragma once
#ifndef MAIN_OBJECT_H_
#define MAIN_OBJECT_H_

#include "commonfunc.h"
#include "BaseObject.h"

#define PLAYER_SPEED 5

class MainObject : public BaseObject
{
public:
	MainObject();
	~MainObject();

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
	void DoPlayer(Map& map_data);
	void CheckToMap(Map& map_data);
	void SetMapXY(const int map_x, const int map_y)
	{
		map_x_ = map_x;
		map_y_ = map_y;
	}
	void CenterEntityOnMap(Map& map_data);
private:
	float x_val_;
	float y_val_;

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

};
#endif // !MAIN_OBJECT_H_