//Using SDL, SDL_image, standard IO, and strings
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <vector>

using namespace std;

//constants
const int SCREEN_WIDTH = 1800;
const int SCREEN_HEIGHT = 1000;
const int TOWER_WIDTH = 80;

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

bool point_in_rect(SDL_Point p,const SDL_Rect r);

//Loads individual image as texture
SDL_Texture* loadTexture(std::string path);

SDL_Window* gWindow = NULL;

SDL_Renderer* gRenderer = NULL;

SDL_Texture* red;
SDL_Texture* blue;
SDL_Texture* green;
const SDL_Rect initialred = { 1720,910,80,80 };
const SDL_Rect initialblue = { 1720,820,80,80 };
const SDL_Rect initialgreen = { 1720,730,80,80 };

SDL_Rect redrect= { 1720,910,80,80 };
SDL_Rect bluerect = { 1720,820,80,80 };
SDL_Rect greenrect = { 1720,730,80,80 };

SDL_Point mouse_position;

bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
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
	return success;
}

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

bool loadMedia()
{
	//Loading success flag
	bool success = true;

	red = loadTexture("C:/Users/ASUS/Desktop/Robodefense/Robo_defense/red.png");
	if (red == NULL)
	{
		printf("Failed to load red texture image!\n");
		success = false;
	}
	blue = loadTexture("C:/Users/ASUS/Desktop/Robodefense/Robo_defense/blue.png");
	if (blue == NULL)
	{
		printf("Failed to load blue image!\n");
		success = false;
	}
	green = loadTexture("C:/Users/ASUS/Desktop/Robodefense/Robo_defense/green.png");
	if (green == NULL)
	{
		printf("Failed to load green image!\n");
		success = false;
	}

	return success;
}


void close()
{
	//Free loaded images
	SDL_DestroyTexture(red);
	red = NULL;


	//Destroy window	
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

SDL_Texture* loadTexture(std::string path)
{
	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
		if (newTexture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	return newTexture;
}

int main(int argc, char* args[])
{
	//Start up SDL and create window
	if ( !init() )
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		//Load media
		if (!loadMedia())
		{
			printf("Failed to load media!\n");
		}
		else
		{
			bool quit = false;
			bool redflag = false;
			bool blueflag = false;
			bool greenflag = false;
			SDL_Event e;
			while (!quit)
			{
				SDL_SetTextureBlendMode(red, SDL_BLENDMODE_BLEND);
				SDL_SetTextureAlphaMod(red, 255);
				SDL_SetTextureBlendMode(blue, SDL_BLENDMODE_BLEND);
				SDL_SetTextureAlphaMod(blue, 255);
				SDL_SetTextureBlendMode(green, SDL_BLENDMODE_BLEND);
				SDL_SetTextureAlphaMod(green, 255);
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(gRenderer);
				SDL_RenderCopy(gRenderer, red, NULL, &initialred);
				SDL_RenderCopy(gRenderer, blue, NULL, &initialblue);
				SDL_RenderCopy(gRenderer, green, NULL, &initialgreen);
				while (SDL_PollEvent(&e) != 0)
				{
					if (e.type == SDL_QUIT)
					{
						quit = true;
					}

					if ( e.type == SDL_MOUSEBUTTONDOWN )
					{
						SDL_GetMouseState(& mouse_position.x, &mouse_position.y);
						if (redflag == true)
						{
							/*
							redrect.x = mouse_position.x;
							redrect.y = mouse_position.y;
							SDL_RenderCopy(gRenderer, red, NULL, &redrect);*/
							// build
							// erase the above code in the loop
							redflag = false;
							continue;
						}
						else if (blueflag == true)
						{
							/*
							bluerect.x = mouse_position.x;
							bluerect.y = mouse_position.y;
							SDL_RenderCopy(gRenderer, blue, NULL, &bluerect);*/
							// build
							// erase the above code in the loop
							blueflag = false;
							continue;
						}
						else if (greenflag == true)
						{
							greenrect.x = mouse_position.x;
							greenrect.y = mouse_position.y;
							SDL_RenderCopy(gRenderer, green, NULL, &greenrect);
							// build
							// erase the above code in the loop
							greenflag = false;
							continue;
						}

						if (point_in_rect(mouse_position, initialred) == true)
						{
							if (redflag == false)
							{
								redflag = true;
							}							
						}
						else if (point_in_rect(mouse_position, initialblue) == true)
						{
							if (blueflag == false)
							{
								blueflag = true;
							}
						}
						else if (point_in_rect(mouse_position, initialgreen) == true)
						{
							if (greenflag == false)
							{
								greenflag = true;
							}
						}
					}

					if (redflag == true)
					{
						if (e.type == SDL_MOUSEMOTION)
						{
							SDL_GetMouseState(&mouse_position.x, &mouse_position.y);
							redrect.x = mouse_position.x;
							redrect.y = mouse_position.y;
							SDL_SetTextureBlendMode(red, SDL_BLENDMODE_BLEND);
							SDL_SetTextureAlphaMod(red, 128);
							SDL_RenderCopy(gRenderer, red, NULL, &redrect);
						}
					}
					if (blueflag == true)
					{
						if (e.type == SDL_MOUSEMOTION)
						{
							SDL_GetMouseState(&mouse_position.x, &mouse_position.y);
							bluerect.x = mouse_position.x;
							bluerect.y = mouse_position.y;
							SDL_SetTextureBlendMode(blue, SDL_BLENDMODE_BLEND);
							SDL_SetTextureAlphaMod(blue, 128);
							SDL_RenderCopy(gRenderer, blue, NULL, &bluerect);
						}
					}
					if (greenflag == true)
					{
						if (e.type == SDL_MOUSEMOTION)
						{
							SDL_GetMouseState(&mouse_position.x, &mouse_position.y);
							greenrect.x = mouse_position.x;
							greenrect.y = mouse_position.y;
							SDL_SetTextureBlendMode(green, SDL_BLENDMODE_BLEND);
							SDL_SetTextureAlphaMod(green, 128);
							SDL_RenderCopy(gRenderer, green, NULL, &greenrect);
						}
					}
				}
				SDL_RenderPresent(gRenderer);			
			}
		}
	}
	close();
	return 0;
}