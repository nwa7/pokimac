#include <iostream>

#include "consoleUtils.hpp"
#include "interface.h"

const int MAP_WIDTH = 80;
const int MAP_HEIGHT = 20;
const int INTERACTION_HEIGHT = 10;

//choix nom player
char * blabla(){
	ConsoleUtils::clear();
	ConsoleUtils::setCursorPos(8, 6);
	std::cout << "> Hey! vous êtes nouveau par ici! On peut connaître votre nom? "<<std::endl;
	char *playerName = (char *)calloc(1, 32);
	ConsoleUtils::setCursorPos(8, 8);
	std::cout << "> ";
	std::cin >> playerName;
	ConsoleUtils::setCursorPos(8, 10);
	std::cout << "> Super, " << playerName << " c'est ça :) ? " << std::endl;
	char rep[32];
	ConsoleUtils::setCursorPos(8, 12);
	std::cout << "> ";
	std::cin >> rep;
	if (rep[0]=='n'){	
		blabla();
	}
	return playerName;
}

//message de game over 
void blablafin(char * playerName){
	ConsoleUtils::clear();
	ConsoleUtils::setCursorPos(8, 6);
	std::cout << "> Bravo " << playerName << "! Vous avez constitué une fine équipe !! "<<std::endl;
	ConsoleUtils::setCursorPos(8, 8);
	std::cout << "> Au plaisir de vous revoir par ici :) "<<std::endl;
	ConsoleUtils::setCursorPos(25, 10);
	std::cout << "Laurence & Elia" << std::endl;
	bool special = false; 
	do{ 
		ConsoleUtils::getChar(&special);
	} while(!special);
}

void blablamauvaisefin(char * playerName){
	ConsoleUtils::clear();
	ConsoleUtils::setCursorPos(8, 6);
	std::cout << "> Oh non " << playerName << " vos pokemon sont tous K.O. :( "<<std::endl;
	ConsoleUtils::setCursorPos(8, 8);
	std::cout << "> N'hésitez pas à retenter votre chance ! "<<std::endl;
	ConsoleUtils::setCursorPos(25, 10);
	std::cout << "Laurence & Elia" << std::endl;
	bool special = false; 
	do{ 
		ConsoleUtils::getChar(&special);
	} while(!special);
}

//selection pokemon starter
Pokemon selecStarter(){
	Pokemon *starterTab = (Pokemon *)malloc(sizeof(Pokemon) * 3);
	char arrow[3]={'<','^','>'};
	for(int i = 0; i< 3; i++){ 
		starterTab[i] = initPokemon(MAP_WIDTH / 2, MAP_HEIGHT / 2, '&', 100, rand() % 5, rand() % 5, rand() % 10);
		ConsoleUtils::setCursorPos(8, 14+i);
		std::cout << '[' << arrow[i] << ']';
		std::cout << starterTab[i].pkName << " [" <<  starterTab[i].typeName <<"]"<< "  PV : " << (int) starterTab[i].hp << "  ATK : " << starterTab[i].atk << "  DEF : " << starterTab[i].def << std::endl  ; 
	}
	int starterchoice=Choice();
	if (starterchoice==2){
		return starterTab[0];
	}
	if (starterchoice==0){
		return starterTab[1];
	}
	if (starterchoice==3){
		return starterTab[2];
	}
	return starterTab[0];
    free(starterTab);
}


bool pokemonko(Player player){
	for (int x=0; x<6; x++){
		if ((player.teamPokemon[x].hp)!=0){
			return 0;
		}
	}
	return 1;
}