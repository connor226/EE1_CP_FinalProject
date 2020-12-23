#ifndef TOWER_H
#define TOWER_H
#include"SDL.h"
#include"ENEMY.h"
//#include"final/const.h"
#include<cmath>
#define PI 3.14159265


class tower{
    public:
	friend class ENEMY;
        tower(int num_x, int num_y, int type) :x(80+num_x*90), y(70+num_y*90), theta(0), lock(false), locked_enemy(NULL)
        {
            kind = type;
            quad.x = x;
            quad.y = y;
            t = SDL_GetTicks();
            switch (kind){
            case 0:
                atk = 5;
                cooltime = 1;
                range = 10;
                break;
            case 1:
                atk = 5;
                cooltime = 1;
                range = 10;
                break;
            case 2:
                atk = 5;
                cooltime = 1;
                range = 10;
                break;
            case 3:
                atk = 5;
                cooltime = 1;
                range = 10;
                break;
            case 4:
                atk = 5;
                cooltime = 1;
                range = 10;
                break;
            case 5:
                atk = 5;
                cooltime = 1;
                range = 10;
                break;
            case 6:
                atk = 5;
                range = 10;
                break;
            case 7:
                atk = 5;
                range = 10;
                break;
            case 8:
                atk = 5;
                range = 10;
                break;
            default:
                break;
            }
        }
        bool ableatk(int t_c){
            if (t_c - t>cooltime){
                t = t_c;
                return true;
            }
            else{
                false;
            }
        }
        bool inrange(ENEMY* monster)//check if enemy is in tower range
        {
            if (pow((monster->pos.first - x), 2) + pow((monster->pos.second - y), 2) > pow(range, 2))
            {
                lock = true;
                locked_enemy = monster;
                return true;
            }
            return false;
        }
        void rotate(){
            if(kind<6)
            {
                if(lock){
                        calculated_theta = (atan2(y-locked_enemy->pos.first,locked_enemy->pos.second-x))*180/3.14159;
                        theta = int(calculated_theta/11.25);
                }  
            }
            else{
                theta+= 1;
                if(theta>7)theta-=8;
            }
        }
	int theta;
	int kind;
	SDL_Rect quad={0,0,90,90};
    int x,y;
    int atk;
    int range;
    int t;
    double calculated_theta;
    int cooltime;
    bool lock;
    ENEMY* locked_enemy;
};
#endif
