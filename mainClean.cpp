#include <iostream>
#include "consoleUtils.hpp"
#include <random>

using std::cin;
using std::cout;
using std::endl;

const int MAP_WIDTH = 80;
const int MAP_HEIGHT = 20;
const int INTERACTION_HEIGHT = 10;

struct Position
{
	int x;
	int y;
};

struct Player
{
	Position curPos;
	char skin;
	int pv;
};

struct Pokemon
{
	Position curPos;
	//string name; 
	char skin;
	int pv;
};

void initScreen(char *tab, int width, int height);
void displayScreen(char *tab, int width, int height, int x, int y);
Pokemon initPokemon(int x, int y, char skin, int pv);
Player initPlayer(int x, int y, char skin, int pv);
void displayCharacter(int x, int y, char skin);
void pokemonMove(Pokemon *pokemon, int MAP_WIDTH, int MAP_HEIGHT, int textOffset);
void playerMove(Player *player, int c, int MAP_HEIGHT, int MAP_WIDTH, int textOffset);
void displayActionChoice(int MAP_WIDTH);
int meetPokemon(char *screen, int MAP_WIDTH, int MAP_HEIGHT, int textOffset, Player player, Pokemon pokemon);
void displayMap(char *map, int MAP_WIDTH, int MAP_HEIGHT, int textOffset, Player player, Pokemon pokemon);
int main()
{
	ConsoleUtils::clear();
	std::cout << "GOTTA CATCH THEM ALL!!" << std::endl;
	std::cout << "Hit space to quit" << std::endl;
	{

		//génération nombre random pour déplacement pokemon
		std::srand(std::time(nullptr));
		int textOffset = 2; //décaler car on a 2 phrasesau début
		
		//init map principale 
		char *map = (char *)malloc(sizeof(char) * MAP_WIDTH * MAP_HEIGHT);
		initScreen(map, MAP_WIDTH, MAP_HEIGHT);
		displayScreen(map, MAP_WIDTH, MAP_HEIGHT, 0, 0+textOffset);

		//init screen interaction recontre pokemon
		char interactionScreen[MAP_WIDTH * INTERACTION_HEIGHT];
		initScreen(interactionScreen, MAP_WIDTH, INTERACTION_HEIGHT);

		//player
		Player player;
		player = initPlayer(MAP_WIDTH / 2, MAP_HEIGHT /2 , '@', 100);
		displayCharacter(player.curPos.x, player.curPos.y + textOffset, player.skin);

		//pokemon
		Pokemon pok1;
		pok1 = initPokemon(MAP_WIDTH - 20, MAP_HEIGHT - 5, '&', 100);
		displayCharacter(pok1.curPos.x, pok1.curPos.y + textOffset, pok1.skin);
	   
		bool gameNotOver = false;
		while (!gameNotOver){
			bool special = false;
			int c = ConsoleUtils::getChar(&special);
			if (special)
			{
				playerMove(&player, c, MAP_HEIGHT, MAP_WIDTH, textOffset); 
				if (player.curPos.x == pok1.curPos.x && player.curPos.y == pok1.curPos.y)
				{
					//passage nouvel écran
					ConsoleUtils::clear();
					displayScreen(interactionScreen, MAP_WIDTH, INTERACTION_HEIGHT, 0, 0);	
					
					//fuite 
					if(meetPokemon(map, MAP_WIDTH, MAP_HEIGHT, textOffset, player, pok1)==3){
						pokemonMove(&pok1, MAP_WIDTH, MAP_HEIGHT, textOffset);
						displayMap(map, MAP_WIDTH, MAP_HEIGHT, textOffset, player, pok1);
					};	
					
				}
				else
				{
					displayCharacter(pok1.curPos.x, pok1.curPos.y + textOffset, ' ');
					pokemonMove(&pok1, MAP_WIDTH, MAP_HEIGHT, textOffset);
					pok1.skin = '&';
					displayCharacter(pok1.curPos.x, pok1.curPos.y + textOffset, pok1.skin);
				}

				//DEBUG
				ConsoleUtils::setCursorPos(120, 0);
				std::cout << player.curPos.x << "  " << player.curPos.y; 
				ConsoleUtils::setCursorPos(120, 1); 
				std::cout << pok1.curPos.x << "  "  << pok1.curPos.y; 
				//FIN DEBUG
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

void initScreen(char *tab, int width, int height){
	for (int j = 0; j < height; j++){
		for (int i = 0; i < width; i++)
		{
			tab[j * width + i] = (j % (height - 1) == 0) ? '-' : (i % (width - 1) == 0) ? '|'
																							: ' ';
		}
	}
}

void displayScreen(char *tab, int width, int height, int x, int y){
	ConsoleUtils::setCursorPos(0, 2);
	for (int j = 0; j < height; j++){
		for (int i = 0; i < width; i++){
			std::cout << tab[j * width + i];
		}
		std::cout << std::endl;
	}
}

Player initPlayer(int x, int y, char skin, int pv){
	Player player;
	player.curPos.x = x;
	player.curPos.y = y;
	player.skin = skin;
	player.pv = pv;
	return player;
}

Pokemon initPokemon(int x, int y, char skin, int pv){
	Pokemon pokemon;
	pokemon.curPos.x = x;
	pokemon.curPos.y = y;
	pokemon.skin = skin;
	pokemon.pv = pv;
	return pokemon;
}


void displayCharacter(int x, int y, char skin){
	ConsoleUtils::setCursorPos(x, y);
	std::cout << skin;
}
 
void pokemonMove(Pokemon *pokemon, int MAP_WIDTH, int MAP_HEIGHT, int textOffset){
	int randomMove = rand();
	if (randomMove % 4 == 0 && pokemon->curPos.x != MAP_WIDTH - 2){
		pokemon->curPos.x += 1;
	}
	else if (randomMove % 4 == 1 && pokemon->curPos.x != 0){
		pokemon->curPos.x -= 1;
	}
	else if (randomMove % 4 == 2 && pokemon->curPos.y != MAP_HEIGHT - 2)
	{
		pokemon->curPos.y += 1;
	}
	else if (randomMove % 4 == 3 && pokemon->curPos.y != textOffset + 1)
	{
		pokemon->curPos.y -= 1;
	}

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
	
		displayCharacter(oldPos.x, oldPos.y + textOffset, ' ');
		displayCharacter(player->curPos.x, player->curPos.y + textOffset, player->skin);				
	}
}

void displayActionChoice(int MAP_WIDTH){

	std::cout << std::endl << "What will you do?" << std::endl;
	std::cout << std::endl << "<- POKEMON" <<"              "<<"FIGHT v" << "               "<<"CAPTURE ^"<<"              "<<"FLY AWAY ->" << std::endl;
	for (int i = 0; i < MAP_WIDTH; i++){
		std::cout << "-";
	}
}

int meetPokemon(char *screen, int MAP_WIDTH, int MAP_HEIGHT, int textOffset, Player player, Pokemon pokemon){
	displayActionChoice(MAP_WIDTH);
	int arrowChoice;
	do{ 
	bool special = false;
	arrowChoice = ConsoleUtils::getChar(&special);
	} while(arrowChoice != ConsoleUtils::KEY_UP && arrowChoice != ConsoleUtils::KEY_DOWN && arrowChoice != ConsoleUtils::KEY_LEFT && arrowChoice != ConsoleUtils::KEY_RIGHT);
	switch (arrowChoice){
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
			break;
	}
	
}

void displayMap(char *map, int MAP_WIDTH, int MAP_HEIGHT, int textOffset, Player player, Pokemon pokemon){
	ConsoleUtils::clear();
	std::cout << "GOTTA CATCH THEM ALL!!" << std::endl;
	std::cout << "Hit space to quit" << std::endl;
	displayScreen(map, MAP_WIDTH, MAP_HEIGHT, 0, 0+textOffset);
	displayCharacter(player.curPos.x, player.curPos.y + textOffset, player.skin);
	displayCharacter(pokemon.curPos.x, pokemon.curPos.y + textOffset, pokemon.skin);
}