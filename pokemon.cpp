#include "pokemon.h"
#include <random>

//stats 
int pkStat[] = {5, 10, 15, 20, 25};
char const *pkName[] = {"Nevolli", "Rieuchu", "LaPortide", "Boosteevflor", "Drakeven", "Alakyurek", "Noemiaous", "Ectozlema", "Robzillard", "Theopiqueur"};
char const *pkType[] = {"Maths", "Programmation", "Audiovisuel", "Media", "Image"};

float tabDegatCoef[5][5] = {{0.5, 1, 1, 2, 0.5}, {1, 0.5, 0.5, 1, 2}, {1, 2, 0.5, 0.5, 1}, {0.5, 1, 2, 0.5, 1},{2, 0.5, 1, 1, 0.5}}; 

//creation pokemon
Pokemon initPokemon(int x, int y, char skin, int hp, int atkIndex, int defIndex, int nameIndex){
	Pokemon pokemon;
	pokemon.curPos.x = x;
	pokemon.curPos.y = y;
	pokemon.skin = skin;
	pokemon.hp = hp;
	pokemon.atk = pkStat[atkIndex];
	pokemon.def = pkStat[defIndex];
	pokemon.degatCoef = 1;
	pokemon.typeNumber = nameIndex/2; //utile pour setDegatCoef
	pokemon.typeName = pkType[nameIndex/2];
	pokemon.pkName = pkName[nameIndex];
	pokemon.active = true;
	return pokemon;
}

//deplacement pokemon
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

//set les coefficients de degats
void setDegatCoef(Pokemon *fightingPokemon, Pokemon *enemyPokemon){
    fightingPokemon->degatCoef = tabDegatCoef[fightingPokemon->typeNumber][enemyPokemon->typeNumber];
	enemyPokemon->degatCoef = tabDegatCoef[enemyPokemon->typeNumber][fightingPokemon->typeNumber];
}
