#ifndef EXPLOSION_H
#define EXPLOSION_H

#include <Windows.h>
#include "commonfunc.h"
#include "BaseObject.h"

class Explosion :public BaseObject
{
public:
	Explosion();
	~Explosion();
	bool LoadImage(std::string path, SDL_Renderer* screen);
	void Show(SDL_Renderer* des);
	void Set_Clip();
	void Set_Frame_(const int& k) { frame_ = k; }
	void set_angle(const int& k) { angle = k; }
private:
	int frame_;
	int width_frame_;
	int height_frame_;
	SDL_Rect frame_clip_[5];
	int angle;
};
#endif // !EXPLOSION_H
