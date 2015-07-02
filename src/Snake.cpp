#include <ctime>
#include <cstdlib>
#include <deque>
#include <string>
#include <fstream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Snake.h"

using namespace std;

/**************
* Constructor *
**************/

Snake::Snake()
{
	/** random **/
	
	srand(time(0));
    
    /** SDL **/
    
    SDL_Init(SDL_INIT_VIDEO);
    SDL_WM_SetCaption("Snake by Ceytix",NULL);
    
    screen = SDL_SetVideoMode(750, 810, 32, SDL_HWSURFACE|SDL_DOUBLEBUF);
    wall = SDL_CreateRGBSurface(SDL_HWSURFACE,15,15,32,0,0,0,0); //a black square (10*10)
    body = IMG_Load("files/pictures/body.png");
    food = IMG_Load("files/pictures/food.gif");
    
    scorePos.x = 5;
    scorePos.y = 760;
    
    score2Pos.x = 380;
    score2Pos.y = 760;
    
    /** SDL Events **/
    
    SDL_EventState(SDL_MOUSEMOTION, SDL_IGNORE);
    SDL_EventState(SDL_MOUSEBUTTONUP, SDL_IGNORE);
    SDL_EventState(SDL_MOUSEBUTTONDOWN, SDL_IGNORE);
    SDL_EventState(SDL_KEYUP, SDL_IGNORE);
    
    /** TTF **/
    
    TTF_Init();
}

/*************
* Destructor *
*************/

Snake::~Snake()
{
	SDL_FreeSurface(screen);
	SDL_FreeSurface(wall);
	SDL_FreeSurface(body);
	SDL_FreeSurface(food);
	
	TTF_Quit();
	SDL_Quit();
}

/*****************
* void newGame() *
*****************/

void Snake::newGame()
{
	/** map **/
	
	for(int i=0; i<50; i++)
	{
		for(int j=0; j<50; j++)
		{
			map[i][j] = 0;
		}
	}
    
	/** snake **/
	
	while(!xPos.empty())
	{
		xPos.pop_back();
	}
	
	while(!yPos.empty())
	{
		yPos.pop_back();
	}
    
    snakeSize = 1;
    
    placeWalls();
    placeFood();
    
    map[xPos[0]][yPos[0]] = 2; //there is a snake in [25][25]
    
    /** speed & time **/
    
    delay = 150;
    
    previousTime = 0;
    currentTime = 0;
	
	leave = false;
	lose = false;
    
    /** bools **/
    
    goRight = true;
    goLeft = false;
    goUp = false;
    goDown = false;
    
    /** record **/
    
    loadRecord();
}

/**************
* void play() *
**************/

void Snake::play(int value)
{   
	level = value;
	
	newGame();
    
    while(!leave && !lose)
    {	
		SDL_PollEvent(&event);
		
		eventManagement();
		
		currentTime = SDL_GetTicks();
		
		if(currentTime >= previousTime + delay)
    	{
			move();
		
			hits();
		
			changeDelay();
			
			previousTime = currentTime;
		}
		else 
		{
    		SDL_Delay(delay-(currentTime-previousTime));
    	}
    	
		print();
    }
    
    saveRecord();
}

/*************************
* void eventManagement() *
*************************/

void Snake::eventManagement()
{
	switch(event.type)
	{
		case SDL_QUIT:
            leave = true;
            break;

        case SDL_KEYDOWN:
        switch(event.key.keysym.sym)
        {
            case SDLK_ESCAPE:
            leave = true;
            break;

            case SDLK_UP:
            if(!goDown && snakeSize >= 2)
            {
                goUp = true;
                goDown = false;
                goLeft = false;
                goRight = false;
            }
            else if(snakeSize == 1)
            {
                goUp = true;
                goDown = false;
                goLeft = false;
                goRight = false;
            }
            break;

            case SDLK_DOWN:
            if(!goUp && snakeSize >= 2)
            {
                goDown = true;
                goUp = false;
                goLeft = false;
                goRight = false;
            }
            else if(snakeSize == 1)
            {
                goDown = true;
                goUp = false;
                goLeft = false;
                goRight = false;
            }
            break;

            case SDLK_LEFT:
            if(!goRight && snakeSize >= 2)
            {
                goLeft = true;
                goRight = false;
                goUp = false;
                goDown = false;
            }
            else if(snakeSize == 1)
            {
                goLeft = true;
                goRight = false;
                goUp = false;
                goDown = false;
            }
            break;

            case SDLK_RIGHT:
            if(!goLeft && snakeSize >= 2)
            {
                goRight = true;
                goLeft = false;
                goUp = false;
                goDown = false;
            }
            else if(snakeSize == 1)
            {
                goRight = true;
                goLeft = false;
                goUp = false;
                goDown = false;
            }
            break;
        }
        break;
    }
}

/**************
* void move() *
**************/

void Snake::move()
{
    if(goRight)
    {
        xPos.push_front(xPos.front() + 1);
        yPos.push_front(yPos.front());
    }
    else if(goLeft)
    {
        xPos.push_front(xPos.front() - 1);
        yPos.push_front(yPos.front());
    }
    else if(goDown)
    {
        xPos.push_front(xPos.front());
        yPos.push_front(yPos.front()+1);
    }
    else
    {
        xPos.push_front(xPos.front());
        yPos.push_front(yPos.front() - 1);
    }
}

/**************
* void hits() *
**************/

void Snake::hits()
{
	if(map[xPos.front()][yPos.front()] == 1) /** the snake hits a wall **/
    {
        lose = true;
    }
    else if(map[xPos.front()][yPos.front()] == 2) /** the snake hits himself **/
    {
        lose = true;
    }
    else if(map[xPos.front()][yPos.front()] == 3) /** the snake eats food **/
    {
        snakeSize++;
        if(snakeSize > record[level])
		{
			record[level] = snakeSize;
		}
		
        for(int i=0; i<snakeSize; i++)
        {
            map[xPos[i]][yPos[i]] = 2;
        }
        
        placeFood();
    }
    else /** nothing **/
    {
        xPos.pop_back();
        yPos.pop_back();
        for(int i=0; i<snakeSize; i++)
        {
            map[xPos[i]][yPos[i]] = 2;
            map[xPos[i+1]][yPos[i+1]] = 0;
        }
    }
}

/***************
* void print() *
***************/

void Snake::print()
{
	SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, 255, 255, 255));

	for(int i=0; i<50; i++)
	{
		for(int j=0; j<50; j++)
		{
		    if(map[i][j] == 1) /** it's a wall **/
		    {
		        wallPos.x = i*15;
		        wallPos.y = j*15;
		        SDL_BlitSurface(wall, 0, screen, &wallPos);
		    }

		    else if(map[i][j] == 2) /** it's a snake **/
		    {
		        bodyPos.x = i*15;
		        bodyPos.y = j*15;
		        SDL_BlitSurface(body, 0, screen, &bodyPos);
		    }

		    else if(map[i][j] == 3) /** it's a food **/
		    {
		        foodPos.x = i*15;
		        foodPos.y = j*15;
		        SDL_BlitSurface(food, 0, screen, &foodPos);
		    }
		}
	}
	
	refreshScore();
	
	SDL_BlitSurface(score, 0, screen, &scorePos);
	SDL_BlitSurface(score2, 0, screen, &score2Pos);
	
	SDL_Flip(screen);
}

/********************
* void loadRecord() *
********************/

void Snake::loadRecord()
{
	string best;

	ifstream best_file("files/best.save");
	for(int i=0; i<10; i++)
	{
		getline(best_file,best);

		record[i] = stoi(best);
	}
}

/********************
* void saveRecord() *
********************/

void Snake::saveRecord()
{
	ofstream bestSave("files/best.save");
	for(int i=0; i<10; i++)
	{
		bestSave << record[i] << endl;
	}
}

/**********************
* void refreshScore() *
**********************/

void Snake::refreshScore()
{
	TTF_Font *times = NULL;
	times = TTF_OpenFont("files/times.ttf",50);

	SDL_Color black = {0,0,0};
	SDL_Color white = {255,255,255};

	string scorePrint = "Score: " + to_string(snakeSize);
	
	string score2Print = "Best: " + to_string(record[level]);

	score = TTF_RenderText_Shaded(times, scorePrint.c_str(), black, white);
	score2 = TTF_RenderText_Shaded(times, score2Print.c_str(), black, white);
}

/*********************
* void changeDelay() *
*********************/

void Snake::changeDelay()
{
	if(snakeSize >= 10) delay = 140;
    if(snakeSize >= 20) delay = 130;
    if(snakeSize >= 30) delay = 120;
    if(snakeSize >= 40) delay = 110;
    if(snakeSize >= 50) delay = 100;
    if(snakeSize >= 60) delay = 90;
    if(snakeSize >= 70) delay = 75;
    if(snakeSize >= 80) delay = 65;
    if(snakeSize >= 90) delay = 50;
}

/***********************
* void placeWalls(int) *
***********************/

void Snake::placeWalls()
{
	/** walls around the map **/
	
	for(int i=0; i<50; i++)
    {
        map[i][0] = 1;
        map[i][49] = 1;
    }

    for(int i=0; i<50; i++)
    {
        map[0][i]= 1;
        map[49][i]= 1;
    }
    
    switch(level)
    {
    	case 0:
			xPos.push_front(25);
    		yPos.push_front(25);
			break;
			
    	case 1:
    		for(int i=10; i<40; i++)
    		{
    			map[16][i] = 1;
    			map[33][i] = 1;
    		}
    		
			xPos.push_front(25);
    		yPos.push_front(25);
    		break;
    		
    	case 2:
    		for(int i=1; i<=10; i++)
    		{
    			map[7][i] = 1;
    			map[14][i] = 1;
    			map[21][i] = 1;
    			map[28][i] = 1;
    			map[35][i] = 1;
    			map[42][i] = 1;
    			map[7][i+38] = 1;
    			map[14][i+38] = 1;
    			map[21][i+38] = 1;
    			map[28][i+38] = 1;
    			map[35][i+38] = 1;
    			map[42][i+38] = 1;
    		}
    		
    		xPos.push_front(25);
    		yPos.push_front(25);
    		break;
    		
    	case 3:
    		for(int i=1; i<=10; i++)
    		{
    			map[i][11] = 1;
    			map[i+38][39] = 1;
    			map[39][i] = 1;
    			map[11][i+38] = 1;
    		}
    		for(int i=1; i<=8; i++)
    		{
    			map[14][i] = 1;
    			map[36][i+40] = 1;
    			map[i][36] = 1;
    			map[i+40][14] = 1;
    		}
    		
    		map[24][22] = 1;
    		map[25][22] = 1;
    		map[26][22] = 1;
    		
    		map[27][24] = 1;
    		map[27][25] = 1;
    		map[27][26] = 1;
    		
    		map[25][27] = 1;
    		map[24][27] = 1;
    		map[23][27] = 1;
    		
    		map[22][25] = 1;
    		map[22][24] = 1;
    		map[22][23] = 1;
    		
    		xPos.push_front(25);
    		yPos.push_front(20);
    		break;
    		
    	case 4:
    		for(int i=1; i<49; i++)
    		{
    			map[i][30] = 1;
    		}
    		map[26][30] = 0;
    		map[28][30] = 0;
    		
    		for(int i=14; i<=20; i++)
    		{
    			map[i][10] = 1;
    			map[i][23] = 1;
    		}
    		
    		for(int i=14; i<=19; i++)
    		{
    			map[10][i] = 1;
    		}
    		
    		map[11][14] = 1;
    		map[11][13] = 1;
    		map[12][13] = 1;
    		map[12][12] = 1;
    		map[13][12] = 1;
    		map[13][11] = 1;
    		map[14][11] = 1;
    		
    		map[11][19] = 1;
    		map[11][20] = 1;
    		map[12][20] = 1;
    		map[12][21] = 1;
    		map[13][21] = 1;
    		map[13][22] = 1;
    		map[14][22] = 1;
    		
    		map[20][11] = 1;
    		map[21][11] = 1;
    		map[21][12] = 1;
    		map[22][12] = 1;
    		map[22][13] = 1;
    		map[23][13] = 1;
    		map[23][14] = 1;
    		map[24][14] = 1;
    		map[24][15] = 1;
    		
    		map[20][22] = 1;
    		map[21][22] = 1;
    		map[21][21] = 1;
    		map[22][21] = 1;
    		map[22][20] = 1;
    		map[23][20] = 1;
    		map[23][19] = 1;
    		map[24][19] = 1;
    		map[24][18] = 1;
    		
    		xPos.push_front(25);
    		yPos.push_front(25);
    		break;
    		
    	case 5:
    		for(int i=0; i<25; i++)
    		{
    			map[23][2*i] = 1;
    			map[26][2*i+1] = 1;
    		}
    		
    		xPos.push_front(1);
    		yPos.push_front(1);
    		break;
    		
    	case 6:
    		break;
    		
    	case 7:
    		break;
    		
    	case 8:
    		break;
    	
    	case 9:
    		break;
    		
    	default:
    		break;
    }
}

/*******************
* void placeFood() *
*******************/

void Snake::placeFood()
{
	do
    {
        xFoodPos = rand()%48 + 1;
        yFoodPos = rand()%48 + 1;
    }
    while(map[xFoodPos][yFoodPos] != 0);

    map[xFoodPos][yFoodPos] = 3;
}
