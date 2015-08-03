#ifndef INDEX_CPP
#define INDEX_CPP

#include <ctime>
#include <cstdlib>
#include <SDL.h>
#include <SDL_image.h>

#include "Snake.cpp"
#include "Index.h"

/**************
* constructor *
**************/

Index::Index()
{
	/** random **/
	
	srand(time(0));
    
    /** SDL **/
    
    SDL_Init(SDL_INIT_VIDEO);
    SDL_WM_SetCaption("Snake by Ceytix",NULL);
    
    screen = SDL_SetVideoMode(750, 810, 32, SDL_HWSURFACE|SDL_DOUBLEBUF);
    indexPicture = IMG_Load("files/pictures/index.png");
    levelChoicePicture = IMG_Load("files/pictures/levelchoice.png");
    creditsPicture = IMG_Load("files/pictures/credits.png");
    
    pos.x = 0;
    pos.y = 0;
    
    /** SDL Events **/
    
    SDL_EventState(SDL_MOUSEMOTION, SDL_IGNORE);
    SDL_EventState(SDL_MOUSEBUTTONUP, SDL_IGNORE);
    SDL_EventState(SDL_KEYUP, SDL_IGNORE);
}

/*************
* Destructor *
*************/

Index::~Index()
{
	delete game;

	SDL_FreeSurface(creditsPicture);
	SDL_FreeSurface(levelChoicePicture);
	SDL_FreeSurface(indexPicture);
	SDL_FreeSurface(screen);
	
	SDL_Quit();
}

/********************
* void printIndex() *
*********************/

void Index::printIndex()
{
	SDL_BlitSurface(indexPicture, 0, screen, &pos);
	SDL_Flip(screen);
	
	bool quit = false;
	
	while(!quit)
	{
		SDL_WaitEvent(&event);
		
		switch(event.type)
		{
			case SDL_QUIT:
				quit = true;
				break;
			
			case SDL_KEYDOWN:
				if(event.key.keysym.sym == SDLK_ESCAPE)
					quit = true;
				break;
			
			case SDL_MOUSEBUTTONDOWN:
				if(event.button.x >= 45 && event.button.x <= 345 && event.button.y >= 720 && event.button.y <= 800)
				{
					game = new Snake();
					game->play(levelChoice());
				}
				else if(event.button.x >= 405 && event.button.x <= 705 && event.button.y >= 720 && event.button.y <= 800)
				{
					credits();
				}
				break;
		}
		
		/** Blits **/
		
		SDL_BlitSurface(indexPicture, 0, screen, &pos);
		SDL_Flip(screen);
	}
}

/********************
* int levelChoice() *
********************/

int Index::levelChoice()
{
	SDL_BlitSurface(levelChoicePicture, 0, screen, &pos);
	SDL_Flip(screen);
		
	bool quit = false;
	
	while(!quit)
	{
		SDL_WaitEvent(&event);
		
		switch(event.type)
		{
			case SDL_QUIT:
				quit = true;
				break;
			
			case SDL_KEYDOWN:
				if(event.key.keysym.sym == SDLK_ESCAPE)
					quit = true;
				break;
			
			case SDL_MOUSEBUTTONDOWN:
				if(event.button.x >= 45 && event.button.x <= 345 && event.button.y >= 40 && event.button.y <= 144)
				{
					return 0;
				}
				else if(event.button.x >= 45 && event.button.x <= 345 && event.button.y >= 184 && event.button.y <= 288)
				{
					return 1;
				}
				else if(event.button.x >= 45 && event.button.x <= 345 && event.button.y >= 328 && event.button.y <= 432)
				{
					return 2;
				}
				else if(event.button.x >= 45 && event.button.x <= 345 && event.button.y >= 472 && event.button.y <= 576)
				{
					return 3;
				}
				else if(event.button.x >= 45 && event.button.x <= 345 && event.button.y >= 616 && event.button.y <= 720)
				{
					return 4;
				}
				else if(event.button.x >= 405 && event.button.x <= 705 && event.button.y >= 40 && event.button.y <= 144)
				{
					return 5;
				}
				else if(event.button.x >= 405 && event.button.x <= 705 && event.button.y >= 184 && event.button.y <= 288)
				{
					return 6;
				}
				else if(event.button.x >= 405 && event.button.x <= 705 && event.button.y >= 328 && event.button.y <= 432)
				{
					return 7;
				}
				else if(event.button.x >= 405 && event.button.x <= 705 && event.button.y >= 472 && event.button.y <= 576)
				{
					return 8;
				}
				else if(event.button.x >= 405 && event.button.x <= 705 && event.button.y >= 616 && event.button.y <= 720)
				{
					return 9;
				}
				break;
		}
		
		/** Blits **/
		
		SDL_BlitSurface(levelChoicePicture, 0, screen, &pos);
		SDL_Flip(screen);
	}
}

/******************
* void credits () *
******************/

void Index::credits()
{
	SDL_BlitSurface(creditsPicture, 0, screen, &pos);
	SDL_Flip(screen);
		
	bool quit = false;
	
	while(!quit)
	{
		SDL_WaitEvent(&event);
		
		switch(event.type)
		{
			case SDL_QUIT:
				quit = true;
				break;
			
			case SDL_KEYDOWN:
				if(event.key.keysym.sym == SDLK_ESCAPE)
					quit = true;
				break;
			
			case SDL_MOUSEBUTTONDOWN:
				if(event.button.x >= 0 && event.button.x <= 0 && event.button.y >= 0 && event.button.y <= 0)
				{
					quit = true;
				}
			
				break;
		}
		
		/** Blits **/
		
		SDL_BlitSurface(creditsPicture, 0, screen, &pos);
		SDL_Flip(screen);
	}
}

#endif

