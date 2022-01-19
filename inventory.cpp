#include <random>
#include "consoleUtils.hpp"
#include "interface.h"
#include "player.h"
#include "pokemon.h"
#include "position.h"

const int MAP_WIDTH = 80;
const int MAP_HEIGHT = 20;
const int INTERACTION_HEIGHT = 10;


void displayActionChoice2(int MAP_WIDTH){

	std::cout << std::endl << "What will you do?" << std::endl;
	std::cout << std::endl << "<- BACK" <<"              "<<"POKEBALL v" << "               "<<"POTION ^"<<"              "<<"      " << std::endl;
	for (int i = 0; i < MAP_WIDTH; i++){
		std::cout << "-";
	}
}

int Choice(){
	int arrowChoice;
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
bool capture(Pokemon pokemon){
	int luck= rand() % 100;
	int weak=(100-pokemon.hp);
	if(luck + weak < 50 ){
		return 0;
	}
	else{
		return 1;
	}
}

int sparePlace (Player player){
	for (int x=0; x<6; x++){
		if (player.teamPokemon[x].atk==0){
			return x;
		}
	}
	return -1;
}
void displayInventory(Pokemon pokemon, Player player, int textOffset, int * chosenone ){
	
    ConsoleUtils::clear();
	//init screen interaction rencontre pokemon
	char fightScreen[MAP_WIDTH * INTERACTION_HEIGHT]; /*** A remplacer par écran combat ***/
	initFightScreen(fightScreen, MAP_WIDTH, INTERACTION_HEIGHT, player, pokemon); /*** A remplacer par écran combat ***/
	displayScreen(fightScreen, MAP_WIDTH, INTERACTION_HEIGHT, 0, 0+textOffset); /*** A remplacer par écran combat ***/
	displayActionChoice2(MAP_WIDTH);
	std::cout << std::endl;		
	std::cout << player.teamPokemon[0].pkName << "  " << player.teamPokemon[0].hp << "  " << player.teamPokemon[0].atk << player.teamPokemon[0].def << "  " << player.teamPokemon[0].typeName << "  " << player.teamPokemon[0].pkName << "  " << player.teamPokemon[0].degatCoef << "   " << player.teamPokemon[0].typeNumber << std::endl;
	std::cout << std::endl;	
	std::cout << pokemon.pkName << "  " << pokemon.hp << "  " << pokemon.atk << pokemon.def << "  " << pokemon.typeName << "  " << pokemon.pkName << "  " << pokemon.degatCoef << "   " << pokemon.typeNumber << std::endl;
	 
	int fightchoice= Choice();

	std::cout << fightchoice << std::endl;

	if(fightchoice==2) {	
	}
	else if(fightchoice==1){
		ConsoleUtils::clear();
		bool captured = capture(pokemon);
		int spareplace = sparePlace(player);
		std::cout << spareplace<< std::endl;
		if (captured == 1 && spareplace != -1 ){
			std::cout << "Pokemon capturé !"<< std::endl;		
		}
		else if (captured == 0) {
			std::cout << "La capture du pokemon a échoué" << std::endl;
		}
		else if (spareplace==-1){
			std::cout << "Team pokemon pleine" << std::endl;
		}
	}
	else if(fightchoice==3){
		std::cout << "Choice 3"<< std::endl;		
		player.teamPokemon[*chosenone].hp += (player.teamPokemon[*chosenone].atk)/2; /*** valeurs totalement pas pensées, A REVOIR ***/
	}
	
	ConsoleUtils::clear();
	displayScreen(fightScreen, MAP_WIDTH, INTERACTION_HEIGHT, 0, 0+textOffset);
	displayActionChoice2(MAP_WIDTH);
	
	std::cout << std::endl;		
	std::cout << player.teamPokemon[0].pkName << "  " << player.teamPokemon[0].hp << "  " << player.teamPokemon[0].atk << player.teamPokemon[0].def << "  " << player.teamPokemon[0].typeName << "  " << player.teamPokemon[0].pkName << "  " << player.teamPokemon[0].degatCoef << "   " << player.teamPokemon[0].typeNumber << std::endl;
	std::cout << std::endl;	
	std::cout << pokemon.pkName << "  " << pokemon.hp << "  " << pokemon.atk << pokemon.def << "  " << pokemon.typeName << "  " << pokemon.pkName << "  " << pokemon.degatCoef << "   " << pokemon.typeNumber << std::endl;
				
					
}   

