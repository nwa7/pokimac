#ifndef POKEMON_H
#define POKEMON_H

#include "position.h"

struct Pokemon
{
	Position curPos; 
	char skin;
	float hp;
	float atk;
	float def;
	char const *typeName;
	char const *pkName; 
	float degatCoef;
	int typeNumber;
	bool active;
};
typedef struct Pokemon Pokemon;

//Pokemon initPokemon(int x, int y, char skin, int hp);
Pokemon initPokemon(int x, int y, char skin, int hp, int atkIndex, int defIndex, int nameIndex);
void pokemonMove(Pokemon *pokemon, int MAP_WIDTH, int MAP_HEIGHT, int textOffset);
void setDegatCoef(Pokemon *fightingPokemon, Pokemon *enemyPokemon);
void setStatPk(char *statPokemon);

#endif