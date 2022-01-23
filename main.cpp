#include <iostream>
#include <random>
#include <time.h>

#include "consoleUtils.hpp"
#include "interface.h"
#include "player.h"
#include "pokemon.h"
#include "inventory.h"
#include "surrounding.h"


const int MAP_WIDTH = 80;
const int MAP_HEIGHT = 20;
const int INTERACTION_HEIGHT = 10;
int chosenone = 0;
Bag bag = initBag();

int meetPokemon(char *screen, int MAP_WIDTH, int MAP_HEIGHT, int textOffset, Player player, Pokemon pokemon);
void Attack(Pokemon *fightingPokemon, Pokemon *enemyPokemon);

int main(){

	//génération nombre random pour déplacement pokemon
	std::srand(std::time(nullptr));
	int textOffset = 2; //décaler car on a 2 phrases au début
	int numberPokemon = rand() % 25 + 8;

	// ecran d'accueil
	char *map = (char *)malloc(sizeof(char) * MAP_WIDTH * MAP_HEIGHT);
	initScreen(map, MAP_WIDTH, MAP_HEIGHT);
	displayScreen(map, MAP_WIDTH, MAP_HEIGHT, 0, 0 + textOffset);
	

	char *playerName = blabla();

	ConsoleUtils::clear();
	ConsoleUtils::setCursorPos(8, 6);
	std::cout << "> Parfait! Bienvenue dans notre monde rempli de pokemons! "<<std::endl;
	sleep(1);
	ConsoleUtils::setCursorPos(8, 8);
	std::cout << "> Pour commencer il faut choisir votre premier pokemon"<<std::endl;
	sleep(1);
	ConsoleUtils::setCursorPos(8, 10);
	std::cout << "> Voici les choix possibles :"<<std::endl;
	
	Pokemon starterPokemon = selecStarter();
	
	ConsoleUtils::setCursorPos(8, 18);
	std::cout << "> "<< starterPokemon.pkName << " fait desormais partie de votre équipe !" << std::endl;	
	sleep(1);
	ConsoleUtils::setCursorPos(8, 20);
	std::cout << "> Le but est de construire une team de 6 pokemons"<<std::endl;
	sleep(1);
	ConsoleUtils::setCursorPos(8, 22);
	std::cout << "> Pour jouer, utilisez les flèches du clavier"<<std::endl;
	sleep(1);
	ConsoleUtils::setCursorPos(8, 24);
	std::cout << "> Pour sortir du jeu il suffit de presser la barre espace"<<std::endl;
	sleep(1);
	ConsoleUtils::setCursorPos(8, 26);
	std::cout << "> ATTRAPEZ-LES TOUS !"<<std::endl;
	
	bool special = false; 
	do{ 
		ConsoleUtils::getChar(&special);
	} while(!special);
	

	ConsoleUtils::clear();

	//init map principale
	initGrass(map, MAP_WIDTH , MAP_HEIGHT/2);
	displayScreen(map, MAP_WIDTH, MAP_HEIGHT, 0, 0 + textOffset);

	//init screen interaction recontre pokemon
	char interactionScreen[MAP_WIDTH * INTERACTION_HEIGHT];
	initScreen(interactionScreen, MAP_WIDTH, INTERACTION_HEIGHT);

	//player
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
		int nameIndex = rand() % 10;
		pokemonTab[i] = initPokemon((MAP_WIDTH - 2) - pokemonX, (MAP_HEIGHT - 2) - pokemonY, '&', 100, atkIndex, defIndex, nameIndex);
		setSkinGrass(&pokemonTab[i], 'w', '&', MAP_HEIGHT/2);
		displayCharacter(pokemonTab[i].curPos.x, pokemonTab[i].curPos.y + textOffset, pokemonTab[i].skin);
	}

	bool gameNotOver = false;
	bool gagne = false;

	while (!gameNotOver){

		bool special = false;
		int c = ConsoleUtils::getChar(&special);

		if (special){

			playerMove(&player, c, MAP_HEIGHT, MAP_WIDTH, textOffset);

			int pokemonCollidId = -1;

			for (int i = 0; i < numberPokemon; i++){

				if (!pokemonTab[i].active) continue; //si la collision se fait avec un pokemon mort ou deja capturé 

				//checker collision
				if (player.curPos.x == pokemonTab[i].curPos.x && player.curPos.y == pokemonTab[i].curPos.y){ 
					pokemonCollidId = i;
					break;
				}else{
					//afficher skin precedent du pokemon
					setSkinGrass(&pokemonTab[i], 'w', ' ', MAP_HEIGHT/2);
					displayCharacter(pokemonTab[i].curPos.x, pokemonTab[i].curPos.y + textOffset, pokemonTab[i].skin);
					//bouger pokemon
					pokemonMove(&pokemonTab[i], MAP_WIDTH, MAP_HEIGHT, textOffset);
					//afficher pokemon
					setSkinGrass(&pokemonTab[i], 'w', '&', MAP_HEIGHT/2);
					displayCharacter(pokemonTab[i].curPos.x, pokemonTab[i].curPos.y + textOffset, pokemonTab[i].skin);

					if (!pokemonTab[i].active) continue;
					//rechecker collision
					if (player.curPos.x == pokemonTab[i].curPos.x && player.curPos.y == pokemonTab[i].curPos.y) 
					{
						pokemonCollidId = i;
						break;
					}
				}
			}

			if (pokemonCollidId != -1){

				//passage nouvel écran
				ConsoleUtils::clear();
				displayScreen(interactionScreen, MAP_WIDTH, INTERACTION_HEIGHT, 0, 0);
				displayActionChoice(MAP_WIDTH, INTERACTION_HEIGHT + textOffset);
				displayPkStat(player.teamPokemon[chosenone], pokemonTab[pokemonCollidId], MAP_WIDTH);

				int meetPkmn = 0;
				bool meetOver = false;
				bool playerTour = true;

				while (!meetOver)
				{
					if (playerTour){

						meetPkmn = Choice();

						//fuite
						if (meetPkmn == 3){
							
							cleanMessageArea(MAP_WIDTH, INTERACTION_HEIGHT + 8);
							std::cout << " Vous avez décidé de fuir...Trouillard !" << std::flush;
							sleep(2);
							meetOver = true;
						} //attaque
						else if (meetPkmn == 1){

							Attack(&player.teamPokemon[chosenone], &pokemonTab[pokemonCollidId]);

							cleanMessageArea(MAP_WIDTH, INTERACTION_HEIGHT + 8);
							std::cout << "Vous attaquez " << pokemonTab[pokemonCollidId].pkName << " !";

							if(pokemonTab[pokemonCollidId].hp <= 0){

								pokemonTab[pokemonCollidId].hp =0;

								displayPkStat(player.teamPokemon[chosenone], pokemonTab[pokemonCollidId], MAP_WIDTH);
								cleanMessageArea(MAP_WIDTH, INTERACTION_HEIGHT + 8);
								std::cout << "Félicitations ! Vous avez vaincu " << pokemonTab[pokemonCollidId].pkName << " !" << std::flush;
								std::cout << std::endl;

								//possibilité de gagner un objet après victoire 
								int pokeballwon = rand() % 20;
								if (pokeballwon<5){
									bag.pokeball++;
								std::cout << "Vous obtenez 1 pokeball!" << std::endl;
								}
								else if(pokeballwon==6 || pokeballwon==7){	
									bag.pokeball+=2;
									std::cout << "Vous obtenez 2 pokeballs!" << std::endl;
									}
								else if(pokeballwon==8){	
								bag.pokeball+=3;
								std::cout << "Vous obtenez 3 pokeballs!" << std::endl;
								}
								int potionwon = rand() % 20;
								if (potionwon<5){
									bag.potion++;
								std::cout << "Vous obtenez 1 potion!" << std::endl;
								}
								else if(potionwon==6 || potionwon==7){	
									bag.potion+=2;
									std::cout << "Vous obtenez 2 potions!" << std::endl;
									}
								else if(potionwon==8){	
								bag.potion+=3;
								std::cout << "Vous obtenez 3 potions!" << std::endl;
								}
								pokemonTab[pokemonCollidId].active = false;
								sleep(2);
								meetOver = true; 
							}else { 
								displayPkStat(player.teamPokemon[chosenone], pokemonTab[pokemonCollidId], MAP_WIDTH);	
								playerTour = false;
							}
						} //entrer dans l'inventaire
						else if (meetPkmn == 0){
							displayInventory(pokemonTab + pokemonCollidId, &player, textOffset, &chosenone, &bag, &meetOver, &playerTour);
						}  	            
						//changer de pokemon 
						else if (meetPkmn == 2){
							displayteamPokemon(&player, &pokemonTab[pokemonCollidId], textOffset, &chosenone, &playerTour);
						}
					
					}
					else{
						//tour du pokemon, il attaque
						sleep(1);

						Attack(&pokemonTab[pokemonCollidId], &player.teamPokemon[chosenone]);

						cleanMessageArea(MAP_WIDTH, INTERACTION_HEIGHT + 8);
						std::cout << pokemonTab[pokemonCollidId].pkName << " vous attaque !";

						if (player.teamPokemon[chosenone].hp <= 0){
							player.teamPokemon[chosenone].hp = 0;

							//laisser la possibilité de choisir un autre pokemon lorsque chosenone meurt
							displayteamPokemon(&player, &pokemonTab[pokemonCollidId], textOffset, &chosenone, &playerTour);

							//terminer combat si nouveau pokemon choisi est aussi mort
							if (player.teamPokemon[chosenone].hp <= 0){
								player.teamPokemon[chosenone].hp = 0;
							meetOver = true;
							}
						}
						else{								
							displayPkStat(player.teamPokemon[chosenone], pokemonTab[pokemonCollidId], MAP_WIDTH);
							playerTour = true;
						}
					}
				}
				//tester si équipe complete
				if (player.teamPokemon[5].atk != 0){
					gagne=true;
					gameNotOver = true;
				}

				//remettre map, pokemon et player
				displayMap(map, MAP_WIDTH, MAP_HEIGHT, textOffset);
				ConsoleUtils::setColor(ConsoleUtils::Color::CYAN); 
				displayCharacter(player.curPos.x, player.curPos.y + textOffset, player.skin);
				ConsoleUtils::resetColors();

				for (int i = 0; i < numberPokemon; i++)
				{
					if (pokemonTab[i].active) {
					displayCharacter(pokemonTab[i].curPos.x, pokemonTab[i].curPos.y + textOffset, pokemonTab[i].skin);
					}
				}
			}
			}
			else if (c == ' ')
			{
				gameNotOver = true;
			}
		}
	if (gagne){
		blablafin(playerName);
	}
	// On libère tout le monde
	free(playerName);
	free(map);
	free(pokemonTab);
	free(player.teamPokemon);

	ConsoleUtils::clear();
}


void Attack(Pokemon *fightingPokemon, Pokemon *enemyPokemon){
	enemyPokemon->hp -= (fightingPokemon->atk * fightingPokemon->degatCoef) - (enemyPokemon->def/100 * (fightingPokemon->atk * fightingPokemon->degatCoef));
}