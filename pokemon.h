#ifndef POKEMON_H
#define POKEMON_H

#include "position.h"

struct Pokemon
{
	Position curPos; 
	char skin;
	float pv;
	float atk;
	float def;
	char const *typeName;
	char const *pkName; 
	float degatCoef;
	int typeNumber;
};
typedef struct Pokemon Pokemon;

//Pokemon initPokemon(int x, int y, char skin, int pv);
Pokemon initPokemon(int x, int y, char skin, int pv, int atkIndex, int defIndex, int nameIndex);
void pokemonMove(Pokemon *pokemon, int MAP_WIDTH, int MAP_HEIGHT, int textOffset);
void setDegatCoef(Pokemon *fightingPokemon, Pokemon *enemyPokemon);
void setStatPk(char *statPokemon);

#endif