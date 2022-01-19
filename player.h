#ifndef PLAYER_H
#define PLAYER_H


#include "position.h"
#include "pokemon.h"

/*struct Player
{
	Position curPos;
	char skin;
	int hp;
	bool active;
};*/

struct Player
{
	char const* name;
	Position curPos;
	char skin;
	Pokemon *teamPokemon; 
};
typedef struct Player Player;

Player initPlayer(int x, int y, char skin, Pokemon starterPokemon);
void playerMove(Player *player, int c, int MAP_HEIGHT, int MAP_WIDTH, int textOffset);

#endif