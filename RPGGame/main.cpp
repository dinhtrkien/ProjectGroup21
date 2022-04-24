#include <Windows.h>
#include "commonfunc.h"
#include "BaseObject.h"
#include "mainObject.h"
#include "game_map.h"
#include "timer.h"

BaseObject g_background;
bool InitData()
{
    bool success = true;
    int ret = SDL_Init(SDL_INIT_VIDEO);
    if (ret < 0)
    {
        return false;
    }
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
    g_window = SDL_CreateWindow("GAME DIT NHAU CUC PHE", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_RESIZABLE);

    if (g_window == NULL)
    {
        success = false;
    }
    else
    {
        g_screen = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
        if (g_screen == NULL) success = false;
        else
        {
            SDL_SetRenderDrawColor(g_screen, 255, 255, 255, 255);
            int imgflags = IMG_INIT_PNG;
            if (!(IMG_Init(imgflags) && imgflags))
            {
                success = false;
            }
        }
    }

    return success;

}

bool LoadBackGround()
{
    bool ret = g_background.LoadImage("img/bg.png", g_screen);
    if (ret == false)
        return false;

    return true;
}

void close()
{
    g_background.Free();
    SDL_DestroyRenderer(g_screen);
    g_screen = NULL;
    SDL_DestroyWindow(g_window);
    g_window = NULL;
    IMG_Quit();
    SDL_Quit();
}

int main(int argc, char* argv[])
{
    Timer fps_time;
    if (InitData() == false)
        return -1;

    if (LoadBackGround() == false)
        return -1;

    GameMap game_map;
    char map01[30] = "map/map02.dat";
    game_map.LoadMap(map01);
    game_map.LoadTiles(g_screen);

    MainObject p_player;
    p_player.LoadImage("img/player_right.png", g_screen);
    p_player.Main_Set_clip();
    bool isquit = false;
    while (!isquit)
    {
        fps_time.start();
        while (SDL_PollEvent(&g_event) != 0)
        {
            if (g_event.type == SDL_QUIT)
            {
                isquit = true;
            }
            p_player.HandleInputAction(g_event, g_screen);
            
        }
       
        SDL_SetRenderDrawColor(g_screen, 255, 255, 255, 255);
        SDL_RenderClear(g_screen);
        g_background.Render(g_screen, NULL);

        

        game_map.DrawMap(g_screen);

        
        p_player.HandleBullet(g_screen);
        p_player.Show(g_screen);

        SDL_RenderPresent(g_screen);
        int real_time = fps_time.get_ticks();
        int time_one_frame = 1000 / FRAME_PER_SECOND;

        if (real_time < time_one_frame)
        {
            int delay_time = time_one_frame - real_time;
            SDL_Delay(delay_time);

        }
    }
    
    close();
    return 0;
}