#ifndef INVENTORY_H
#define INVENTORY_H

struct Bag
{
	int pokeball;
	int potion;
};
typedef struct Bag Bag;

void displayInventory(Pokemon *pokemon, Player *player, int textOffset, int * chosenone, Bag *bag, bool * meetOver, bool * playerTour);
void displayteamPokemon(Player *player, Pokemon *pokemon, int textOffset, int * chosenone, bool * playerTour);
void displayPlayerPkm(Player player, int pokemonIndex, int prevpokemonIndex);
Bag initBag();
#endif