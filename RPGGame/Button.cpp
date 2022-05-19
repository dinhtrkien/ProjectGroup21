#include "Button.h"

void Button::Render(SDL_Renderer* des, TTF_Font* p_font)
{
	Content.SetText(text);
	Content.LoadFromRenderText(p_font, des);
	Content.SetTextColor(0, 0, 0);
	Content.RenderText(des, rect_.x, rect_.y, NULL);
}

bool Button::OnClick(SDL_Event events, Mouse clone)
{
	if (Collision::AABB(clone.GetRect(), rect_)&& (events.type == SDL_MOUSEBUTTONDOWN))
	{
			if (events.button.button == SDL_BUTTON_LEFT)
			{
				return true;
			}
	}
	return false;
}

void Button::Free()
{
	background.Free();
	Content.free();
	rect_ = { 0,0,0,0 };
}