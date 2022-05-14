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
#include "Collision.h"
#include "TextObject.h"
#include "items.h"
#include <time.h>
#include <stdlib.h>

BaseObject g_background;
TTF_Font *menu_font = NULL;

bool InitData()
{
    bool success = true;
    int ret = SDL_Init(SDL_INIT_VIDEO);
    if (ret < 0)
    {
        return false;
    }
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
    g_window = SDL_CreateWindow("Arena Of Archer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_RESIZABLE);

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

        //font init

        if (TTF_Init() == -1)
        {
            success = false;
        }
        else
        {
            menu_font = TTF_OpenFont("font/ancient_modern_tales.ttf", 20);
            if (menu_font == NULL)
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

int g_level = 1;
int num_enemy = 1;
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

    Timer time_shoot;
    GameMap game_map;
    char map01[30] = "map/map02.dat";
    game_map.LoadMap(map01);
    game_map.LoadTiles(g_screen);

    Mouse mouse;

    Player p_player;
    p_player.LoadImage("img/player_right.png", g_screen);
    p_player.Main_Set_clip();
    p_player.set_damage(10);


    std::vector<Enemy*> Enemy_List = MakeEnemyList(num_enemy);
    for (int i = 0; i < Enemy_List.size(); i++)
    {
        Enemy_List[i]->LoadImage("img/player_down.png", g_screen);
        Enemy_List[i]->Make_Animation();
        Enemy_List[i]->LoadBullet(g_screen);
        Enemy_List[i]->set_damage(5);
    }
   
    std::vector<Items*> items_list;
    int e_damage = 5;
    int E_MAX_HP_ = 20;

    Explosion explosion=Explosion();
    explosion.LoadImage("img/explosion.png", g_screen);

    SDL_Rect rect;
    rect.x = 0;
    rect.y = 0;
    rect.h = 30;
    rect.w = 204;

    SDL_Rect HP = { 2,2,200,26 };

    
    int time_per_shoot=0;
    int time_shoot_start=0;

    bool isquit = false;



    while (!isquit)
    {
        fps_time.start();
        time_shoot.start();
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

		//map
		Map map_data = game_map.GetMap();

		p_player.SetMapXY(map_data.start_x_, map_data.start_y_);
		p_player.DoPlayer(map_data);	
		
		game_map.SetMap(map_data);
		game_map.DrawMap(g_screen);
		//



		mouse.update();
        
        if (num_enemy == 0) {
            g_level++;
            num_enemy = g_level;
            e_damage += 2;
            Enemy_List = MakeEnemyList(num_enemy); for (int i = 0; i < Enemy_List.size(); i++)
            {
                Enemy_List[i]->LoadImage("img/player_down.png", g_screen);
                Enemy_List[i]->Make_Animation();
                Enemy_List[i]->LoadBullet(g_screen);
                Enemy_List[i]->set_damage(e_damage);
                E_MAX_HP_ += g_level * 5;
                Enemy_List[i]->set_Max_hp(E_MAX_HP_);
            }
        }
       
			
        p_player.HandleBullet(g_screen);
        p_player.Show(g_screen);
        
        for (int i = 0; i < Enemy_List.size(); i++)
        {
                Enemy_List[i]->Make_Action(p_player.GetRect().x, p_player.GetRect().y, g_screen, Enemy_List);

                Enemy_List[i]->Show(g_screen);

                if (Enemy_List[i]->get_bullet_list()[0]->get_is_move() == false) 
                {                                  
                       Enemy_List[i]->SetupBullet(g_screen, p_player.GetRect().x, p_player.GetRect().y);                          
                }

                Enemy_List[i]->HandleBullet(g_screen);

                SDL_Rect player_rect;
                player_rect.x = p_player.GetRect().x;
                player_rect.y = p_player.GetRect().y;
                player_rect.w = p_player.get_width_frame();
                player_rect.h = p_player.get_height_frame();

                if (Collision::AABB(Enemy_List[i]->get_bullet_list()[0]->GetRect(), player_rect)) 
                { 
                    Enemy_List[i]->get_bullet_list()[0]->set_is_move(false); 
                    p_player.set_hp_(p_player.get_hp_() - e_damage);
                    Bullet* p_bullet = Enemy_List[i]->get_bullet_list()[0];
                    for (int k = 0; k < 16; k++)
                    {
                        explosion.Set_Clip();
                        explosion.SetRect(p_bullet->GetRect().x - 32, p_bullet->GetRect().y - 32);
                        explosion.Set_Frame_(k);
                        explosion.Show(g_screen);
                    }
                }
        }
       
        for (int i = 0; i < Enemy_List.size() -1; i++)
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
                if (Collision::AABB(Bullet_Rect, Enemy_Rect)) // Neu dan ban trung
                {
                    for (int k = 0; k < 16; k++)
                    {
                        explosion.Set_Clip();
                        explosion.SetRect(p_bullet->GetRect().x-32, p_bullet->GetRect().y-32);
                        explosion.Set_Frame_(k);
                        explosion.Show(g_screen);
                    }
                    Enemy_List[j]->set_hp(Enemy_List[j]->get_hp() - p_player.get_damage());
                    p_player.Free_Bullet(i); // Xoa vien dan
                    
                }

            }
            
        }
        for (int i=0;i<Enemy_List.size(); i++)
            if (Enemy_List[i]->get_hp() == 0)
            {
                srand(time(0));
                int des = rand() % 100;
                if (des %2== 0)
                {
                    Items* item = new Items();
                    item->SetRect(Enemy_List[i]->GetRect().x, Enemy_List[i]->GetRect().y);
                    items_list.push_back(item);
                }
                if (num_enemy>=1) num_enemy--;
                Enemy* e_clone = Enemy_List[i];
                    e_clone->Free();
                    e_clone = NULL;
                    Enemy_List.erase(Enemy_List.begin()+i);
                    delete e_clone;

                    
            }

        for (int i = 0; i < items_list.size(); i++)
        {
            items_list[i]->show(g_screen);
            SDL_Rect item_clone = items_list[i]->GetRect();
            SDL_Rect player_rect;
            player_rect.x = p_player.GetRect().x;
            player_rect.y = p_player.GetRect().y;
            player_rect.w = p_player.get_width_frame();
            player_rect.h = p_player.get_height_frame();
            if (Collision::AABB(item_clone, player_rect)|| items_list[i]->get_real_time() - items_list[i]->get_t_start() >= 5000)
            {
                Items* clone = items_list[i];
                clone->Free();
                items_list.erase(items_list.begin() + i);
                if (Collision::AABB(item_clone, player_rect))
                {

                    if (p_player.get_hp_() + 10 < 100)
                    {
                        p_player.set_hp_(p_player.get_hp_() + 10);
                    }
                    else p_player.set_hp_(100);
                }
                clone = NULL;
                delete clone;
            }
        }


		// check enemy collision
		for (int i = 0;i < Enemy_List.size(); i++)
		{
			for (int j = i;j < Enemy_List.size(); j++)
			{
				if (Collision::AABB(Enemy_List[i]->GetRect(), Enemy_List[j]->GetRect()))
				{
					if (Collision::Distance(Enemy_List[i]->GetRect(), p_player.GetRect()) > Collision::Distance(Enemy_List[j]->GetRect(), p_player.GetRect()))
					{
						Enemy_List[i]->set_x_speed(0);
						Enemy_List[i]->set_y_speed(0);
					}
					else
					{
						Enemy_List[j]->set_x_speed(0);
						Enemy_List[j]->set_y_speed(0);
					}
				}
			}

		}
		//


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
