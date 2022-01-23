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

	std::cout << std::endl << "Que va-tu faire?" << std::endl;
	std::cout << std::endl << "<- RETOUR" <<"              "<<"POKEBALL v" << "               "<<"POTION ^"<<"              "<<"      " << std::endl;
	for (int i = 0; i < MAP_WIDTH; i++){
		std::cout << "-";
	}
}

bool capture(Pokemon pokemon){
	int luck= rand() % 100;
	int weak=(100-pokemon.hp);
	if(luck + weak < 80 ){
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
	displayPkStat((*player).teamPokemon[*chosenone], *pokemon, MAP_WIDTH);
	ConsoleUtils::setCursorPos(0, 17); 

	// Inventory menu loop	
	for(;;)
	{
		// Inventory action choice
		int inventoryChoice = Choice();
		// Potion action
		if(inventoryChoice==0) {
			if ((*bag).potion > 0){
				if((*player).teamPokemon[*chosenone].hp >70){
					(*player).teamPokemon[*chosenone].hp =100;
					(*bag).potion--;
				}
				else {
					(*player).teamPokemon[*chosenone].hp += 30;
					(*bag).potion--;
				}
			
				std::cout <<" Vous avez utilisé une potion sur " << (*player).teamPokemon[*chosenone].pkName << " !" << std::endl;
				std::cout << " Il vous reste "<<(*bag).potion << " potions" << std::endl;
				sleep(2);
			}

		else {
			std::cout << " Il ne vous reste plus de potion" << std::endl;
			sleep(2);
		}
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
			if ((*bag).pokeball <= 0){
				std::cout << " Il ne vous reste plus de pokeball" << std::endl;
				sleep(2);
			}
			else{
				if (captured == 1 && spareplace != -1 ){
					std::cout << " Pokemon capturé !"<< std::endl;
					(*bag).pokeball--;
					std::cout << " Il vous reste "<<(*bag).pokeball << " pokeballs" << std::endl;
					sleep(2);
					addpkmntoteam(*player, *pokemon, spareplace);
					std::cout <<(*pokemon).pkName << " a été ajouté à votre team pokemon"<< std::endl;
					(*pokemon).active=false;
					sleep(2);
					*meetOver=true;
					break;
				}
				else if (captured == 0) {
					(*bag).pokeball--;
					std::cout << " La capture du pokemon a échoué" << std::endl;
					std::cout << " Il te reste "<<(*bag).pokeball << " pokeballs" << std::endl;
					sleep(2);
					*playerTour=false;
					ConsoleUtils::clear();
					displayScreen(interactionScreen, MAP_WIDTH, INTERACTION_HEIGHT, 0, 0);
					displayActionChoice(MAP_WIDTH,INTERACTION_HEIGHT + textOffset);
					displayPkStat((*player).teamPokemon[*chosenone], *pokemon, MAP_WIDTH);
					break;
				}
				else if (spareplace==-1){
					std::cout << " Team pokemon pleine" << std::endl; // Implémentée pour une version du jeu avec un but différent
				}
			}
		}
		// Leave inventory -> to fight menu
		else if (inventoryChoice == 2)
		{
			
			ConsoleUtils::clear();
			displayScreen(interactionScreen, MAP_WIDTH, INTERACTION_HEIGHT, 0, 0);
			displayActionChoice(MAP_WIDTH,INTERACTION_HEIGHT + textOffset);
			displayPkStat((*player).teamPokemon[*chosenone], *pokemon, MAP_WIDTH);
			break;
		}
	}	
}   

void displayActionChoice3(int MAP_WIDTH){
	ConsoleUtils::setCursorPos(0, 12);
	std::cout << std::endl << "Qu'allez-vous faire?" << std::endl;
	std::cout << std::endl << "<- RETOUR" <<"              "<<"PARCOURIR v" << "               "<<"CHOISIR ^"<<"              "<<"      " << std::endl;
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
			std::cout << player->teamPokemon[i].pkName << " [" <<  player->teamPokemon[i].typeName <<"]"<< "  PV : " << (int) player->teamPokemon[i].hp << "  ATK : " << player->teamPokemon[i].atk << "  DEF : " << player->teamPokemon[i].def  ; 
			ConsoleUtils::resetColors();
		}else {
		std::cout << player->teamPokemon[i].pkName << " [" <<  player->teamPokemon[i].typeName <<"]"<< "  PV : " << (int) player->teamPokemon[i].hp << "  ATK : " << player->teamPokemon[i].atk << "  DEF : " << player->teamPokemon[i].def  ; 
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

