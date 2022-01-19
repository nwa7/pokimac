#include <iostream>
#include "consoleUtils.hpp"
#include "interface.h"
#include "player.h"
#include "pokemon.h"
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

void initFightScreen(char *tab, int width, int height, Player player, Pokemon pokemon){
	for (int j = 0; j < height; j++){
		for (int i = 0; i < width; i++)
		{
			tab[j * width + i] = (j % (height - 1) == 0) ? '-' : (i % (width - 1) == 0) ? '|' : ' ';
		}
	}	
	char name_pokemon[] = "Hubert";
	size_t len_name=6;
	size_t len_life=12;
	size_t pokemon_life=50; /*** à remplacer par hp***/
	for (size_t k = 0; name_pokemon[k] != '\0'; k++){
		tab[width + 1+k] = name_pokemon[k];
	}

	for (size_t k = 0; name_pokemon[k] != '\0'; k++){
		tab[2 * width-len_name-1+k] = name_pokemon[k];
	}

	tab[2 * width + 1] = '[' ;
	for (size_t k = 0; k < 10; k++){
		tab[2 * width + k + 2] = k < pokemon_life / 10 ? '#' : ' ' ;
	}
	tab[2 * width + len_life] = ']';

	tab[3 * width - 1 - len_life] = '[' ;
	for (size_t k = 0; k < 10; k++){
		tab[3 * width-len_life + k] = k < pokemon_life / 10 ? '#' : ' ' ;
	}
	tab[3 * width - 2 ] = ']';

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