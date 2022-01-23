#include "consoleUtils.hpp"
#include "player.h"
#include "interface.h"
#include "pokemon.h"

Player initPlayer(int x, int y, char skin, Pokemon starterPokemon){
	Player player;
	player.curPos.x = x;
	player.curPos.y = y;
	player.skin = skin;
	player.teamPokemon = (Pokemon *)calloc(6,sizeof(Pokemon));
	player.teamPokemon[0] = starterPokemon;
	return player;
}


void playerMove(Player *player, int c, int MAP_HEIGHT, int MAP_WIDTH, int textOffset){

	Position oldPos = player->curPos;

	switch (c){
		case ConsoleUtils::KEY_UP:
			if (player->curPos.y > 1)
				player->curPos.y-=1;
			break;
		case ConsoleUtils::KEY_DOWN:
			if (player->curPos.y < MAP_HEIGHT - 2)
				player->curPos.y+=1;
			break;
		case ConsoleUtils::KEY_LEFT:
			if (player->curPos.x > 1)
				player->curPos.x-=1;
			break;
		case ConsoleUtils::KEY_RIGHT:
			if (player->curPos.x < MAP_WIDTH - 2)
				player->curPos.x+=1;
			break;
		default:
			break;
	}

	if (oldPos.x != player->curPos.x || oldPos.y != player->curPos.y){
		if(oldPos.y < 10){ 
			displayCharacter(oldPos.x, oldPos.y + textOffset, 'w');
		} else {
			displayCharacter(oldPos.x, oldPos.y + textOffset, ' ');
		}
		//displayCharacter(oldPos.x, oldPos.y + textOffset, ' ');
		ConsoleUtils::setColor(ConsoleUtils::Color::CYAN); 
		displayCharacter(player->curPos.x, player->curPos.y + textOffset, player->skin);	
		ConsoleUtils::resetColors();			
	}
}