SRC=Main.c
BIN=projet

$(BIN): $(SRC) moteur.o
	gcc -Wall -g -std=c99 $(SRC) `sdl-config  --cflags --libs` -o $(BIN) moteur.o -lm
physique.o: moteur.c moteur.h
	gcc -Wall -Wextra -pedantic -g -std=c99 -c `sdl-config --cflags --libs` -lm -O3 moteur.c
clean:
	rm -f $(BIN)
