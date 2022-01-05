#include <algorithm>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <iomanip> // for std::setfill & std::setw

#include "consoleUtils.hpp"

#define WAIT_ANY_KEY std::cout << "Press any key to continue..." << std::endl; ConsoleUtils::getChar();

int main() {
	ConsoleUtils::clear();
	std::cout << "Console test program." << std::endl;
	WAIT_ANY_KEY

	std::cout << "Test 1: Colors" << std::endl;
	for (int i = 0; i < 16; i++) {
		ConsoleUtils::setColor(static_cast<ConsoleUtils::Color>(i));
		std::cout << i << " ";
	}

	ConsoleUtils::setColor(ConsoleUtils::Color::RED);
	std::cout << std::endl << "This text is red." << std::endl;

	ConsoleUtils::resetColors();
	std::cout << std::endl << "You should see numbers 0-15 in different colors." << std::endl;
	WAIT_ANY_KEY
	
	std::cout << "\nTest 2: Background colors\n";
	for (int i = 0; i < 8; i++) {
		ConsoleUtils::setBackgroundColor(static_cast<ConsoleUtils::BackgroundColor>(i));
		std::cout << i;
		ConsoleUtils::setBackgroundColor(ConsoleUtils::BackgroundColor::BG_BLACK);
		std::cout << ' ';
	}
	ConsoleUtils::setBackgroundColor(ConsoleUtils::BackgroundColor::BG_BLACK);
	ConsoleUtils::resetColors();
	std::cout << "\nYou should see numbers 0-7 in different-colored backgrounds.\n";

	WAIT_ANY_KEY

	std::cout << "\nTest 2 bis: Text and background colors\n";
	ConsoleUtils::setColor(ConsoleUtils::Color::BLUE);
	ConsoleUtils::setBackgroundColor(ConsoleUtils::BackgroundColor::BG_WHITE);
	std::cout << "text in blue on white background";
	ConsoleUtils::resetColors(); std::cout << std::endl;
	
	ConsoleUtils::setColor(ConsoleUtils::Color::LIGHTRED);
	ConsoleUtils::setBackgroundColor(ConsoleUtils::BackgroundColor::BG_CYAN);
	std::cout << "text in light red on cyan background";
	ConsoleUtils::resetColors(); std::cout << std::endl;

	ConsoleUtils::setColor(ConsoleUtils::Color::GREEN);
	ConsoleUtils::setBackgroundColor(ConsoleUtils::BackgroundColor::BG_YELLOW);
	std::cout << "text in green on yellow background";
	ConsoleUtils::resetColors(); std::cout << std::endl;

	WAIT_ANY_KEY

	ConsoleUtils::clear();
	std::cout << "Test 3: Clear screen" << std::endl;
	std::cout << "The colors should now be gone." << std::endl;
	WAIT_ANY_KEY

	ConsoleUtils::clear();
	std::cout << "Test 6: Cursor positioning (uses 0-based coordinates)" << std::endl;
	ConsoleUtils::setCursorPos(0,1); std::cout << "(0,1)";
	ConsoleUtils::setCursorPos(16,6); std::cout << "(16,6)";
	ConsoleUtils::setCursorPos(4,3); std::cout << "(4,3)";
	ConsoleUtils::setCursorPos(8,8); std::cout << "(8,8)";
	std::cout << std::endl << "You should see three coordinates in their specified locations." << std::endl;
	WAIT_ANY_KEY

	ConsoleUtils::clear();
	std::cout << "Test 7: Blocking keyboard input" << std::endl;
	std::cout << "You should be able to move the '@' character with zqsd keys." << std::endl;
	std::cout << "Hit Space to continue to the next test." << std::endl;
	std::cout << "Last pressed key:" << std::endl;
	{	
		int x = 7; int y = 7; bool exitLoop = false;

		while (!exitLoop) {
			ConsoleUtils::setCursorPos(x,y); std::cout << '@'; // Output player
			
			bool special = false;
			int c = ConsoleUtils::getChar(&special); // Get character

			ConsoleUtils::setCursorPos(18, 3); std::cout << (char)c << " - " << c << (special?" special Char":"             ");

			ConsoleUtils::setCursorPos(x,y); std::cout << ' '; // Clean
			switch (c) {
				case 'z': --y; break;
				case 's': ++y; break;
				case 'q': --x; break;
				case 'd': ++x; break;
				case ' ': exitLoop = true; break;
				default: break;
			}
		}
	}

	ConsoleUtils::clear();
	std::cout << "Test 8: Non-blocking keyboard input" << std::endl;
	std::cout << "You should be able to move the '@' character with ZQSD keys." << std::endl;
	std::cout << "Hit Space to continue to the next test." << std::endl;
	std::cout << "Last pressed key:" << std::endl;
	std::cout << "Count:" << std::endl;
	{	
		int x = 7;
		int y = 7;
		bool exitLoop = false;
		unsigned int cnt = 0;

		ConsoleUtils::setCursorPos(x,y); std::cout << '@'; // first display

		while (!exitLoop) {
			
			ConsoleUtils::setCursorPos(7, 4); std::cout << std::setfill('0') << std::setw(8) << cnt; // update cnt
		
			if (ConsoleUtils::kbhit()) {
				bool special = false;
				int c = ConsoleUtils::getChar(&special); // Get character

				ConsoleUtils::setCursorPos(18, 3); std::cout << (char)c << " - " << c << (special?" special Char":"             ");
				
				ConsoleUtils::setCursorPos(x, y); std::cout << ' '; // clean
				switch (c) {
					case 'z': --y; break;
					case 's': ++y; break;
					case 'q': --x; break;
					case 'd': ++x; break;
					case ' ': exitLoop = true; break;
					default: break;
				}
				ConsoleUtils::setCursorPos(x,y); std::cout << '@'; // display
			}
			++cnt;
		}
	}

	ConsoleUtils::clear();
	std::cout << "Test 9: keyboard input using arrows keys and display allocated tab of char" << std::endl;
	std::cout << "Hit Space to continue to the next test." << std::endl;
	{
		unsigned int textOffset = 2; // my call to setCursorPos must be shifted by 2 because I display 3 sentences above before.

		struct Position {
			unsigned int x;
			unsigned int y;
		};

		// init my char tab
		unsigned int width = 20;
		unsigned int height = 8;
		char* tab = (char*) malloc(sizeof(char) * width * height);

		// fill my char tab with specific pattern 
		for (unsigned int j=0; j<height; j++) {
			for (unsigned int i=0; i<width; i++) {
				tab[j*width+i] = (i%(width-1) == 0 || j%(height-1) == 0) ?  '#' : '.';
			}
		}

		Position pos = {width / 2, height / 2};

		// Display my tab at origin (0,0)
		ConsoleUtils::setCursorPos(0, 0 + textOffset);
		for (unsigned int j=0; j<height; j++) {
			for (unsigned int i=0; i<width; i++) {
				std::cout << tab[j*width+i];
			}
			std::cout << std::endl;
		}

		ConsoleUtils::setCursorPos(pos.x, pos.y + textOffset);
		std::cout << '@'; // Output '@' at my position

		bool exitLoop = false;
		while (!exitLoop) {
			bool special = false;
			int c = ConsoleUtils::getChar(&special);

			Position oldPos = pos;

			if(special) {
				switch (c) {
					case ConsoleUtils::KEY_UP: if(pos.y>0) --pos.y; break;
					case ConsoleUtils::KEY_DOWN: if(pos.y<height-1) ++pos.y; break;
					case ConsoleUtils::KEY_LEFT: if(pos.x>0) --pos.x; break;
					case ConsoleUtils::KEY_RIGHT: if(pos.x<width-1) ++pos.x; break;
					default: break;
				}
			}else if (c == ' ') {
				 exitLoop = true;
			}

			// if my position change
			if(oldPos.x != pos.x || oldPos.y != pos.y) {
				ConsoleUtils::setCursorPos(oldPos.x, oldPos.y + textOffset);
				std::cout << tab[oldPos.y*width+oldPos.x]; // Clean up my current location by showing what is in my tab
				ConsoleUtils::setCursorPos(pos.x, pos.y + textOffset);
				std::cout << '@'; // Output '@' at my position
			}
		}
		// important free my allocated memory
		free(tab);
	}

	ConsoleUtils::clear();
	std::cout << "All tests done. Bye!" << std::endl;
	return 0;
}
