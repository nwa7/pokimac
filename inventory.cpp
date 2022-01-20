#include <random>

#include "consoleUtils.hpp"
#include "interface.h"
#include "player.h" 
#include "pokemon.h"
#include "position.h"
#include "inventory.h"

const int MAP_WIDTH = 80;
const int MAP_HEIGHT = 20;
const int INTERACTION_HEIGHT = 10;


Bag initBag(){
	Bag bag;
	bag.pokeball = 10;
	bag.potion = 10;
	return bag;
}


void displayActionChoice2(int MAP_WIDTH){

	std::cout << std::endl << "What will you do?" << std::endl;
	std::cout << std::endl << "<- BACK" <<"              "<<"POKEBALL v" << "               "<<"POTION ^"<<"              "<<"      " << std::endl;
	for (int i = 0; i < MAP_WIDTH; i++){
		std::cout << "-";
	}
}

int Choice(){
	int arrowChoice = -1;
	do{ 
		bool special = false; 
		arrowChoice = ConsoleUtils::getChar(&special);
	} while(arrowChoice != ConsoleUtils::KEY_UP && arrowChoice != ConsoleUtils::KEY_DOWN && arrowChoice != ConsoleUtils::KEY_LEFT);
	switch (arrowChoice){
		case ConsoleUtils::KEY_UP:
			return 0;

		case ConsoleUtils::KEY_DOWN:
			return 1;

		case ConsoleUtils::KEY_LEFT:
			return 2;

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

void displayInventory(Pokemon pokemon, Player player, int textOffset, int * chosenone, Bag *bag, bool * meetOver ){
	
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
	 
	// Inventory menu loop	
	for(;;)
	{
		// Inventory action choice
		int inventoryChoice = Choice();
		// Potion action
		if(inventoryChoice==0) {
			player.teamPokemon[*chosenone].hp += 20; 
		}
		// Capture action
		else if(inventoryChoice==1){
			// Good chance to capture pokemon (return 1 if captured)
			bool captured = capture(pokemon);
			// Check if a stash is available for a new pokemon (return index in team pokemon)
			int spareplace = sparePlace(player);

			if (captured == 1 && spareplace != -1 ){
				std::cout << "Pokemon capturé !"<< std::endl;
				(*bag).pokeball--;
				std::cout << (*bag).pokeball << std::endl;
				sleep(3);
				*meetOver=true;
				break;
			}
			else if (captured == 0) {
				(*bag).pokeball--;
				std::cout << (*bag).pokeball << std::endl;
				std::cout << "La capture du pokemon a échoué" << std::endl;
			}
			else if (spareplace==-1){
				std::cout << "Team pokemon pleine" << std::endl;
			}
		}
		// Leave inventory -> to fight menu
		else if (inventoryChoice == 2)
		{
			#if 0
			ConsoleUtils::clear();
			displayScreen(fightScreen, MAP_WIDTH, INTERACTION_HEIGHT, 0, 0+textOffset);
			displayActionChoice2(MAP_WIDTH);
			
			std::cout << std::endl;		
			std::cout << player.teamPokemon[0].pkName << "  " << player.teamPokemon[0].hp << "  " << player.teamPokemon[0].atk << player.teamPokemon[0].def << "  " << player.teamPokemon[0].typeName << "  " << player.teamPokemon[0].pkName << "  " << player.teamPokemon[0].degatCoef << "   " << player.teamPokemon[0].typeNumber << std::endl;
			std::cout << std::endl;	
			std::cout << pokemon.pkName << "  " << pokemon.hp << "  " << pokemon.atk << pokemon.def << "  " << pokemon.typeName << "  " << pokemon.pkName << "  " << pokemon.degatCoef << "   " << pokemon.typeNumber << std::endl;
			#endif
			break;
		}
	}	
}   

