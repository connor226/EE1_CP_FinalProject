#ifndef INC_BITS_H
#define INC_BITS_H
#include <bits/stdc++.h>
#endif
/*
#ifndef INC_SDL_H
#define INC_SDL_H
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#endif
*/

using namespace std;
typedef pair<int,int> pii;
const int RIGHT = 0;
const int LEFT = 1;
const int UP = 2;
const int DOWN = 3;

#define X first
#define Y second

pii DIR[4] = {make_pair(0, 1), make_pair(0, -1), make_pair(-1, 0), make_pair(1, 0)};

pii operator +(const pii &p1, const pii &p2){
	return make_pair(p1.X + p2.X, p1.Y + p2.Y);
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
		int hp, speed, dir;
		pii pos;
//		SDL_Texture *pic;
//		SDL_Rect rect;
		ENEMY(int type){
			switch(type){
				case 1:{
					hp = 100;
					speed = 2;
					break;
				}
				case 2: {
					hp = 75;
					speed = 3;
					break;
				}
				case 3: {
					hp = 150;
					speed = 1;
					break;
				}
			}
			CanFly = false;
			dir = RIGHT;
		}
		void FindPath() {
			queue<val> q;
			bool visited[18][10] = {};
			val start, path;
			start.pos = pos;
			start.shortest_path.push_back(pos);
			q.push(start);
			visited[pos.X][pos.Y] = true;
			while(!q.empty()){
				path = q.front();
				q.pop();
				if(path.pos == make_pair(17, 5))  break;
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
		}
};

vector<ENEMY*> enemy;
