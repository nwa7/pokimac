
# Dans un fichier makefile, on peut utiliser de variables.
# monvar = valeur    pour affecter
# $(monvar)          pour recuperer la valeur

# De plus, il y a quelques variables internes, qu'on peut utiliser:
# $@ pour nom de cible
# $< pour nom de la premiere dependance
# $^ pour toute la liste des dépendances


CC=g++
CFLAGS=-Wall -g

game: main.o interface.o player.o pokemon.o inventory.o
	$(CC) -o $@ $^
	
main.o: main.cpp player.h pokemon.h interface.h consoleUtils.hpp
	$(CC) -o $@ -c $< $(CFLAGS)

player.o: player.cpp consoleUtils.hpp player.h interface.h
	$(CC) -o $@ -c $< $(CFLAGS)

pokemon.o: pokemon.cpp pokemon.h
	$(CC) -o $@ -c $< $(CFLAGS)	

interface.o: interface.cpp consoleUtils.hpp interface.h
	$(CC) -o $@ -c $< $(CFLAGS)	

inventory.o: inventory.cpp consoleUtils.hpp inventory.h
	$(CC) -o $@ -c $< $(CFLAGS)	

clean:
	rm -rf *.o


