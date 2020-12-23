//Using SDL, SDL_image, standard IO, and strings
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>

using namespace std;

//constants
const int SCREEN_WIDTH = 1800;
const int SCREEN_HEIGHT = 1000;
const int TOWER_WIDTH = 90;

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

SDL_Texture* background;
SDL_Texture* light;
SDL_Texture* slow;
SDL_Texture* rocket;
const SDL_Rect initiallight = { 1720,910,90,90 };
const SDL_Rect initialslow = { 1720,820,90,90 };
const SDL_Rect initialrocket = { 1720,730,90,90 };

SDL_Rect lightrect= { 1720,910,80,80 };
SDL_Rect slowrect = { 1720,820,80,80 };
SDL_Rect rocketrect = { 1720,730,80,80 };

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
	background = loadTexture("C:/Users/ASUS/Desktop/Robodefense/Robo_defense/Basic_Level_Classic.jpg");
	if (background == NULL)
	{
		printf("Failed to load background texture image!\n");
		success = false;
	}
	light = loadTexture("C:/Users/ASUS/Desktop/Robodefense/Robo_defense/Light_Gun_user.png");
	if (light == NULL)
	{
		printf("Failed to load light image!\n");
		success = false;
	}
	slow = loadTexture("C:/Users/ASUS/Desktop/Robodefense/Robo_defense/Slow_Tower_user.png");
	if (slow == NULL)
	{
		printf("Failed to load slow image!\n");
		success = false;
	}
	rocket = loadTexture("C:/Users/ASUS/Desktop/Robodefense/Robo_defense/Light_Rocket_Launcher_user.png");
	if (rocket == NULL)
	{
		printf("Failed to load rocket image!\n");
		success = false;
	}
	return success;
}

void close()
{
	//Free loaded images
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
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0xFF, 0xFF, 0xFF));
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
			bool lightflag = false;
			bool slowflag = false;
			bool rocketflag = false;
			SDL_Event e;
			while (!quit)
			{
				SDL_SetTextureBlendMode(light, SDL_BLENDMODE_BLEND);
				SDL_SetTextureAlphaMod(light, 255);
				SDL_SetTextureBlendMode(slow, SDL_BLENDMODE_BLEND);
				SDL_SetTextureAlphaMod(slow, 255);
				SDL_SetTextureBlendMode(rocket, SDL_BLENDMODE_BLEND);
				SDL_SetTextureAlphaMod(rocket, 255);
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(gRenderer);
				SDL_RenderCopy(gRenderer, background, NULL, NULL);
				SDL_RenderCopy(gRenderer, light, NULL, &initiallight);
				SDL_RenderCopy(gRenderer, slow, NULL, &initialslow);
				SDL_RenderCopy(gRenderer, rocket, NULL, &initialrocket);
				while (SDL_PollEvent(&e) != 0)
				{
					if (e.type == SDL_QUIT)
					{
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
							lightrect.x = mouse_position.x-45;
							lightrect.y = mouse_position.y-45;
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
							slowrect.x = mouse_position.x-45;
							slowrect.y = mouse_position.y-45;
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
							rocketrect.x = mouse_position.x-45;
							rocketrect.y = mouse_position.y-45;
							SDL_SetTextureBlendMode(rocket, SDL_BLENDMODE_BLEND);
							SDL_SetTextureAlphaMod(rocket, 192);
							SDL_RenderCopy(gRenderer, rocket, NULL, &rocketrect);
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