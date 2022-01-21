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

void addpkmntoteam (Player player, Pokemon pokemon, int index){

	player.teamPokemon[index].curPos.x = pokemon.curPos.x;
	player.teamPokemon[index].curPos.y = pokemon.curPos.y;
	player.teamPokemon[index].skin = pokemon.skin;
	player.teamPokemon[index].hp = 100;
	player.teamPokemon[index].atk = pokemon.atk;
	player.teamPokemon[index].def = pokemon.def;
	player.teamPokemon[index].degatCoef = pokemon.degatCoef;
	player.teamPokemon[index].typeNumber = pokemon.typeNumber;
	player.teamPokemon[index].typeName = pokemon.typeName;
	player.teamPokemon[index].pkName = pokemon.pkName;
	pokemon.active = false;
}

void displayInventory(Pokemon *pokemon, Player *player, int textOffset, int * chosenone, Bag *bag, bool * meetOver, bool * playerTour  ){
	
    ConsoleUtils::clear();
	//init screen interaction rencontre pokemon
	char interactionScreen[MAP_WIDTH * INTERACTION_HEIGHT];
	initScreen(interactionScreen, MAP_WIDTH, INTERACTION_HEIGHT); 
	displayScreen(interactionScreen, MAP_WIDTH, INTERACTION_HEIGHT, 0, 0+textOffset); 
	displayActionChoice2(MAP_WIDTH);
	/*std::cout << std::endl;		
	std::cout << (*player).teamPokemon[0].pkName << "  " << (*player).teamPokemon[0].hp << "  " << (*player).teamPokemon[0].atk << (*player).teamPokemon[0].def << "  " << (*player).teamPokemon[0].typeName << "  " << (*player).teamPokemon[0].pkName << "  " << (*player).teamPokemon[0].degatCoef << "   " << (*player).teamPokemon[0].typeNumber << std::endl;
	std::cout << std::endl;	
	std::cout <<(*pokemon).pkName << "  " << (*pokemon).hp << "  " << (*pokemon).atk << (*pokemon).def << "  " << (*pokemon).typeName << "  " << (*pokemon).pkName << "  " << (*pokemon).degatCoef << "   " << (*pokemon).typeNumber << std::endl;*/
	displayPkStat((*player).teamPokemon[*chosenone], *pokemon, MAP_WIDTH);
	ConsoleUtils::setCursorPos(0, 17); // nb magique, que faire?
	// Inventory menu loop	
	for(;;)
	{
		// Inventory action choice
		int inventoryChoice = Choice();
		// Potion action
		if(inventoryChoice==0) {
			if((*player).teamPokemon[*chosenone].hp >80){
			(*player).teamPokemon[*chosenone].hp =100;
			}else {
			(*player).teamPokemon[*chosenone].hp += 20;
			}
			std::cout <<" Vous avez utilisé une potion sur " << (*player).teamPokemon[*chosenone].pkName << " !" << std::endl;
			sleep(2);
			*playerTour=false;
			ConsoleUtils::clear();
			displayScreen(interactionScreen, MAP_WIDTH, INTERACTION_HEIGHT, 0, 0);
			displayActionChoice(MAP_WIDTH,INTERACTION_HEIGHT + textOffset);
			displayPkStat((*player).teamPokemon[*chosenone], *pokemon, MAP_WIDTH);
			break; 
			
		}
		// Capture action
		else if(inventoryChoice==1){
			// Good chance to capture pokemon (return 1 if captured)
			bool captured = capture(*pokemon);
			// Check if a stash is available for a new pokemon (return index in team pokemon)
			int spareplace = sparePlace(*player);

			if (captured == 1 && spareplace != -1 ){
				std::cout << "Pokemon capturé !"<< std::endl;
				(*bag).pokeball--;
				std::cout << (*bag).pokeball << std::endl;
				sleep(2);
				addpkmntoteam(*player, *pokemon, spareplace);
				std::cout <<(*pokemon).pkName << " a été ajouté à votre team pokemon"<< std::endl;
				sleep(2);
				*meetOver=true;
				break;
			}
			else if (captured == 0) {
				(*bag).pokeball--;
				std::cout << (*bag).pokeball << std::endl;
				std::cout << "La capture du pokemon a échoué" << std::endl;
				sleep(2);
				*playerTour=false;
				ConsoleUtils::clear();
				displayScreen(interactionScreen, MAP_WIDTH, INTERACTION_HEIGHT, 0, 0);
				displayActionChoice(MAP_WIDTH,INTERACTION_HEIGHT + textOffset);
				displayPkStat((*player).teamPokemon[*chosenone], *pokemon, MAP_WIDTH);
				break;
			}
			else if (spareplace==-1){
				std::cout << "Team pokemon pleine" << std::endl;
			}
		}
		// Leave inventory -> to fight menu
		else if (inventoryChoice == 2)
		{
			
			ConsoleUtils::clear();
			displayScreen(interactionScreen, MAP_WIDTH, INTERACTION_HEIGHT, 0, 0);
			displayActionChoice(MAP_WIDTH,INTERACTION_HEIGHT + textOffset);
			
			/*std::cout << std::endl;		
			std::cout << (*player).teamPokemon[0].pkName << "  " << (*player).teamPokemon[0].hp << "  " << (*player).teamPokemon[0].atk << (*player).teamPokemon[0].def << "  " << (*player).teamPokemon[0].typeName << "  " << (*player).teamPokemon[0].pkName << "  " << (*player).teamPokemon[0].degatCoef << "   " << (*player).teamPokemon[0].typeNumber << std::endl;
			std::cout << std::endl;	
			std::cout <<(*pokemon).pkName << "  " << (*pokemon).hp << "  " << (*pokemon).atk << (*pokemon).def << "  " << (*pokemon).typeName << "  " << (*pokemon).pkName << "  " << (*pokemon).degatCoef << "   " << (*pokemon).typeNumber << std::endl;*/
			displayPkStat((*player).teamPokemon[*chosenone], *pokemon, MAP_WIDTH);
			break;
		}
	}	
}   

void displayActionChoice3(int MAP_WIDTH){
	ConsoleUtils::setCursorPos(0, 12);
	std::cout << std::endl << "What will you do?" << std::endl;
	std::cout << std::endl << "<- BACK" <<"              "<<"CHOOSE v" << "               "<<"SEND ^"<<"              "<<"      " << std::endl;
	for (int i = 0; i < MAP_WIDTH; i++){
		std::cout << "-";
	}
}

void displayPlayerPkm(Player player, int pokemonIndex, int prevpokemonIndex){
	ConsoleUtils::setCursorPos(0, 18+prevpokemonIndex);
	std::cout << player.teamPokemon[prevpokemonIndex].pkName << " [" <<  player.teamPokemon[prevpokemonIndex].typeName <<"]"<< "  HP : " <<  (int) player.teamPokemon[prevpokemonIndex].hp << "  ATK : " << player.teamPokemon[prevpokemonIndex].atk << "  DEF : " << player.teamPokemon[prevpokemonIndex].def  ;
	ConsoleUtils::setCursorPos(0, 18+pokemonIndex);
	ConsoleUtils::setBackgroundColor(ConsoleUtils::BackgroundColor::BG_BLUE);
	std::cout << player.teamPokemon[pokemonIndex].pkName << " [" <<  player.teamPokemon[pokemonIndex].typeName <<"]"<< "  HP : " << (int)  player.teamPokemon[pokemonIndex].hp << "  ATK : " << player.teamPokemon[pokemonIndex].atk << "  DEF : " << player.teamPokemon[pokemonIndex].def  ; 
	ConsoleUtils::resetColors();
}



void displayteamPokemon(Player *player, Pokemon *pokemon, int textOffset, int * chosenone, bool * playerTour){
	
    ConsoleUtils::clear();
	char interactionScreen[MAP_WIDTH * INTERACTION_HEIGHT];
	initScreen(interactionScreen, MAP_WIDTH, INTERACTION_HEIGHT); 
	displayScreen(interactionScreen, MAP_WIDTH, INTERACTION_HEIGHT, 0, 0+textOffset); 
	displayPkStat((*player).teamPokemon[*chosenone], *pokemon, MAP_WIDTH);
	displayActionChoice3(MAP_WIDTH);

	int filledSpot = sparePlace (*player); 
	for(int i = 0; i< filledSpot; i++){ 
		ConsoleUtils::setCursorPos(0, 18+i);
		if(i ==0){ 
			ConsoleUtils::setCursorPos(0, 18);
			ConsoleUtils::setBackgroundColor(ConsoleUtils::BackgroundColor::BG_BLUE);
			std::cout << player->teamPokemon[i].pkName << " [" <<  player->teamPokemon[i].typeName <<"]"<< "  HP : " << (int) player->teamPokemon[i].hp << "  ATK : " << player->teamPokemon[i].atk << "  DEF : " << player->teamPokemon[i].def  ; 
			ConsoleUtils::resetColors();
		}else {
		std::cout << player->teamPokemon[i].pkName << " [" <<  player->teamPokemon[i].typeName <<"]"<< "  HP : " << (int) player->teamPokemon[i].hp << "  ATK : " << player->teamPokemon[i].atk << "  DEF : " << player->teamPokemon[i].def  ; 
		}
	}

	int i = 1;
	int j = i-1;
	bool choiceDone = false; 
	while(!choiceDone){ 
		int PkmChoice = Choice();

		if(PkmChoice==0) {
			if(filledSpot==1 || *chosenone == i-1){
				choiceDone = true;
			}
			else { 
			if(i==0){ 
			*chosenone = j;
			}else { 
			 *chosenone = i-1;
			}
			* playerTour = false;
			choiceDone = true; 
			}
			
		}
		else if(PkmChoice==1){
			if(filledSpot==1){
				choiceDone = true;
			}else { 
			displayPlayerPkm(*player, i, j);	
			if(i>=filledSpot-1){
			j=i;
			i=0;

			}else{
				i+=1;
				j = i-1;
			}	
			}
		}
		else if (PkmChoice == 2)
		{
			choiceDone = true;
		}
	}	
		ConsoleUtils::clear();
		displayScreen(interactionScreen, MAP_WIDTH, INTERACTION_HEIGHT, 0, 0);
		displayActionChoice(MAP_WIDTH,INTERACTION_HEIGHT + textOffset);
		displayPkStat((*player).teamPokemon[*chosenone], *pokemon, MAP_WIDTH);

}    

