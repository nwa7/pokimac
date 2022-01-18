#include "pokemon.h"
#include <random>

int pkStat[] = {5, 10, 15, 20, 25};
char const *pkName[] = {"Nevolli", "Rieuchu", "LaPortide", "Boosteevflor", "Drakeven", "Alakyurek", "Noemiaous", "Ectozlema", "Robzillard", "Theopiqueur"};
char const *pkType[] = {"Maths", "Programmation", "Audiovisuel", "Media", "Image"};

float tabDegatCoef[5][5] = {{0.5, 1, 1, 2, 0.5}, {1, 0.5, 0.5, 1, 2}, {1, 2, 0.5, 0.5, 1}, {0.5, 1, 2, 0.5, 1},{2, 0.5, 1, 1, 0.5}}; 

/*Pokemon initPokemon(int x, int y, char skin, int pv){
	Pokemon pokemon;
	pokemon.curPos.x = x;
	pokemon.curPos.y = y;
	pokemon.skin = skin;
	pokemon.pv = pv;
	return pokemon;
}*/

Pokemon initPokemon(int x, int y, char skin, int pv, int atkIndex, int defIndex, int nameIndex){
	Pokemon pokemon;
	pokemon.curPos.x = x;
	pokemon.curPos.y = y;
	pokemon.skin = skin;
	pokemon.pv = pv;
	pokemon.atk = pkStat[atkIndex];
	pokemon.def = pkStat[defIndex];
	pokemon.degatCoef = 1;
	pokemon.typeNumber = nameIndex/2;
	pokemon.typeName = pkType[nameIndex/2];
	pokemon.pkName = pkName[nameIndex];
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

void setDegatCoef(Pokemon *fightingPokemon, Pokemon *enemyPokemon){
    fightingPokemon->degatCoef = tabDegatCoef[fightingPokemon->typeNumber][enemyPokemon->typeNumber];
	enemyPokemon->degatCoef = tabDegatCoef[enemyPokemon->typeNumber][fightingPokemon->typeNumber];
}
