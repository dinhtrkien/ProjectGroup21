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
#include <fstream>
#include "Button.h"
#include "MainMenu.h"
#include "menu.h"

BaseObject g_menu_background;
TTF_Font* g_menu_font = NULL;

bool InitData()
{
    bool success = true;
    int ret = SDL_Init(SDL_INIT_VIDEO);
    if (ret < 0)
    {
        return false;
    }
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
    g_window = SDL_CreateWindow("Arena Of Archer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

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
            g_menu_font = TTF_OpenFont("font/BreathFire.ttf", 30);
            if (g_menu_font == NULL)
            {
                success = false;
            }
        }
    }


    return success;
}

bool LoadBackGround()
{
    bool ret = g_menu_background.LoadImage("img/background.png", g_screen);
    if (ret == false)
        return false;

    return true;
}

void close()
{
    g_menu_background.Free();
    SDL_DestroyRenderer(g_screen);
    g_screen = NULL;
    SDL_DestroyWindow(g_window);
    g_window = NULL;
    IMG_Quit();
    SDL_Quit();
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

    bool is_quit = false;
    bool is_paused = false;
    bool is_new_game = false;
    bool is_continued_game = true;
    bool is_game_over = false;
    bool is_help_menu = false;
    bool is_main_menu = true;

    GameBoard menu;
    
    TextObject text_level;
    TextObject txt;
    TextObject game_score;

    Timer time_shoot;
    GameMap game_map;
    char map01[30] = "map/map02.dat";
    game_map.LoadMap(map01);
    game_map.LoadTiles(g_screen);

    Mouse mouse;

    Player p_player;

    int level = 1;
    int num_enemy = 1;
    int score = 0;
    int high_score = 0;
    std::ifstream in_file("data/game/high_score.dat");
    if (in_file)
    {
        in_file >> high_score;
        in_file.close();
    }
    std::vector<Enemy*> Enemy_List;

    std::vector<Items*> items_list;
    int e_damage = 5;
    int E_MAX_HP_ = 20;

    Explosion explosion = Explosion();
    explosion.LoadImage("img/explosion.png", g_screen);

    SDL_Rect rect;
    rect.x = 0;
    rect.y = 0;
    rect.h = 30;
    rect.w = 204;

    SDL_Rect HP = { 2,2,200,26 };


    bool ingame = false;

    while (!is_quit)
    {
        fps_time.start();
        time_shoot.start();
        while (SDL_PollEvent(&g_event) != 0)
        {
            if (g_event.type == SDL_QUIT)
            {
                is_quit = true;
            }
            p_player.HandleInputAction(g_event, g_screen);
        }
        mouse.Free();
        mouse.update();

        SDL_SetRenderDrawColor(g_screen, 255, 49, 0, 0);
        SDL_RenderClear(g_screen);
        g_menu_background.Render(g_screen, NULL);

        //Main menu
        if (is_main_menu)
        {
            menu.RenderMainMenu(g_screen, g_menu_font);

            //mouse over button handling

            if (menu.mainmenu_play.MouseOver(g_event, mouse))
            {
                menu.mainmenu_play.SetButtonColor(255, 0, 0);
            }
            else
            {
                menu.mainmenu_play.SetButtonColor(0, 0, 0);
            }

            if (menu.mainmenu_continue.MouseOver(g_event, mouse))
            {
                menu.mainmenu_continue.SetButtonColor(255, 0, 0);
            }
            else
            {
                menu.mainmenu_continue.SetButtonColor(0, 0, 0);
            }

            if (menu.mainmenu_exit.MouseOver(g_event, mouse))
            {
                menu.mainmenu_exit.SetButtonColor(255, 0, 0);
            }
            else
            {
                menu.mainmenu_exit.SetButtonColor(0, 0, 0);
            }

            if (menu.mainmenu_help.MouseOver(g_event, mouse))
            {
                menu.mainmenu_help.SetButtonColor(255, 0, 0);
            }
            else
            {
                menu.mainmenu_help.SetButtonColor(0, 0, 0);
            }

            //Button clicked handling
            if (menu.mainmenu_play.OnClick(g_event, mouse))
            {
                is_main_menu = false;
                is_new_game = true;
                ingame = true;
                is_continued_game = false;
                is_paused = false;
                is_game_over = false;
                is_help_menu = false;
            }

            if (menu.mainmenu_continue.OnClick(g_event, mouse))
            {
                std::ifstream file("data/game/state.dat");
                int check;
                file >> check;
                if (check == 1)
                {
                    is_main_menu = false;
                    ingame = true;
                    is_continued_game = true;
                    is_new_game = false;
                    is_paused = false;
                    is_game_over = false;
                    is_help_menu = false;
                    file.close();
                }
            }

            if (menu.mainmenu_exit.OnClick(g_event, mouse))
            {
                is_quit = true;
            }

            if (menu.mainmenu_help.OnClick(g_event, mouse))
            {
                is_main_menu = false;
                is_help_menu = true;
            }
        }

        //help menu
        if (is_help_menu)
        {
            menu.MainMenuFree();
            menu.RenderHelpMenu(g_screen, g_menu_font, "img/instruction.png");

            if (menu.help_backtomain.MouseOver(g_event, mouse))
            {
                menu.help_backtomain.SetButtonColor(255, 0, 0);
            }
            else
            {
                menu.help_backtomain.SetButtonColor(0, 0, 0);
            }

            if (menu.help_backtomain.OnClick(g_event, mouse))
            {
                is_main_menu = true;
                is_help_menu = false;
                menu.HelpMenuFree();
            }
        }

        // Game Over Menu
        if (is_game_over)
        {
            menu.RenderGameOver(g_screen, g_menu_font, score, high_score);

            //Mouse over handling
            if (menu.gameover_exit.MouseOver(g_event, mouse))
            {
                menu.gameover_exit.SetButtonColor(255, 0, 0);
            }
            else
            {
                menu.gameover_exit.SetButtonColor(0, 0, 0);
            }

            if (menu.gameover_backtomain.MouseOver(g_event, mouse))
            {
                menu.gameover_backtomain.SetButtonColor(255, 0, 0);
            }
            else
            {
                menu.gameover_backtomain.SetButtonColor(0, 0, 0);
            }

            //Button clicked handling
            if (menu.gameover_exit.OnClick(g_event, mouse))
            {
                is_quit = true;
            }

            if (menu.gameover_backtomain.OnClick(g_event, mouse))
            {
                is_main_menu = true;
                is_paused = false;
                ingame = false;
                is_continued_game = false;
                is_game_over = false;
                menu.GameOverFree();
                std::ofstream file("data/game/state.dat");
                if (file)
                {
                    file << 0;
                }
                file.close();
            }
        }

        //Game Paused menu
        if (!is_game_over && is_paused)
        {
            menu.RenderGamePaused(g_screen, g_menu_font);

            //Mouse over handling

            if (menu.gamepaused_exit.MouseOver(g_event, mouse))
            {
                menu.gamepaused_exit.SetButtonColor(255, 0, 0);
            } 
            else
            {
                menu.gamepaused_exit.SetButtonColor(0, 0, 0);
            }

            if (menu.gamepaused_resume.MouseOver(g_event, mouse))
            {
                menu.gamepaused_resume.SetButtonColor(255, 0, 0);
            }
            else
            {
                menu.gamepaused_resume.SetButtonColor(0, 0, 0);
            }

            if (menu.gamepaused_backtomain.MouseOver(g_event, mouse))
            {
                menu.gamepaused_backtomain.SetButtonColor(255, 0, 0);
            }
            else
            {
                menu.gamepaused_backtomain.SetButtonColor(0, 0, 0);
            }

            //Button clicked handling

            if (menu.gamepaused_exit.OnClick(g_event, mouse))
            {
                is_quit = true;
            }

            if (menu.gamepaused_resume.OnClick(g_event, mouse))
            {
                ingame = true;
                is_paused = false;
                menu.GamePausedFree();
            }

            if (menu.gamepaused_backtomain.OnClick(g_event, mouse))
            {
                is_main_menu = true;
                is_paused = false;
                ingame = false;
                is_continued_game = false;
                is_game_over = false;
                menu.GamePausedFree();
            }
        }


        //Gameplay
        if ((!is_paused) && (ingame))
        {
            // press esc to pause game
            if (g_event.type == SDL_KEYDOWN)
            {
                if (g_event.key.keysym.sym == SDLK_ESCAPE)
                {
                    is_paused = true;
                }
            }
            game_map.DrawMap(g_screen);

            Map map_data = game_map.GetMap();

            p_player.CheckMapCollision(map_data);

            game_map.DrawMap(g_screen);
            if (is_new_game)
            {
                level = 1;
                e_damage = 5;
                E_MAX_HP_ = 20;
                p_player.Free();
                p_player = Player();
                p_player.LoadImage("img/player_down.png", g_screen);
                p_player.Main_Set_clip();
                p_player.set_damage(10);
                score = 0;
                std::ifstream infile("data/game/high_score.dat");
                if (infile)
                {
                    infile >> high_score;
                    infile.close();
                }
                for (int i = 0; i < Enemy_List.size(); i++)
                {
                    Enemy* e_clone = Enemy_List[i];
                    e_clone->Free();
                    e_clone = NULL;
                    Enemy_List.erase(Enemy_List.begin() + i);
                    delete e_clone;
                }
                num_enemy = 1;
                Enemy_List = MakeEnemyList(num_enemy);
                for (int i = 0; i < Enemy_List.size(); i++)
                {
                    Enemy_List[i]->LoadImage("img/enemy_down.png", g_screen);
                    Enemy_List[i]->Make_Animation();
                    Enemy_List[i]->LoadBullet(g_screen);
                    Enemy_List[i]->set_damage(e_damage);
                    Enemy_List[i]->set_Max_hp(E_MAX_HP_);
                }
                is_new_game = false;
            }

            if (is_continued_game)
            {
                p_player.LoadImage("img/player_right.png", g_screen);
                p_player.Main_Set_clip();
                p_player.set_damage(10);
                std::ifstream infile("data/player/player.dat");
                if (infile)
                {
                    int a;
                    infile >> a;
                    infile >> a;
                    infile >> a;
                    p_player.set_x_pos(a);
                    infile >> a;
                    p_player.set_y_pos(a);
                    infile >> a;
                    infile >> a;
                    p_player.set_hp_(a);
                    infile >> a;
                    p_player.set_damage(a);
                    infile.close();
                }

                infile.open("data/game/game.dat");
                if (infile)
                {
                    infile >> level;
                    infile >> num_enemy;
                    infile >> score;
                    infile.close();
                }
                infile.open("data/game/high_score.dat");
                if (infile)
                {
                    infile >> high_score;
                    infile.close();
                }
                Enemy_List = MakeEnemyList(num_enemy);
                for (int i = 0; i < Enemy_List.size(); i++)
                {
                    Enemy_List[i]->LoadImage("img/enemy_down.png", g_screen);
                    Enemy_List[i]->Make_Animation();
                    Enemy_List[i]->LoadBullet(g_screen);
                    Enemy_List[i]->set_damage(5);
                }
                for (int i = 0; i < num_enemy; i++)
                {
                    infile.open("data/Enemy/enemy_" + std::to_string(i) + ".dat");
                    if (infile)
                    {
                        int a;
                        infile >> a;
                        infile >> a;
                        infile >> a;
                        Enemy_List[i]->set_x_pos(a);
                        infile >> a;
                        Enemy_List[i]->set_y_pos(a);
                        infile >> a;
                        infile >> a;
                        Enemy_List[i]->set_hp(a);
                        infile >> a;
                        Enemy_List[i]->set_Max_hp(a);
                        infile >> a;
                        Enemy_List[i]->set_damage(a);
                        infile.close();
                    }
                }
                is_continued_game = false;
            }
            // Ket thuc mot man choi khi so ke thu = 0
            if (num_enemy == 0) {
                level++;
                num_enemy = level;
                e_damage += 2;
                Enemy_List = MakeEnemyList(num_enemy); for (int i = 0; i < Enemy_List.size(); i++) // Tao list ke thu moi
                {
                    Enemy_List[i]->LoadImage("img/enemy_down.png", g_screen);
                    Enemy_List[i]->Make_Animation();
                    Enemy_List[i]->LoadBullet(g_screen);
                    Enemy_List[i]->set_damage(e_damage);
                    E_MAX_HP_ += level * 5;
                    Enemy_List[i]->set_Max_hp(E_MAX_HP_);
                }
            }

            p_player.HandleBullet(g_screen);
            p_player.Show(g_screen);

            for (int i = 0; i < Enemy_List.size(); i++)
            {


                Enemy_List[i]->Make_Action(p_player.GetRect().x, p_player.GetRect().y, g_screen, Enemy_List);

				Enemy_List[i]->CheckMapCollision(map_data);

                Enemy_List[i]->Show(g_screen);

                if (Enemy_List[i]->get_bullet_list()[0]->get_is_move() == false)
                {
                    Enemy_List[i]->SetupBullet(g_screen, p_player.GetRect().x, p_player.GetRect().y);
                }

                Enemy_List[i]->HandleBullet(g_screen);
                if (Enemy_List[i]->get_bullet_list()[0]->CheckMapCollision(map_data))
                {
                    Bullet* p_bullet = Enemy_List[i]->get_bullet_list()[0];
                    explosion.SetRect(p_bullet->GetRect().x, p_bullet->GetRect().y);
                    for (int k = 0; k < 4; k++)
                    {
                        explosion.Set_Clip();
                        explosion.Set_Frame_(k);
                        explosion.set_angle(p_bullet->get_direct_angle());
                        explosion.Show(g_screen);
                    }
                }

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
                    explosion.SetRect(p_bullet->GetRect().x, p_bullet->GetRect().y);
                    for (int k = 0; k < 4; k++)
                    {
                        explosion.Set_Clip();
                        explosion.Set_Frame_(k);
                        explosion.set_angle(p_bullet->get_direct_angle());
                        explosion.Show(g_screen);
                    }
                }
            }

            for (int i = 0; i < Enemy_List.size(); i++)
            {
                for (int j = i; j < Enemy_List.size(); j++)
                {
                    SDL_Rect rect1 = Enemy_List[i]->GetRect();
                    rect1.w = Enemy_List[i]->get_width_frame();
                    rect1.h = Enemy_List[i]->get_height_frame();

                    SDL_Rect rect2 = Enemy_List[j]->GetRect();
                    rect2.w = Enemy_List[j]->get_width_frame();
                    rect2.h = Enemy_List[j]->get_height_frame();

                    if (Collision::AABB(rect1, rect2))
                    {
                        Enemy_List[i]->SetRect(rect1.x - Enemy_List[i]->get_x_speed(), rect1.y - Enemy_List[i]->get_y_speed());
                        Enemy_List[j]->SetRect(rect2.x - Enemy_List[j]->get_x_speed(), rect2.y - Enemy_List[j]->get_y_speed());
                        if (Collision::Distance(rect1, p_player.GetRect()) > Collision::Distance(rect2, p_player.GetRect()))
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

            std::vector<Bullet*> bullet_list = p_player.get_bullet_list();

            for (int i = 0; i < bullet_list.size(); i++)
            {
                Bullet* p_bullet = bullet_list[i];
              
                if (p_bullet->CheckMapCollision(map_data))
                {
                    explosion.SetRect(p_bullet->GetRect().x, p_bullet->GetRect().y);
                    for (int k = 0; k < 4; k++)
                    {
                        explosion.Set_Clip();
                        explosion.Set_Frame_(k);
                        explosion.set_angle(p_bullet->get_direct_angle());
                        explosion.Show(g_screen);
                    }
                    p_player.Free_Bullet(i);
                }
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
                        explosion.SetRect(p_bullet->GetRect().x, p_bullet->GetRect().y);
                        for (int k = 0; k < 4; k++)
                        {
                            explosion.Set_Clip();
                            explosion.Set_Frame_(k);
                            explosion.set_angle(p_bullet->get_direct_angle());
                            explosion.Show(g_screen);
                        }
                        Enemy_List[j]->set_hp(Enemy_List[j]->get_hp() - p_player.get_damage());
                        
                        p_player.Free_Bullet(i); //Xoa vien dan
                    }

                }

            }

            for (int i = 0; i < Enemy_List.size(); i++)
            {
                if (Enemy_List[i]->get_hp() == 0)
                {
                    srand(time(0));
                    int des = rand() % 100;
                    if (des % 2 == 0)
                    {
                        Items* item = new Items();
                        item->SetRect(Enemy_List[i]->GetRect().x, Enemy_List[i]->GetRect().y);
                        items_list.push_back(item);
                    }
                    if (num_enemy >= 1) num_enemy--;
                    Enemy* e_clone = Enemy_List[i];
                    e_clone->Free();
                    e_clone = NULL;
                    Enemy_List.erase(Enemy_List.begin() + i);
                    delete e_clone;
                    score++;
                }
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
                if (Collision::AABB(item_clone, player_rect) || items_list[i]->get_real_time() - items_list[i]->get_t_start() >= 5000)
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
                    delete clone;
                    clone = NULL;
                }
            }

            //hien thi level
            text_level.SetText("LEVEL: " + std::to_string(level));
            text_level.LoadFromRenderText(g_menu_font, g_screen);
            text_level.SetTextColor(255, 0, 0);
            text_level.RenderText(g_screen, 450, 10, NULL);

            //hien thi score 
            game_score.SetText("YOUR SCORE: " + std::to_string(score));
            game_score.LoadFromRenderText(g_menu_font, g_screen);
            game_score.SetTextColor(255, 0, 0);
            game_score.RenderText(g_screen, 800, 10, NULL);

            //hien thi thanh mau
            SDL_RenderDrawRect(g_screen, &rect);
            SDL_SetRenderDrawColor(g_screen, 255, 0, 0, 0);
            HP.w = p_player.get_hp_() * 2;
            SDL_RenderFillRect(g_screen, &HP);

            //save file
            p_player.Export("data/player/player.dat");
            for (int i = 0; i < Enemy_List.size(); i++)
            {
                Enemy_List[i]->Export("data/Enemy/enemy_" + std::to_string(i) + ".dat");
            }

            std::ofstream file("data/game/game.dat");

            if (file)
            {
                file << level << std::endl;
                file << Enemy_List.size() << std::endl;
                file << score << std::endl;
                file.close();
            }
            
            if ((p_player.get_hp_() <= 0) && ingame)
            {
                is_paused = true;
                is_game_over = true;
                if (score > high_score) high_score = score;
                std::ofstream out_file("data/game/high_score.dat");
                if (out_file)
                {
                    out_file << high_score;
                }
            }
            std::ofstream file1("data/game/state.dat");
            if (file)
            {
                if (!is_game_over) file1 << "1"; else file1 << "0";
            }
            file1.close();
        }

        mouse.DrawMouse(g_screen);

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
