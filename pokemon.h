#ifndef POKEMON_H
#define POKEMON_H

#include "position.h"

struct Pokemon
{
	Position curPos;
	//string name; 
	char skin;
	int pv;
};

Pokemon initPokemon(int x, int y, char skin, int pv);
void pokemonMove(Pokemon *pokemon, int MAP_WIDTH, int MAP_HEIGHT, int textOffset);

#endif