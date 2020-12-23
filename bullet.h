#ifndef 
#include"tower.h"
#include"enemy.h"
#include<cmath>
class bullet
{
    public:
	friend class tower;
	bullet(tower* tower1, ENEMY* enemy1){
	    kind = tower1->kind%3;
	    speed = 50;
	    atk = tower->atk;
	    x = tower1->x;
	    y = tower1->y;
	    // modify the position of bullet
	    if(kind%3==0){
	    	quad.x = x+22;
	    	quad.y = y+22;
			quad.w = 45;
			quad.h = 45;
	    }
	    else{
			quad.x = x;
			quad.y = y;
			quad.w = 90;
			quad.h = 90;
	    }
	    v_x = (enemy1->pos.first-tower1->x)/speed;
	    v_y = (enemy1->pos.second-tower1->y)/speed;
	    x_e = x;
	    y_e = y;
	}
	void move()
	{
  	    x_e += v_x;
	    y_e += v_y;
	    x = int(x_e);
	    y = int(y_e);
	    if(kind%3==0){
			quad.x = x+22;
			quad.y = y+22;
	    }
	    else{
			quad.x = x;
			quad.y = y;
	    }
	}
	bool touch(ENEMY* enemy1)
	{
		//distance unsure
	    if(pow(enemy1->pos.first-x,2)+pow(enemy1->pos.second-y,2)<3600){
    		return true;
	    }
	    else{
			return false;
	    }	
	}
	SDL_Rect quad = {0,0,80,80};
	int x,y,speed,atk,kind;
	double x_e,y_e,v_x,v_y;
}
