CC = g++
CFLAGS = -Wall -Wextra -Werror

SRC = main.cpp
OBJ = $(patsubst %.cpp, %.o, $(SRC))
BIN = main

all: $(BIN)

$(BIN): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	$(RM) $(BIN) $(OBJ)
