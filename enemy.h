#ifndef INC_BITS_H
#define INC_BITS_H
#include <bits/stdc++.h>
#endif

#ifndef INC_SDL_H
#define INC_SDL_H
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#endif


using namespace std;
typedef pair<int,int> pii;

const int RIGHT = 0;
const int LEFT = 1;
const int UP = 2;
const int DOWN = 3;
const char *Light_Soldier_path = "./pictures/Light_soldier.png";
const char *Heavy_Soldier_path = "./pictures/Heavy_Soldier.png";
const char *Light_Tank_path = "./pictures/Light_Tank.png";
const char *Heavy_Tank_path = "./pictures/Heavy_Tank.png";

#define X first
#define Y second

pii DIR[4] = {{0, 1}, {0, -1}, {-1, 0}, {1, 0}};

pii operator +(const pii &p1, const pii &p2){
	return {p1.X + p2.X, p1.Y + p2.Y};
}

pii operator -(const pii &p1, const pii &p2){
	return {p1.X - p2.X, p1.Y - p2.Y};
}

bool check(pii p){
	return (p.X >= 0 && p.X < 18 && p.Y >= 0 && p.Y < 18);
}

class val{
	public:
		pii pos;
		vector<pair<int, int> > shortest_path;
};

class ENEMY{
	public:
		bool CanFly;
		int hp, speed, dir, money;
		pii pos;
//		SDL_Texture *pic;
//		SDL_Rect rect;
		ENEMY(int type){
			switch(type){
				case 1:{  //Light_Soldier
					hp = 75;
					speed = 4;
					money = 2;
					break;
				}
				case 2:{  //Heavy_Soldier
					hp = 100;
					speed = 2;
					money = 1;
					break;
				}
				case 3:{  //Light_Tank
					hp = 150;
					speed = 1;
					money = 5;
					break;
				}
				case 4:{  //Heavy_Tank
					hp = 200;
					speed = 1;
					money = 10;
					break;
				}
			}
			rect.w = 80;
			rect.h = 80;
			CanFly = false;
			dir = RIGHT;
		}
		bool FindPath(){  //return false if there isn't any path
			queue<val> q;
			bool visited[18][10] = {}, exist_path = false;
			val start, path;
			start.pos = pos;
			start.shortest_path.push_back(pos);
			q.push(start);
			visited[pos.X][pos.Y] = true;
			while(!q.empty()){
				path = q.front();
				q.pop();
				if(path.pos == make_pair(17, 5)){
					exist_path = true;
					break;
				}
				for(int i = 0; i < 4; i++){
					if(check(pos + DIR[i]) && !visited[pos.X + DIR[i].X][pos.Y + DIR[i].Y]){
						visited[pos.X + DIR[i].X][pos.Y + DIR[i].Y] = true;
						val tmp = path;
						tmp.pos = path.pos + DIR[i];
						tmp.shortest_path.push_back(tmp.pos);
						q.push(tmp);
					}
				}
			}
			if(!exist_path)  return false;
			else{
				if(path.shortest_path.size() > 1){
					if(path.shortest_path[1].pos - pos == DIR[RIGHT]){
						rect.x += speed;
					}
					if(path.shortest_path[1].pos - pos == DIR[LEFT]){
						rect.x -= speed;
					}
					if(path.shortest_path[1].pos - pos == DIR[UP]){
						rect.y -= speed;
					}
					if(path.shortest_path[1].pos - pos == DIR[DOWN]){
						rect.x += speed;
					}
					
				}
				else{
					/*
						*****TODO*****
						an enemy reaches the exit here!!!
						maybe we should call a function here to remove this enemy,
						and then minus one point from the base's hp
					*/
				}
				return true;
			}
		}
};

vector<ENEMY*> enemy;
