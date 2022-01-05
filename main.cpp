#define TAB_WIDTH 11
#define TAB_HEIGHT 11

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

void pop_pokemon(char **tab, class Player)
{
    for (unsigned int j=1; j<TAB_HEIGHT - 1; j++) {
		for (unsigned int i=1; i<TAB_WIDTH - 1; i++) {
            if (rand() % 8 == 2)
			    tab[j][i] = '$';
		}
	} 
}

int main(void){
    ConsoleUtils::clear();
	std::cout << "Test 9: keyboard input using arrows keys and display allocated tab of char" << std::endl;
	std::cout << "Hit Space to continue to the next test." << std::endl;
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
				tab[j][i] = (i%(TAB_WIDTH-1) == 0 || j%(TAB_HEIGHT-1) == 0) ?  '#' : '.';
			}
		}

        pop_pokemon(tab, p);

		// Display my tab at origin (0,0)
		ConsoleUtils::setCursorPos(0, 0 + textOffset);
		for (unsigned int j=0; j<TAB_HEIGHT; j++) {
			for (unsigned int i=0; i<TAB_WIDTH; i++) {
				std::cout << tab[j][i];
			}
			std::cout << std::endl;
		}

		ConsoleUtils::setCursorPos(p.cur_pos.x, p.cur_pos.y + textOffset);
		std::cout << p.skin; // Output '@' at my position

		bool exitLoop = false;
		while (!exitLoop) {
			bool special = false;
			int c = ConsoleUtils::getChar(&special);

			Position oldPos = p.cur_pos;

			if(special) {
				switch (c) {
					case ConsoleUtils::KEY_UP: if(p.cur_pos.y>0) --p.cur_pos.y; break;
					case ConsoleUtils::KEY_DOWN: if(p.cur_pos.y<TAB_HEIGHT-1) ++p.cur_pos.y; break;
					case ConsoleUtils::KEY_LEFT: if(p.cur_pos.x>0) --p.cur_pos.x; break;
					case ConsoleUtils::KEY_RIGHT: if(p.cur_pos.x<TAB_WIDTH-1) ++p.cur_pos.x; break;
					default: break;
				}
			}else if (c == ' ') {
				 exitLoop = true;
			}

			// if my position change
			if(oldPos.x != p.cur_pos.x || oldPos.y != p.cur_pos.y) {
				ConsoleUtils::setCursorPos(oldPos.x, oldPos.y + textOffset);
				std::cout << tab[oldPos.y][oldPos.x]; // Clean up my current location by showing what is in my tab
				ConsoleUtils::setCursorPos(p.cur_pos.x, p.cur_pos.y + textOffset);
				std::cout << p.skin; // Output '@' at my position
			}
		}
		// important free my allocated memory
		free(tab);
	}
    ConsoleUtils::clear();
}