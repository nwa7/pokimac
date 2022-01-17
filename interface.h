#ifndef INTERFACE_H
#define INTERFACE_H

void initScreen(char *tab, int width, int height);
void displayScreen(char *tab, int width, int height, int x, int y);
void displayMap(char *map, int MAP_WIDTH, int MAP_HEIGHT, int textOffset);
void displayActionChoice(int MAP_WIDTH);
void displayCharacter(int x, int y, char skin);

#endif