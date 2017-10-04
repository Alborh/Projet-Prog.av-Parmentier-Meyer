SRC=main.c
BIN=test
all:$(BIN)

$(BIN):$(SRC)
	gcc $(SRC) -o $(BIN) -Wall -g -std=c99 `sdl-config --cflags --libs`
clean:
	rm -f $(BIN)
