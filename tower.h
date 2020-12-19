#include"SDL.h"
#include"enemy"
#include"final/const.h"
#include<cmath>
#define PI 3.14159265
#ifndef TOWER_H
#define TOWER_H
#endif
class tower{
    public:
        tower(int x, int y, int kind) :x(x), y(y), width(80), height(80), theta(0), lock(false), locked_enemy(NULL);
        {
            t = SDL_GetTicks();
            switch (kind){
            case 1:
                pic = tower1;
                atk = 5;
                cooltime = 1;
                range = 10;
                break;
            case 2:
                pic = tower2;
                atk = 5;
                cooltime = 1;
                range = 10;
                break;
        `   case 3:
                pic = tower3;
                atk = 5;
                cooltime = 1;
                range = 10;
                break;
            default:
                break;
            }
        }
        bool ableatk(int t_c)
        {
            if (t_c - t>cooltime)
            {
                t = t_c;
                return true;
            }
            else
            {
                false;
            }
        }
        bool inrange(enemy* monster)
        {
            if (pow((monster->x - x), 2) + pow((monster->y - y), 2) > pow(range, 2))
            {
                lock = true;
                locked_enemy = monster;
                return true;
            }
            else
            {
                false;
            }
        }
        void rotate()
        {
            if(lock)
            {
                theta = atan2(monster->x-x,y-moster->y);
            }
        }
    private:
        int x,y;
        int atk;
        int range;
        int t;
        int theta;
        int omega;
        int cooltime;
        int width;
        int height;
        bool lock;
        enemy* locked_enemy;
        SDL_Texture* pic;
};
