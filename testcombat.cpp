#define TAB_WIDTH 80
#define TAB_HEIGHT 20

#include "consoleUtils.hpp"

struct Position {
	unsigned int x;
	unsigned int y;
};

class Player {
    public:
        struct Position cur_pos = {TAB_WIDTH / 2, TAB_HEIGHT / 2};
        char skin = '@';
};


int main(void){
    ConsoleUtils::clear();
	std::cout << "Test 9: keyboard input using arrows keys and display allocated tab of char" << std::endl;
	std::cout << "Hit Space to exit" << std::endl;
	{
		unsigned int textOffset = 2; // my call to setCursorPos must be shifted by 2 because I display 3 sentences above before.

		// init my char tab
        Player p;
		char **tab = (char **)malloc(sizeof(char *) * TAB_HEIGHT);
        for (size_t i = 0; i < TAB_HEIGHT; ++i)
        {
            tab[i] = (char *)malloc(sizeof(char) * TAB_WIDTH);
        }

		// fill my char tab with specific pattern 
		for (unsigned int j=0; j<TAB_HEIGHT; j++) {
			for (unsigned int i=0; i<TAB_WIDTH; i++) {
				tab[j][i] = (i%(TAB_WIDTH-1) == 0 || j%(TAB_HEIGHT-1) == 0) ?  '#' : ' ';
			}
		}


		// Display my tab at origin (0,0)
		ConsoleUtils::setCursorPos(0, 0 + textOffset);
		for (unsigned int j=0; j<TAB_HEIGHT; j++) {
			for (unsigned int i=0; i<TAB_WIDTH; i++) {
				std::cout << tab[j][i];
			}
			std::cout << std::endl;
		}
	    std::cout << "Some wild pokemon appear!! It's a "<< "Pwet" << std::endl;
	    std::cout << "What will you do?" << std::endl;
        std::cout << std::endl;
        std::cout << "                 "<<"FIGHT ←" << "          "<<"CAPTURE ↑"<<"          "<<"FLY AWAY →" << std::endl;
        for (unsigned int i=0; i<TAB_WIDTH; i++) {
				std::cout << '#';
			}
		bool exitLoop = false;
		while (!exitLoop) {
			bool special = false;
			int c = ConsoleUtils::getChar(&special);

			if(special) {
				switch (c) {
					
					case ConsoleUtils::KEY_RIGHT: ConsoleUtils::clear();
                    
	                std::cout << "Test 9: keyboard input using arrows keys and display allocated tab of char" << std::endl;
	                std::cout << "Hit Space to exit" << std::endl;for (unsigned int j=0; j<TAB_HEIGHT; j++) {
			            for (unsigned int i=0; i<TAB_WIDTH; i++) {
				            std::cout << tab[j][i];
			                }
			                std::cout << std::endl;
		                }
	                std::cout << "Bye bye u coward "<< std::endl;
	                std::cout << std::endl;
                    std::cout << std::endl;
                    std::cout << "     NO I'M NOT ←"<<"       " << "          "<<"         "<<"          "<<"NEXT →" << std::endl;
                    for (unsigned int i=0; i<TAB_WIDTH; i++) {
				        std::cout << '#';
			            }
                    ; break;
                    if(special) {
				        switch (c) {    
                            case ConsoleUtils::KEY_RIGHT: ConsoleUtils::clear(); /*** REMETTRE TERRAIN ***/
                            case ConsoleUtils::KEY_LEFT: ConsoleUtils::clear();}
                    }
					case ConsoleUtils::KEY_UP: if(p.cur_pos.x>0) --p.cur_pos.x; break;

                    std::cout << "Test 9: keyboard input using arrows keys and display allocated tab of char" << std::endl;
	                std::cout << "Hit Space to exit" << std::endl;for (unsigned int j=0; j<TAB_HEIGHT; j++) {
			            for (unsigned int i=0; i<TAB_WIDTH; i++) {
				            std::cout << tab[j][i];
			                }
			                std::cout << std::endl;
		                }
	                std::cout << "So you wanna fight uh?! "<< std::endl;
	                std::cout << std::endl;
                    std::cout << std::endl;
                    std::cout << "    ATTACK 1 ←    "<<"ATTACK 2 ↑    " << "ATTACK 3 →    "<<"ATTACK 4 →"<< std::endl;
                    for (unsigned int i=0; i<TAB_WIDTH; i++) {
				        std::cout << '#';
			            }
                    ; break;
                    if(special) {
				        switch (c) {    
                            case ConsoleUtils::KEY_RIGHT: ConsoleUtils::clear(); /*** REMETTRE TERRAIN ***/
                            case ConsoleUtils::KEY_LEFT: ConsoleUtils::clear();}
                    }
					case ConsoleUtils::KEY_LEFT: if(p.cur_pos.x>0) --p.cur_pos.x; break;
					default: break;
				}
			}else if (c == ' ') {
				 exitLoop = true;
			}


		}
		// important free my allocated memory
		free(tab);
	}
    ConsoleUtils::clear();
}