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
	std::cout << std::endl << "<- POKEMON" <<"              "<<"ATTACK v" << "               "<<"CAPTURE ^"<<"              "<<"HEAL ->" << std::endl;
	for (int i = 0; i < MAP_WIDTH; i++){
		std::cout << "-";
	}
}

int fightChoice(){
	int arrowChoice;
		do{ 
		bool special = false; 
		arrowChoice = ConsoleUtils::getChar(&special);
		} while(arrowChoice != ConsoleUtils::KEY_UP && arrowChoice != ConsoleUtils::KEY_DOWN && arrowChoice != ConsoleUtils::KEY_LEFT && arrowChoice != ConsoleUtils::KEY_RIGHT);
		switch (arrowChoice){
			case ConsoleUtils::KEY_UP:
				return 0;
				break;
			case ConsoleUtils::KEY_DOWN:
				return 1;
				break;
			case ConsoleUtils::KEY_LEFT:
				return 2;
				break;
			case ConsoleUtils::KEY_RIGHT:
				return 3;
			default:
				return -1 ;
		}
}

void displayFight(Pokemon pokemon, Player player, int textOffset, int * chosenone ){
	
    ConsoleUtils::clear();
	//init screen interaction rencontre pokemon
	char fightScreen[MAP_WIDTH * INTERACTION_HEIGHT];
	initFightScreen(fightScreen, MAP_WIDTH, INTERACTION_HEIGHT, player, pokemon);
	displayScreen(fightScreen, MAP_WIDTH, INTERACTION_HEIGHT, 0, 0+textOffset);
	displayActionChoice2(MAP_WIDTH);
	
	std::cout << std::endl;		
	std::cout << player.teamPokemon[0].pkName << "  " << player.teamPokemon[0].hp << "  " << player.teamPokemon[0].atk << player.teamPokemon[0].def << "  " << player.teamPokemon[0].typeName << "  " << player.teamPokemon[0].pkName << "  " << player.teamPokemon[0].degatCoef << "   " << player.teamPokemon[0].typeNumber << std::endl;
	std::cout << std::endl;	
	std::cout << pokemon.pkName << "  " << pokemon.hp << "  " << pokemon.atk << pokemon.def << "  " << pokemon.typeName << "  " << pokemon.pkName << "  " << pokemon.degatCoef << "   " << pokemon.typeNumber << std::endl;

	//passage nouvel écran
	int fightchoice= fightChoice();
	if(fightchoice==1) {
		pokemon.hp-=(player.teamPokemon[*chosenone].atk ) * player.teamPokemon[*chosenone].degatCoef;
		displayFight(pokemon, player, textOffset, chosenone);
	}
	else if(fightchoice==3){
		player.teamPokemon[*chosenone].hp += (player.teamPokemon[*chosenone].atk)/2; /*** valeurs totalement pas pensées, A REVOIR ***/
		displayFight(pokemon, player, textOffset, chosenone ); 
	}
	
	ConsoleUtils::clear();
	displayScreen(fightScreen, MAP_WIDTH, INTERACTION_HEIGHT, 0, 0+textOffset);
	displayActionChoice2(MAP_WIDTH);
	
	std::cout << std::endl;		
	std::cout << player.teamPokemon[0].pkName << "  " << player.teamPokemon[0].hp << "  " << player.teamPokemon[0].atk << player.teamPokemon[0].def << "  " << player.teamPokemon[0].typeName << "  " << player.teamPokemon[0].pkName << "  " << player.teamPokemon[0].degatCoef << "   " << player.teamPokemon[0].typeNumber << std::endl;
	std::cout << std::endl;	
	std::cout << pokemon.pkName << "  " << pokemon.hp << "  " << pokemon.atk << pokemon.def << "  " << pokemon.typeName << "  " << pokemon.pkName << "  " << pokemon.degatCoef << "   " << pokemon.typeNumber << std::endl;
				
					
}   

