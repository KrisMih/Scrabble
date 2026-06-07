CC = gcc
CFLAGS = -Wall -Wextra -Iinclude -std=c11

SRC = src/main.c \
      src/game.c \
      src/trie.c \
      src/dictionary.c \
      src/validation.c \
      src/persistence.c \
      src/config.c

OUT = scrabble.exe

all:
	$(CC) $(CFLAGS) $(SRC) -o $(OUT)

run:
	$(OUT)

clean:
	del /f /q $(OUT)