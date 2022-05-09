#include "Collision.h"

bool Collision::AABB(const SDL_Rect& recA, const SDL_Rect& recB)
{
    if (recA.x > recB.x && recA.x < recB.x + recB.w)
    {
        if (recA.y > recB.y && recA.y < recB.y + recB.h)
        {
            return true;
        }
    }

    if (recA.x > recB.x && recA.x < recB.x + recB.w)
    {
        if (recA.y + recA.h > recB.y && recA.y + recA.h < recB.y + recB.h)
        {
            return true;
        }
    }

    if (recA.x + recA.w > recB.x && recA.x + recA.w < recB.x + recB.w)
    {
        if (recA.y > recB.y && recA.y < recB.y + recB.h)
        {
            return true;
        }
    }

    if (recA.x + recA.w > recB.x && recA.x + recA.w < recB.x + recB.w)
    {
        if (recA.y + recA.h > recB.y && recA.y + recA.h < recB.y + recB.h)
        {
            return true;
        }
    }

    return false;
}
