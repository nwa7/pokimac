#include "pokemon.h"
#include <random>

Pokemon initPokemon(int x, int y, char skin, int pv){
	Pokemon pokemon;
	pokemon.curPos.x = x;
	pokemon.curPos.y = y;
	pokemon.skin = skin;
	pokemon.pv = pv;
	return pokemon;
}

void pokemonMove(Pokemon *pokemon, int MAP_WIDTH, int MAP_HEIGHT, int textOffset){
	int randomMove = rand();
	if (randomMove % 4 == 0 && pokemon->curPos.x != MAP_WIDTH - 2){
		pokemon->curPos.x += 1;
	}
	else if (randomMove % 4 == 1 && pokemon->curPos.x != 2){
		pokemon->curPos.x -= 1;
	}
	else if (randomMove % 4 == 2 && pokemon->curPos.y != MAP_HEIGHT - 2)
	{
		pokemon->curPos.y += 1;
	}
	else if (randomMove % 4 == 3 && pokemon->curPos.y != textOffset + 2)
	{
		pokemon->curPos.y -= 1;
	}

}