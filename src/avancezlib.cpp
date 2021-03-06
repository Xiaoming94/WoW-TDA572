#include "avancezlib.h"
#include <string>

// Creates the main window. Returns true on success.
bool AvancezLib::init(int width, int height)
{
	SDL_Log("Initializing the system...\n");

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL failed the initialization: %s\n", SDL_GetError());
		return false;
	}

	//Create window
	window = SDL_CreateWindow("aVANCEZ", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
	if (window == NULL)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Window could not be created! SDL_Error: %s\n", SDL_GetError());
		return false;
	}
	
	//Create renderer for window
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Renderer could not be created! SDL Error: %s\n", SDL_GetError());
		return false;
	}

	TTF_Init();
	font = TTF_OpenFont("assets/space_invaders.ttf", 12); //this opens a font style and sets a size
	if (font == NULL)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "font cannot be created! SDL_Error: %s\n", SDL_GetError());
		return false;
	}

	// initialize the keys

	// Player 1
	p1key.fire = false;	
	p1key.left = false;	
	p1key.right = false;
	p1key.up = false;
	p1key.down = false;

	// Player 2
	p2key.fire = false;
	p2key.left = false;
	p2key.right = false;
	p2key.up = false;
	p2key.down = false;

	//Initialize renderer color
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

	//Clear screen
	SDL_RenderClear(renderer);

	SDL_Log("System up and running...\n");
	return true;
}


// Destroys the avancez library instance
void AvancezLib::destroy()
{
	SDL_Log("Shutting down the system\n");

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	TTF_CloseFont(font);

	TTF_Quit();
	SDL_Quit();
}


bool AvancezLib::update()
{
	bool go_on = true;
	SDL_Event event;


	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
			go_on = false;

		if (event.type == SDL_KEYDOWN)
		{
			switch (event.key.keysym.sym)
			{
			/**
			 * Player 1 Keybindings
			 */
			case SDLK_ESCAPE:
			case SDLK_q:
				go_on = false;
				break;
			case SDLK_c:
				p1key.fire = true;
				break;
			case SDLK_a:
				p1key.left = true;
				break;
			case SDLK_d:
				p1key.right = true;
				break;
			case SDLK_w:
				p1key.up = true;
				break;
			case SDLK_s:
				p1key.down = true;
				break;
			/**
			 * Player 2 Keybindings
			 */
			case SDLK_m:
				p2key.fire = true;
				break;
			case SDLK_g:
				p2key.left = true;
				break;
			case SDLK_j:
				p2key.right = true;
				break;
			case SDLK_y:
				p2key.up = true;
				break;
			case SDLK_h:
				p2key.down = true;
				break;
			}
		}

		if (event.type == SDL_KEYUP)
		{
			switch (event.key.keysym.sym)
			{
			case SDLK_c:
				p1key.fire = false;
				break;
			case SDLK_a:
				p1key.left = false;
				break;
			case SDLK_d:
				p1key.right = false;
				break;
			case SDLK_w:
				p1key.up = false;
				break;
			case SDLK_s:
				p1key.down = false;
				break;
			case SDLK_m:
				p2key.fire = false;
				break;
			case SDLK_g:
				p2key.left = false;
				break;
			case SDLK_j:
				p2key.right = false;
				break;
			case SDLK_y:
				p2key.up = false;
				break;
			case SDLK_h:
				p2key.down = false;
				break;
			}
		}

	}

	//Update screen
	SDL_RenderPresent(renderer);

	//Clear screen
	SDL_RenderClear(renderer);

	return go_on;
}


Sprite * AvancezLib::createSprite(const char * spriteName)
{
	std::string spriteN(spriteName);
	std::string fullSpritePath = ASSETS_ROOT + spriteN;
	char * path = new char[fullSpritePath.length() + 1];
	strcpy(path, fullSpritePath.c_str());

	SDL_Surface* surf = SDL_LoadBMP(path);
	if (surf == NULL)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Unable to load image %s! SDL_image Error: %s\n", path, SDL_GetError());
		return NULL;
	}

	//Create texture from surface pixels
	SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, surf);
	if (texture == NULL)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Unable to create texture from %s! SDL Error: %s\n", path, SDL_GetError());
		return NULL;
	}

	//Get rid of old loaded surface
	SDL_FreeSurface(surf);

	Sprite * sprite = new Sprite(renderer, texture);

	return sprite;
}

void AvancezLib::drawText(int x, int y, const char * msg)
{
	SDL_Color black = { 0, 0, 0 };  // this is the color in rgb format, maxing out all would give you the color white, and it will be your text's color

	SDL_Surface* surf = TTF_RenderText_Solid(font, msg, black); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first

	SDL_Texture* msg_texture = SDL_CreateTextureFromSurface(renderer, surf); //now you can convert it into a texture

	int w = 0;
	int h = 0;
	SDL_QueryTexture(msg_texture, NULL, NULL, &w, &h);
	SDL_Rect dst_rect = { x, y, w, h };

	SDL_RenderCopy(renderer, msg_texture, NULL, &dst_rect);

	SDL_DestroyTexture(msg_texture);
	SDL_FreeSurface(surf);
}

float AvancezLib::getElapsedTime()
{
	return SDL_GetTicks() / 1000.f;
}

AvancezLib::KeyStatus AvancezLib::getKeyStatus(int playerNum)
{
	return playerNum == 1 ? p1key : p2key;
}


Sprite::Sprite(SDL_Renderer * renderer, SDL_Texture * texture)
{
	this->renderer = renderer;
	this->texture = texture;
}


void Sprite::draw(int x, int y)
{
	SDL_Rect rect;

	rect.x = x;
	rect.y = y;

	SDL_QueryTexture(texture, NULL, NULL, &(rect.w), &(rect.h));

	//Render texture to screen
	SDL_RenderCopy(renderer, texture, NULL, &rect);
}


void Sprite::destroy()
{
	SDL_DestroyTexture(texture);
}

