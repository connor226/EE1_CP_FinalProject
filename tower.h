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
	friend class enemy;
        tower(int num_x, int num_y, int kind) :x(num_x*80), y(num_y*80), width(80), height(80), theta(0), lock(false), locked_enemy(NULL);
        {
	    type = kind;
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
        `   case 2:
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
        `   case 5:
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
        `   case 8:
                atk = 5;
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
	    if(kind<6)
	    {
   		if(lock)
                {
                    calculated_theta = (atan2(y-monster->y,x->monster-x))*180/3.14159;
                    theta = int(calculated_theta/11.25);
		}
               
	    }
            else
	    {
	        theta+= 1;
		if(theta>7)theta-=8;
            }
        }
	int theta;
	int type;
	SDL_Rect quad={0,0,80,80};
    private:
        int x,y;
        int atk;
        int range;
        int t;
	double calculated_theta;
        int omega;
        int cooltime;
        int width;
        int height;
        bool lock;
        enemy* locked_enemy;
};
