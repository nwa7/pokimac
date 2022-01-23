#include <iostream>
#include <string.h>
#include "consoleUtils.hpp"
#include "interface.h"
#include "player.h"
#include "pokemon.h"

//creation écran
void initScreen(char *tab, int width, int height){
	for (int j = 0; j < height; j++){
		for (int i = 0; i < width; i++)
		{
			tab[j * width + i] = (j % (height - 1) == 0) ? '-' : (i % (width - 1) == 0) ? '|'
																							: ' ';
		}
	}
}

//creation herbe
void initGrass(char *tab, int width, int height){
for (int j = 1; j < height; j++){
		for (int i = 1; i < width -1; i++){
			tab[j * width + i] = 'w';
	}
}
}

//affichage ecran
void displayScreen(char *tab, int width, int height, int x, int y){
	ConsoleUtils::setCursorPos(0, 2);
	for (int j = 0; j < height; j++){
		for (int i = 0; i < width; i++){
			std::cout << tab[j * width + i];
		}
		std::cout << std::endl;
	}
}

//affichage de la map
void displayMap(char *map, int MAP_WIDTH, int MAP_HEIGHT, int textOffset){
	ConsoleUtils::clear();
	displayScreen(map, MAP_WIDTH, MAP_HEIGHT, 0, 0+textOffset);
}

//affichage pokemon ou player
void displayCharacter(int x, int y, char skin){
	ConsoleUtils::setCursorPos(x, y);
	std::cout << skin;
}

//affichage menu interaction
void displayActionChoice(int MAP_WIDTH, int y){
	ConsoleUtils::setCursorPos(0, y);
	std::cout << std::endl << "Qu'allez-vous faire?" << std::endl;
	std::cout << std::endl << "<- POKEMON" <<"             "<<"ATTAQUE v" << "             "<<"INVENTAIRE ^"<<"             "<<"FUITE ->" << std::endl;
	for (int i = 0; i < MAP_WIDTH; i++){
		std::cout << "-";
	}
}

//affichage pokemon et stat et barre de vie
void displayPkStat(Pokemon playerPokemon, Pokemon enemyPokemon, int MAP_WIDTH){

	int enemypkLifeLen = enemyPokemon.hp/10; 

	ConsoleUtils::setCursorPos(3, 4);
	std::cout << enemyPokemon.pkName;
	ConsoleUtils::setCursorPos(3, 5);
	std::cout << "[" << enemyPokemon.typeName << "]";
	ConsoleUtils::setCursorPos(3, 6);
	std::cout << "                   ";
	ConsoleUtils::setCursorPos(3, 6);
	std::cout << (int) enemyPokemon.hp;
	ConsoleUtils::setCursorPos(6, 6);
	std::cout << "  [";
	for(int i = 0; i<10; i++){ 
		if (i < enemypkLifeLen){
			std::cout << '#';
		}
		else {
			std::cout << ' ';
		}
	}
	ConsoleUtils::setCursorPos(10 + 9, 6);
	std::cout << "]";
	

	int nameLen = strlen(playerPokemon.pkName);
	int typeLen = strlen(playerPokemon.typeName);
	int playerpkLifeLen = playerPokemon.hp/10; 
	
	ConsoleUtils::setCursorPos(MAP_WIDTH - nameLen - 3, 7);
	std::cout << playerPokemon.pkName;
	ConsoleUtils::setCursorPos(MAP_WIDTH - typeLen - 5, 8);
	std::cout << "[" << playerPokemon.typeName << "]";
	ConsoleUtils::setCursorPos(MAP_WIDTH - 23, 9);
	std::cout << "                      ";
	ConsoleUtils::setCursorPos(MAP_WIDTH - 6 , 9);
	std::cout << (int) playerPokemon.hp;

	ConsoleUtils::setCursorPos(MAP_WIDTH - 10 - 10 , 9);	
	std::cout << "[";
	for(int i=0; i<10; i++){
		if (i < playerpkLifeLen){
			std::cout << '#';
		}
		else {
			std::cout << ' ';
		}
	}
	std::cout << "]" << std::flush;

}

//effacer espace de message
void cleanMessageArea(int width, int height){
ConsoleUtils::setCursorPos(0, height);
	for(int i=0; i<width; i++){
	std::cout << " ";
	}
ConsoleUtils::setCursorPos(0, height);
}

//changer skin lorsque pokemon est dans l'herbe
void setSkinGrass(Pokemon *pokemon, char skinGrass, char skinNormal, int grassHeight){
	if(pokemon->curPos.y < grassHeight){
		pokemon->skin = skinGrass;
	} else{
		pokemon->skin = skinNormal;
	}
}

//detection du choix en fonction des fleches du clavier
int Choice(void){
	int arrowChoice = -1;
	do{ 
		bool special = false; 
		arrowChoice = ConsoleUtils::getChar(&special);
	} while(arrowChoice != ConsoleUtils::KEY_UP && arrowChoice != ConsoleUtils::KEY_DOWN && arrowChoice != ConsoleUtils::KEY_LEFT && arrowChoice != ConsoleUtils::KEY_RIGHT);
	switch (arrowChoice){
		case ConsoleUtils::KEY_UP:
			return 0;

		case ConsoleUtils::KEY_DOWN:
			return 1;

		case ConsoleUtils::KEY_LEFT:
			return 2;

		case ConsoleUtils::KEY_RIGHT:
			return 3;

		default:
			return -1 ;
	}
}
