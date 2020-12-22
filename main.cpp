#include"tower.h"
#include<vector>
#include"enemy.h"
#include"bullet.h"
//init
tower*** towers=new tower**[18];
vector<enemy*> enemies;
vector<bullet*> bullets;
SDL_Texture* bullet_pic[2];
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
    SDL_Surface* loadedSurface = IMG_Load("C:/vclib/10_color_keying/Light_Gun.png");
    tower_pic[0] = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
    SDL_FreeSurface(loadedSurface);
}
tower* upgrade(x,y,tower* old)
{
    tower* x = new tower(x,y,old->kind+1);
    return x;
}


int main( int argc, char* args[] )
{
	//Start up SDL and create window
	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		//Load media
		if( !loadMedia() )
		{
			printf( "Failed to load media!\n" );
		}
		else
		{	
			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;

			//While application is running
			while( !quit )
			{
				//Handle events on queue
				while( SDL_PollEvent( &e ) != 0 )
				{
					//User requests quit
					if( e.type == SDL_QUIT )
					{
						quit = true;
					}
				}
                //unfreeze
                for(int i=0;i<enemies.size();i++)
                {
                    enemies[i].freeze = false;
                }
                //tower motion
                for(int i=0;i<18;i++)
                {
                    for(int j=0;j<10;j++)
                    {
                        if(towers[i][j]!=NULL)
                        {
                            //render tower
                            if(towers[i][j]->kind<6)
                            {
                                if(towers[i][j]->lock==false){
                                    for(int k=0;k<enemies.size();k++)
                                    {
                                        if(towers[i][j]->inrange(enemies[k])
                                        {
                                            towers[i][j]->rotate();
                                            if(towers[i][j]->ableatk(SDL_GetTicks()))
                                            {
                                                //make a bullet
                                                bullet* x = new bullet(towers[i][j], towers[i][j]->lock_enemy);
                                                                        bullets.push_back(x);
                                            }

                                            break;
                                        }
                                    }
                                }
                            }
                            else
                            {
                                if(towers[i][j]->inrange(towers[i][j]->lock_enemy))
                                {
                                    towers[i][j]->rotate();
                                    if(towers[i][j]->ableatk(SDL_GetTicks()))
                                    {
                                        //make a bullet
                                        bullet* x = new bullet(towers[i][j], towers[i][j]->lock_enemy);
                                        bullets.push_back(x);
                                    }
                                }
                                else
                                {
                                    towers[i][j]->lock=false;
                                    for(int k=0;k<enemies.size();k++)
                                    {
                                        if(towers[i][j]->inrange(enemies[k])
                                        {
                                            towers[i][j]->rotate();
                                            if(towers[i][j]->ableatk(SDL_GetTicks()))
                                            {
                                            //make a bullet
                                                bullet* x = new bullet(towers[i][j], towers[i][j]->lock_enemy);
                                                                                bullets.push_back(x);
                                            }
                                            break;
                                        }
                                    }
                                }
                            SDL_RenderCopy(gRender, tower_pic[towers[i][j]->kind], &towerClips[towers[i][j]->theta], &towers[i][j]->quad)
                        }
                        else
                        {
                            for(int k=0;k<enemies.size();k++)
                            {
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
                }
                //bullets motion
                for(int i=0;i<bullets.size();i++)
                {
                    bullets[i]->move();
                    SDL_RenderCopy(gRender, bullet_pic, NULL, &bullets[i]->quad)
                }
                }
                //end
            }
        }
    }
}

//making tower
towers[i][j] = new tower(x,y,kind);
//destroy tower
delete towers[i][j];
towers[i][j]=NULL;
	
	
}
