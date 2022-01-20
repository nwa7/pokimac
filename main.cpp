#include <iostream>
#include <random>
#include "consoleUtils.hpp"
#include "interface.h"
#include "player.h"
#include "pokemon.h"
#include "inventory.h"
#include <time.h>


using std::cin;
using std::cout; 
using std::endl;
using std::flush;

const int MAP_WIDTH = 80;
const int MAP_HEIGHT = 20;
const int INTERACTION_HEIGHT = 10;
int chosenone = 0;
Bag bag = initBag();

int meetPokemon(char *screen, int MAP_WIDTH, int MAP_HEIGHT, int textOffset, Player player, Pokemon pokemon);
void Attack(Pokemon *fightingPokemon, Pokemon *enemyPokemon);

int main(){

	ConsoleUtils::clear();
	std::cout << "GOTTA CATCH THEM ALL!!" << std::endl;
	std::cout << "Hit space to quit" << std::endl;
	{

	//génération nombre random pour déplacement pokemon
	std::srand(std::time(nullptr));
	int textOffset = 2; //décaler car on a 2 phrasesau début
	int numberPokemon = rand() % 25 + 8;

	//init map principale
	char *map = (char *)malloc(sizeof(char) * MAP_WIDTH * MAP_HEIGHT);
	initScreen(map, MAP_WIDTH, MAP_HEIGHT);
	displayScreen(map, MAP_WIDTH, MAP_HEIGHT, 0, 0 + textOffset);

	//init screen interaction recontre pokemon
	char interactionScreen[MAP_WIDTH * INTERACTION_HEIGHT];
	initScreen(interactionScreen, MAP_WIDTH, INTERACTION_HEIGHT);

	//player
	Pokemon starterPokemon = initPokemon(MAP_WIDTH / 2, MAP_HEIGHT / 2, '&', 100, rand() % 5, rand() % 5, rand() % 9);
	Player player;
	player = initPlayer(MAP_WIDTH / 2, MAP_HEIGHT / 2, '@', starterPokemon);
	ConsoleUtils::setColor(ConsoleUtils::Color::CYAN);
	displayCharacter(player.curPos.x, player.curPos.y + textOffset, player.skin);
	ConsoleUtils::resetColors();

	//pokemon
	Pokemon *pokemonTab = (Pokemon *)malloc(sizeof(Pokemon) * numberPokemon);
	for (int i = 0; i < numberPokemon; i++)
	{
		int pokemonX = rand() % 75;
		int pokemonY = rand() % 15;
		int atkIndex = rand() % 5;
		int defIndex = rand() % 5;
		int nameIndex = rand() % 9;
		pokemonTab[i] = initPokemon((MAP_WIDTH - 2) - pokemonX, (MAP_HEIGHT - 2) - pokemonY, '&', 100, atkIndex, defIndex, nameIndex);
		displayCharacter(pokemonTab[i].curPos.x, pokemonTab[i].curPos.y + textOffset, pokemonTab[i].skin);
	}

	bool gameNotOver = false;

	while (!gameNotOver){

		bool special = false;
		int c = ConsoleUtils::getChar(&special);

		if (special){

			playerMove(&player, c, MAP_HEIGHT, MAP_WIDTH, textOffset);

			int pokemonCollidId = -1;

			for (int i = 0; i < numberPokemon; i++){

				if (!pokemonTab[i].active) continue;

				if (player.curPos.x == pokemonTab[i].curPos.x && player.curPos.y == pokemonTab[i].curPos.y){
					pokemonCollidId = i;
					break;
				}else{

					displayCharacter(pokemonTab[i].curPos.x, pokemonTab[i].curPos.y + textOffset, ' ');
					pokemonMove(&pokemonTab[i], MAP_WIDTH, MAP_HEIGHT, textOffset);
					displayCharacter(pokemonTab[i].curPos.x, pokemonTab[i].curPos.y + textOffset, '&');

					if (!pokemonTab[i].active) continue;
					if (player.curPos.x == pokemonTab[i].curPos.x && player.curPos.y == pokemonTab[i].curPos.y){
						pokemonCollidId = i;
						break;
					}
				}
			}

			if (pokemonCollidId != -1){

				//passage nouvel écran
				ConsoleUtils::clear();
				displayScreen(interactionScreen, MAP_WIDTH, INTERACTION_HEIGHT, 0, 0);
				displayActionChoice(MAP_WIDTH, INTERACTION_HEIGHT + 2);
				displayPkStat(player.teamPokemon[0], pokemonTab[pokemonCollidId], MAP_WIDTH);

				int meetPkmn = 0;
				bool meetOver = false;
				bool playerTour = true;

				while (!meetOver)
				{
					if (playerTour){

						meetPkmn = meetPokemon(map, MAP_WIDTH, MAP_HEIGHT, textOffset, player, pokemonTab[pokemonCollidId]);

						//fuite
						if (meetPkmn == 3){
							
							cleanMessageArea(MAP_WIDTH, INTERACTION_HEIGHT + 8);
							cout << " Vous avez décidé de fuir...Trouillard !" << std::flush;
							sleep(1);
							meetOver = true;
						}
						else if (meetPkmn == 1){

							Attack(&player.teamPokemon[0], &pokemonTab[pokemonCollidId]);

							cleanMessageArea(MAP_WIDTH, INTERACTION_HEIGHT + 8);
							cout << "Vous attaquez " << pokemonTab[pokemonCollidId].pkName << " !";

							if(pokemonTab[pokemonCollidId].hp <= 0){

								pokemonTab[pokemonCollidId].hp =0;

								displayPkStat(player.teamPokemon[0], pokemonTab[pokemonCollidId], MAP_WIDTH);
								cleanMessageArea(MAP_WIDTH, INTERACTION_HEIGHT + 8);
								cout << "Félicitations ! Vous avez vaincu " << pokemonTab[pokemonCollidId].pkName << " !" << std::flush;

								pokemonTab[pokemonCollidId].active = false;
								sleep(2);
								meetOver = true; 
							}else { 
								displayPkStat(player.teamPokemon[0], pokemonTab[pokemonCollidId], MAP_WIDTH);	playerTour = false;
							}
						}
						else if (meetPkmn == 0){
							displayInventory(pokemonTab[pokemonCollidId], player, textOffset, &chosenone, &bag, &meetOver );
						}
					
					}
					else{

						sleep(1);

						Attack(&pokemonTab[pokemonCollidId], &player.teamPokemon[0]);
						cleanMessageArea(MAP_WIDTH, INTERACTION_HEIGHT + 8);
						cout << pokemonTab[pokemonCollidId].pkName << " vous attaque !";

						if (player.teamPokemon[0].hp <= 0){
							player.teamPokemon[0].hp = 0;
							meetOver = true;
						}
						else{								
							displayPkStat(player.teamPokemon[0], pokemonTab[pokemonCollidId], MAP_WIDTH);
							playerTour = true;
						}
					}
				}
				displayMap(map, MAP_WIDTH, MAP_HEIGHT, textOffset);
				displayCharacter(player.curPos.x, player.curPos.y + textOffset, player.skin);

				for (int i = 0; i < numberPokemon; i++)
				{
					if (pokemonTab[i].active) {
					displayCharacter(pokemonTab[i].curPos.x, pokemonTab[i].curPos.y + textOffset, '&');
					}
				}
			}
			}
			else if (c == ' ')
			{
				gameNotOver = true;
			}
		}

		free(map);
	}
	ConsoleUtils::clear();
}

int meetPokemon(char *screen, int MAP_WIDTH, int MAP_HEIGHT, int textOffset, Player player, Pokemon pokemon)
{
	int arrowChoice;
	do
	{
		bool special = false;
		arrowChoice = ConsoleUtils::getChar(&special);
	} while (arrowChoice != ConsoleUtils::KEY_UP && arrowChoice != ConsoleUtils::KEY_DOWN && arrowChoice != ConsoleUtils::KEY_LEFT && arrowChoice != ConsoleUtils::KEY_RIGHT);
	switch (arrowChoice)
	{
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
		return 3;
	}
}

void Attack(Pokemon *fightingPokemon, Pokemon *enemyPokemon){
	enemyPokemon->hp -= (fightingPokemon->atk * fightingPokemon->degatCoef) - (enemyPokemon->def/100 * (fightingPokemon->atk * fightingPokemon->degatCoef));
}
