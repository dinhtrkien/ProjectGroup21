#pragma once
#ifndef MOUSE_H
#define MOUSE_H

#include "commonfunc.h"
#include "BaseObject.h"

class Mouse : public BaseObject
{
public:
	Mouse();
	~Mouse();
	void update(); // lay vi tri cua chuot de render
	void DrawMouse(SDL_Renderer* des); // render hong tam vao vi tri cua con chuot
};

#endif // !MOUSE_H
