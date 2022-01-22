#ifndef INTERFACE_H
#define INTERFACE_H
#include "player.h"
#include "pokemon.h"

void initScreen(char *tab, int width, int height);
void initFightScreen(char *tab, int width, int height, Player player, Pokemon pokemon);
void initGrass(char *tab, int width, int height);
void displayScreen(char *tab, int width, int height, int x, int y);
void displayMap(char *map, int MAP_WIDTH, int MAP_HEIGHT, int textOffset);
void displayActionChoice(int MAP_WIDTH, int y);
void displayCharacter(int x, int y, char skin);
void displayPkStat(Pokemon playerPokemon, Pokemon enemyPokemon, int MAP_WIDTH);
void cleanMessageArea(int width, int height);
void setSkinGrass(Pokemon *pokemon, char skinGrass, char skinNormal, int grassHeight);
int Choice(void);
#endif