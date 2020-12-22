#include"tower.h"
#include"enemy.h"
#include<cmath>
class bullet
{
    public:
	friend class tower;
	bullet(tower* tower1, enemy* enemy1):
	{
	    kind = tower1->kind;
	    speed = 50;
	    atk = tower->atk;
	    x = tower1->x;
	    y = tower1->y;
	    quad.x = x;
	    quad.y = y;
	    v_x = (enemy1->x-tower1->x)/speed;
	    v_y = (enemy1->y-tower1->y)/speed;
	}
	void move()
	{
  	    x_e += v_x;
	    y_e += v_y;
	    x = int(x_e);
	    y = int(y_e);
	}
	bool touch(enemy* enemy1)
	{
	    if(pow(enemy1.x-x,2)+pow(enemy1->y-y,2)<3600)
	    {
    		return true;
	    }
	    else
	    {
		return false;
	    }

		
	}
	SDL_Rect quad = {0,0,80,80};
	int x,y,speed,atk,kind;
    private:
	double x_e,y_e,v_x,v_y;
}
