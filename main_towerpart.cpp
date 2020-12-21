#include"tower.h"

tower*** towers=new tower**[18]; 
SDL_Texture* tower_pic[3];
SDL_Rect towerClips[32];
for (int i = 0; i < 32; i++)
{
    towerClips[i].x = 70 * (i + 1);
    towerClips[i].y = 0;
    towerClips[i].w = 70;
    towerClips[i].h = 70;
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
void loadmedia()
{
    SDL_Surface* loadedSurface = IMG_Load("C:/vclib/10_color_keying/Light_Gun.png");
    tower_pic[0] = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
    SDL_FreeSurface(loadedSurface);
}
main()
{
    while(true)
    {
    //start
	//making tower
	towers[i][j] = new tower(x,y,kind);
	//destroy tower
	delete towers[i][j];
	towers[i][j]=NULL;
	for(int i=0;i<18;i++)
	{
	    for(int j=0;j<10;j++)
	    {
		if(towers[i][j]!=NULL)
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
				}
				break;
			    }
			}
		    }
		    else
		    {
		    	if(towers[i][j]->inrange(towers->lock_enemy))
			{
			    towers[i][j]->rotate();
			    if(towers[i][j]->ableatk(SDL_GetTicks()))
			    {
			    	//make a bullet
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
                                    }
                                    break;
                                }
                            }
			}
		    }
		    //render tower
		    SDL_RenderCopy(gRender, tower_pic[towers[i][j]->kind], &towerClips[towers[i][j]->theta], &towers[i][j]->quad) 
		    
		}
	    }
	}
    }
    //end
}
