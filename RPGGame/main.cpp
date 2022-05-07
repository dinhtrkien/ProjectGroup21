#include <Windows.h>
#include <vector>
#include "commonfunc.h"
#include "BaseObject.h"
#include "player.h"
#include "game_map.h"
#include "timer.h"
#include "mouse.h"
#include "enemy.h"
#include "explosion.h"

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

bool CheckBulletOnTarget(const SDL_Rect &a, const SDL_Rect &b) // Kiem tra xem dan a co ban trung b hay khong
{
    int max_range = sqrt(pow(b.h, 2) + pow(b.w, 2)) / 2;
    if (sqrt(pow(a.x+6 - b.x-32, 2) + pow(a.y+6 - b.y-32, 2)) < max_range) return true; else return false;
}

int Distance(const SDL_Rect& a, const SDL_Rect& b)
{
    return int (sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2)));
}

std::vector<Enemy*> MakeEnemyList(const int& n)
{
    std::vector<Enemy*> a;
    for (int i = 0; i < n; i++)
    {
        Enemy* e_clone = new Enemy();
        a.push_back(e_clone);
    }
    return a;
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

    Mouse mouse;

    Player p_player;
    p_player.LoadImage("img/player_right.png", g_screen);
    p_player.Main_Set_clip();

    std::vector<Enemy*> Enemy_List = MakeEnemyList(3);
    for (int i = 0; i < Enemy_List.size(); i++)
    {
        Enemy_List[i]->LoadImage("img/player_down.png", g_screen);
        Enemy_List[i]->Make_Animation();
        Enemy_List[i]->LoadBullet(g_screen);
    }

    Explosion explosion=Explosion();
    explosion.LoadImage("img/explosion.png", g_screen);

    SDL_Rect rect;
    rect.x = 0;
    rect.y = 0;
    rect.h = 30;
    rect.w = 204;

    SDL_Rect HP = { 2,2,200,26 };

    

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
       
        SDL_SetRenderDrawColor(g_screen, 0, 0, 0, 0);
        SDL_RenderClear(g_screen);
        g_background.Render(g_screen, NULL);

        

        game_map.DrawMap(g_screen);

        mouse.update();
        

       
        p_player.HandleBullet(g_screen);
        p_player.Show(g_screen);
        
        for (int i = 0; i < Enemy_List.size(); i++)
        {
                Enemy_List[i]->Make_Action(p_player.GetRect().x, p_player.GetRect().y, g_screen, Enemy_List);

                Enemy_List[i]->Show(g_screen);

               if (Enemy_List[i]->get_bullet_list()[0]->get_is_move()==false) Enemy_List[i]->SetupBullet(g_screen, p_player.GetRect().x, p_player.GetRect().y);

                Enemy_List[i]->HandleBullet(g_screen);

                if (CheckBulletOnTarget(Enemy_List[i]->get_bullet_list()[0]->GetRect(), p_player.GetRect())) 
                { 
                    Enemy_List[i]->get_bullet_list()[0]->set_is_move(false); 

                    p_player.set_hp_(p_player.get_hp_() - 5);
                }
        }
       
        for (int i = 0; i < Enemy_List.size()-1; i++)
        {
            for (int j = i + 1; j < Enemy_List.size(); j++)
            {
                while (sqrt(pow(Enemy_List[i]->GetRect().x - Enemy_List[j]->GetRect().x, 2) + pow(Enemy_List[i]->GetRect().x - Enemy_List[j]->GetRect().x, 2)) < 100)
                {
                    Enemy_List[i]->SetRect(Enemy_List[i]->GetRect().x+8 , Enemy_List[i]->GetRect().y+0);
                }
            }
        }
        
        

        std::vector<Bullet*> bullet_list = p_player.get_bullet_list();

        for (int i = 0; i < bullet_list.size(); i++)
        {
            Bullet* p_bullet = bullet_list[i];
            for (int j = 0; j < Enemy_List.size(); j++)
            {
                Enemy* e_clone = Enemy_List[j];
                SDL_Rect Bullet_Rect = bullet_list[i]->GetRect();
                SDL_Rect Enemy_Rect;
                Enemy_Rect.x = e_clone->GetRect().x;
                Enemy_Rect.y = e_clone->GetRect().y;
                Enemy_Rect.w = e_clone->get_width_frame();
                Enemy_Rect.h = e_clone->get_height_frame();
                if (CheckBulletOnTarget(Bullet_Rect, Enemy_Rect)) // Neu dan ban trung
                {
                    for (int k = 0; k < 16; k++)
                    {
                        explosion.Set_Clip();
                        explosion.SetRect(p_bullet->GetRect().x, p_bullet->GetRect().y);
                        explosion.Set_Frame_(k);
                        explosion.Show(g_screen);
                    }
                    Enemy_List[j]->set_hp(Enemy_List[j]->get_hp() - 10);
                    p_player.Free_Bullet(i); // Xoa vien dan
                    
                }
                if (Enemy_List[j]->get_hp() == 0)
                {
                    
                    e_clone->Free();
                    Enemy_List.erase(Enemy_List.begin() + j);
                   
                }

            }
            
        }

        if (Enemy_List.size() == 0) isquit = true;
        mouse.DrawMouse(g_screen);

        SDL_RenderDrawRect(g_screen, &rect);
        SDL_SetRenderDrawColor(g_screen, 255, 0, 0, 0);
        HP.w = p_player.get_hp_() * 2;
        SDL_RenderFillRect(g_screen, &HP);
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