#include <iostream>
#include "consoleUtils.hpp"
#include "interface.h"
using std::cout;
using std::endl;


void initScreen(char *tab, int width, int height){
	for (int j = 0; j < height; j++){
		for (int i = 0; i < width; i++)
		{
			tab[j * width + i] = (j % (height - 1) == 0) ? '-' : (i % (width - 1) == 0) ? '|'
																							: ' ';
		}
	}
}


void displayScreen(char *tab, int width, int height, int x, int y){
	ConsoleUtils::setCursorPos(0, 2);
	for (int j = 0; j < height; j++){
		for (int i = 0; i < width; i++){
			std::cout << tab[j * width + i];
		}
		std::cout << std::endl;
	}
}


void displayMap(char *map, int MAP_WIDTH, int MAP_HEIGHT, int textOffset){
	ConsoleUtils::clear();
	std::cout << "GOTTA CATCH THEM ALL!!" << std::endl;
	std::cout << "Hit space to quit" << std::endl;
	displayScreen(map, MAP_WIDTH, MAP_HEIGHT, 0, 0+textOffset);
}

void displayCharacter(int x, int y, char skin){
	ConsoleUtils::setCursorPos(x, y);
	std::cout << skin;
}

void displayActionChoice(int MAP_WIDTH){

	std::cout << std::endl << "What will you do?" << std::endl;
	std::cout << std::endl << "<- POKEMON" <<"              "<<"FIGHT v" << "               "<<"CAPTURE ^"<<"              "<<"FLY AWAY ->" << std::endl;
	for (int i = 0; i < MAP_WIDTH; i++){
		std::cout << "-";
	}
}