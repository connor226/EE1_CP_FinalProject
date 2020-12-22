#include"tower.h"
class bullet
{
    public:
	friend class tower;
	bullet(tower* tower1, enemy enemy1):
	{
	    speed = 50;
	    atk = tower->atk;
	    x = tower1->x;
	    y = tower1->y;
	    v_x = (enemy1.x-tower1,x)/speed;
	    v_y = (enemy1.y-tower1.y)/speed;
	}
	void move()
	{
  	    x_e += v_x;
	    y_e += v_y;
	    x = int(x_e);
	    y = int(y_e);
	}
	bool touch(enemy enemy1)
	{
	    if((enemy1.x-x))
	}
	int x,y,speed,atk;
    private:
	double x_e,y_e,v_x,v_y;
}

