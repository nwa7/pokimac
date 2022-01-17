#ifndef PLAYER_H
#define PLAYER_H


#include "position.h"

struct Player
{
	Position curPos;
	char skin;
	int pv;
};

Player initPlayer(int x, int y, char skin, int pv);
void playerMove(Player *player, int c, int MAP_HEIGHT, int MAP_WIDTH, int textOffset);

#endif