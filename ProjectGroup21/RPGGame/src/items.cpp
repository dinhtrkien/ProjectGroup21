#include "items.h"
#include <math.h>

Items::Items()
{
	x_pos_ = 0;
	y_pos_ = 0;
	type = 0;
	t_start=SDL_GetTicks();
}

Items::~Items()
{

}

void Items::show(SDL_Renderer* des)
{
	LoadImage("img/item_hp.png", des);
	Render(des);
}
