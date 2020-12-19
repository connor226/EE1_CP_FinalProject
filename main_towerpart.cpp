#include"tower.h"
change?
tower*** towers=new tower**[18]; 

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
		    
		}
	    }
	}
    }
    //end
}
