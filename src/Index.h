#include <SDL.h>

class Index
{
	public:
		
		Index();
		~Index();
		
		void printIndex();
		int levelChoice();
		void credits();
		
	private:
	
		/** SDL **/
		
		SDL_Surface *screen, *indexPicture, *levelChoicePicture, *creditsPicture;
		
		SDL_Rect pos;
		
		SDL_Event event;
		
		/** Snake **/
		
		Snake *game;
};

