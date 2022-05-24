#ifndef ITEMS_H
#define ITEMS_H

#include "commonfunc.h"
#include "BaseObject.h"

class Items :public BaseObject
{
public:

	Items();
	~Items();

	void set_x_pos(const int& _x) { x_pos_ = _x; }
	void set_y_pos(const int& _y) { y_pos_ = _y; }

	int get_x_pos() { return x_pos_; }
	int get_y_pos() { return y_pos_; }

	void set_type(const int& _type) { type = _type; }
	int get_type() { return type; }

	void show(SDL_Renderer* des);

	void set_t_start() { t_start = SDL_GetTicks(); }
	int get_real_time() {
		return SDL_GetTicks();
	}

	int get_t_start() { return t_start; }
private:
	int x_pos_;
	int y_pos_;
	int type; // 1: heal; 2,3,4...:
	int t_start;
};

#endif 
