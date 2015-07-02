#include <queue>
#include <SDL.h>

class Snake
{
	public:
	
		Snake();
		~Snake();
		
		void newGame();
		void play(int);
		
		void eventManagement();
		void move();
		void hits();
		void print();
		
		void loadRecord();
		void saveRecord();
		void refreshScore();
		
		void changeDelay();
		
		void placeWalls(int);
		void placeFood();
		
	private:
	
		std::deque<int> xPos;
		std::deque<int> yPos;
		
		int map[50][50];
		
		int snakeSize;
		int record;
		
		int delay;
		
		int xFoodPos, yFoodPos;
		
		bool goLeft, goRight, goUp, goDown;
		bool leave, lose;
		
		int previousTime, currentTime;
		
		/** SDL **/
		
		SDL_Surface *screen, *wall, *body, *food, *score, *score2;
		
		SDL_Rect wallPos, bodyPos, foodPos, scorePos, score2Pos;
		
		SDL_Event event;
};
