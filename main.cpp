#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include"tower.h"
#include<vector>
#include"ENEMY.h"
#include"bullet.h"

using namespace std;

//variable
const int SCREEN_WIDTH = 1800;
const int SCREEN_HEIGHT = 1000;
const int TOWER_WIDTH = 90;

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;

//map's things
SDL_Texture* background;
SDL_Texture* light;
SDL_Texture* slow;
SDL_Texture* rocket;
const SDL_Rect initiallight = { 80,70,90,90 };
const SDL_Rect initialslow = { 1720,820,90,90 };
const SDL_Rect initialrocket = { 1720,730,90,90 };
SDL_Rect lightrect= { 1720,910,80,80 };
SDL_Rect slowrect = { 1720,820,80,80 };
SDL_Rect rocketrect = { 1720,730,80,80 };
SDL_Point mouse_position;

bool point_in_rect(SDL_Point p, const SDL_Rect r)
{
	if ((p.x>r.x)&&(p.x<r.x+r.w)&&(p.y>r.y)&&(p.y<r.y+r.h))
	{
		return true;
	}
	else
	{
		return false;
	}
}
//map

//tower's thing
tower*** towers=new tower**[18];
SDL_Texture* tower_pic[9];
SDL_Rect towerClips[6][32];
SDL_Rect towerClips2[3][8];
for(int j=0;j<6;j++)
{
    for (int i = 0; i < 32; i++)
    {
        towerClips[j][i].x = 70 * (i + 1);
        towerClips[j][i].y = 0;
        towerClips[j][i].w= 70;
        towerClips[j][i].h = 70;
    }
}
for(int j=0;j<3;j++)
{
    for (int i = 0; i < 8; i++)
    {
        towerClips2[j][i].x = 70 * (i + 1);
        towerClips2[j][i].y = 0;
        towerClips2[j][i].w = 70;
        towerClips2[j][i].h = 70;
    }
}	
for(int i=0;i<18;i++)
{
    towers[i] = new tower*[10];
}
for(int i=0;i<18;i++)
{
    for(int j=0;j<10;j++)
    {
	towers[i][j]=NULL;
    }
}
//tower

//bullet's thing
SDL_Texture* bullet_pic[3];
vector<bullet*> bullets;
//bullet

//enemy's things
vector<ENEMY*> enemies;
//enemy

//init
void init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}

		//Create window
		gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Create renderer for window
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
			if (gRenderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}
			}
		}
	}

	//return success;
}
void loadmedia()
{
    SDL_Surface* loadedSurface = IMG_Load("pictures/Light_Gun.png");
    tower_pic[0] = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
    loadedSurface = IMG_Load("pictures/Medium_Gun.png");
    tower_pic[1] = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
    loadedSurface = IMG_Load("pictures/Heavy_Gun.png");
    tower_pic[2] = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
    loadedSurface = IMG_Load("pictures/Light_Rocket_Launcher.pngpng");
    tower_pic[3] = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
    loadedSurface = IMG_Load("pictures/Medium_Rocket_Launcher.png.png");
    tower_pic[4] = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
    loadedSurface = IMG_Load("pictures/Heavy_Rocket_Launcher.png.png");
    tower_pic[5] = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
    loadedSurface = IMG_Load("pictures/Basic_Slow_Tower.png");
    tower_pic[6] = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
    loadedSurface = IMG_Load("pictures/Upgraded_Slow_Tower.png");
    tower_pic[7] = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
    loadedSurface = IMG_Load("pictures/Adavanced_Slow_Tower3.png");
    tower_pic[8] = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
    loadedSurface = IMG_Load("pictures/Light_Gun.png");
    bullet_pic[0] = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
    loadedSurface = IMG_Load("pictures/Medium_Gun.png");
    tower_pic[1] = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
    loadedSurface = IMG_Load("pictures/Heavy_Gun.png");
    tower_pic[2] = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
    loadedSurface = IMG_Load("pictures/Basic_Level_Classic.jpg");
    background = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
    loadedSurface = IMG_Load("pictures/Light_Gun.png");
    light = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
    loadedSurface = IMG_Load("pictures/Slow_Tower.png");
    slow = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
    loadedSurface = IMG_Load("pictures/Light_Rocket_Launcher.png");
    rocket = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
    SDL_FreeSurface(loadedSurface);
}

void close()
{
	//Free loaded images
    for(int i=0;i<9;i++)
    {
        SDL_DestroyTexture(tower_pic[i]);
        tower_pic[i] = NULL;
    }
	SDL_DestroyTexture(light);
	light = NULL;
	SDL_DestroyTexture(slow);
	slow = NULL;
	SDL_DestroyTexture(rocket);
	rocket = NULL;
	SDL_DestroyTexture(background);
	background = NULL;

	//Destroy window	
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}
tower* upgrade(x,y,tower* old)
{
    tower* x = new tower(x,y,old->kind+1);
    return x;
}


int main( int argc, char* args[] )
{
	//Start up SDL and create window
	if( !init() ){
		printf( "Failed to initialize!\n" );
	}
	else{
		//Load media
		if( !loadMedia() ){
			printf( "Failed to load media!\n" );
		}
		else{	
			//Main loop flag
			bool quit = false;
            bool lightflag = false;
			bool slowflag = false;
			bool rocketflag = false;
			//Event handler
			SDL_Event e;

			//While application is running
			while( !quit ){
                SDL_SetTextureBlendMode(light, SDL_BLENDMODE_BLEND);
				SDL_SetTextureAlphaMod(light, 255);
				SDL_SetTextureBlendMode(slow, SDL_BLENDMODE_BLEND);
				SDL_SetTextureAlphaMod(slow, 255);
				SDL_SetTextureBlendMode(rocket, SDL_BLENDMODE_BLEND);
				SDL_SetTextureAlphaMod(rocket, 255);
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(gRenderer);
				SDL_RenderCopy(gRenderer, background, NULL, NULL);
				
				//Handle events on queue
				while( SDL_PollEvent( &e ) != 0 ){
					//User requests quit
					if( e.type == SDL_QUIT ){
						quit = true;
					}
                    if ( e.type == SDL_MOUSEBUTTONDOWN )
					{
						SDL_GetMouseState(& mouse_position.x, &mouse_position.y);
						if (lightflag == true)
						{
							/*
							int p,q
							p=(mouse_position.x-80)/90;
							q=(mouse_position.y-70)/90;
							build the tower on the point (p,q);
							 */
							lightflag = false;
							continue;
						}else if (slowflag == true){
							/*
							 build
							*/
							slowflag = false;
							continue;
						}else if (rocketflag == true){
							/*
							 build
							*/
							rocketflag = false;
							continue;
						}

						if (point_in_rect(mouse_position, initiallight) == true)
						{
							if (lightflag == false)
							{
								lightflag = true;
							}							
						}else if (point_in_rect(mouse_position, initialslow) == true){
							if (slowflag == false)
							{
								slowflag = true;
							}
						}else if (point_in_rect(mouse_position, initialrocket) == true){
							if (rocketflag == false)
							{
								rocketflag = true;
							}
						}
					}

					if (lightflag == true)
					{
						if (e.type == SDL_MOUSEMOTION)
						{
							SDL_GetMouseState(&mouse_position.x, &mouse_position.y);
							lightrect.x = mouse_position.x;
							lightrect.y = mouse_position.y;
							SDL_SetTextureBlendMode(light, SDL_BLENDMODE_BLEND);
							SDL_SetTextureAlphaMod(light, 192); //3/4 transparent
							SDL_RenderCopy(gRenderer, light, NULL, &lightrect);
						}
					}
					if (slowflag == true)
					{
						if (e.type == SDL_MOUSEMOTION)
						{
							SDL_GetMouseState(&mouse_position.x, &mouse_position.y);
							slowrect.x = mouse_position.x;
							slowrect.y = mouse_position.y;
							SDL_SetTextureBlendMode(slow, SDL_BLENDMODE_BLEND);
							SDL_SetTextureAlphaMod(slow, 192);
							SDL_RenderCopy(gRenderer, slow, NULL, &slowrect);
						}
					}
					if (rocketflag == true)
					{
						if (e.type == SDL_MOUSEMOTION)
						{
							SDL_GetMouseState(&mouse_position.x, &mouse_position.y);
							rocketrect.x = mouse_position.x;
							rocketrect.y = mouse_position.y;
							SDL_SetTextureBlendMode(rocket, SDL_BLENDMODE_BLEND);
							SDL_SetTextureAlphaMod(rocket, 192);
							SDL_RenderCopy(gRenderer, rocket, NULL, &rocketrect);
						}
					}
				}
                //unfreeze
                for(int i=0;i<enemies.size();i++){
                    enemies[i]->freeze = false;
                }
                //tower motion
                for(int i=0;i<18;i++){
                    for(int j=0;j<10;j++){
                        if(towers[i][j]!=NULL){
                            //render tower
                            if(towers[i][j]->kind<6){
                                if(towers[i][j]->lock==false){
                                    for(int k=0;k<enemies.size();k++){
                                        if(towers[i][j]->inrange(enemies[k]){
                                            towers[i][j]->rotate();
                                            if(towers[i][j]->ableatk(SDL_GetTicks())){
                                                //make a bullet
                                                bullet* x = new bullet(towers[i][j], towers[i][j]->lock_enemy);
                                                bullets.push_back(x);
                                            }
                                            break;
                                        }
                                    }
                                }
                            }
                            else{
                                if(towers[i][j]->inrange(towers[i][j]->lock_enemy)){
                                    towers[i][j]->rotate();
                                    if(towers[i][j]->ableatk(SDL_GetTicks())){
                                        //make a bullet
                                        bullet* x = new bullet(towers[i][j], towers[i][j]->lock_enemy);
                                        bullets.push_back(x);
                                    }
                                }
                                else{
                                    towers[i][j]->lock=false;
                                    for(int k=0;k<enemies.size();k++){
                                        if(towers[i][j]->inrange(enemies[k]){
                                            towers[i][j]->rotate();
                                            if(towers[i][j]->ableatk(SDL_GetTicks())){
                                            //make a bullet
                                                bullet* x = new bullet(towers[i][j], towers[i][j]->lock_enemy);
                                                bullets.push_back(x);
                                            }
                                            break;
                                        }
                                    }
                                }
                            SDL_RenderCopy(gRender, tower_pic[towers[i][j]->kind], &towerClips[towers[i][j]->theta], &towers[i][j]->quad);
                            }
                        }
                        else{
                            for(int k=0;k<enemies.size();k++){
                                if(towers[i][j]->inrange(enemies[k])
                                {
                                    enemies[k].freeze = towers[i][j]->atk;
                                }
                            }
                            towers[i][j]->rotate();
                            SDL_RenderCopy(gRender, tower_pic[towers[i][j]->kind], &towerClips2[towers[i][j]->theta], &towers[i][j]->quad)
                        } 
                    }
                }
                //bullets motion
                for(int i=bullets.size()-1;i>=0;i--){
                    bullets[i]->move();
		            for(int j=0;j<enemies.size();j++){
		                if(bullets[i]->touch(enemies[j])){
			                enemies[j]->hp -= bullets[i]->atk;//
		                    delete bullets[i];
  			                bullets[i] = NULL;
			                bullets.erase(bullets.begin()+i);
			            break;
			            }
		            }
                }
                for(int i=0;i<bullets.size();i++){
                    SDL_RenderCopy(gRender, bullet_pic[bullets[i]->kind], NULL, &bullets[i]->quad)
                }
                //enemies motion
                //render buttom
                SDL_RenderCopy(gRenderer, light, NULL, &initiallight);
				SDL_RenderCopy(gRenderer, slow, NULL, &initialslow);
				SDL_RenderCopy(gRenderer, rocket, NULL, &initialrocket);
            }
        }
    }
}

//making tower
//towers[i][j] = new tower(x,y,kind);
//destroy tower
//delete towers[i][j];
//towers[i][j]=NULL;
	