CC=gcc
CFLAGS=-Wall -Wextra -Werror -Wwrite-strings -Wshadow -std=c99
OBJ=find_my_letter.o lib/display.o lib/keyboard.o lib/engine.o lib/set_game.o lib/score.o
LDFLAGS=
EXEC= play

all: find_my_letter tests clean

find_my_letter: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LDFLAGS) -o $(EXEC)

display.o : lib/display.c lib/display.h
	$(CC) -o lib/display.o -c lib/display.c $(CFLAGS)

keyboard.o : lib/keyboard.c lib/keyboard.h
	$(CC) -o lib/keyboard.o -c lib/keyboard.c $(CFLAGS)

engine.o : lib/engine.c lib/engine.h
	$(CC) -o lib/engine.o -c lib/engine.c $(CFLAGS)

set_game.o : lib/set_game.c lib/set_game.h
	$(CC) -o lib/set_game.o -c lib/set_game.c $(CFLAGS)

score.o : lib/score.c lib/score.h
	$(CC) -o lib/score.o -c lib/score.c $(CFLAGS)

tests :
	$(CC) -Wall -o ../tests/run-keyboard_tests ../tests/keyboard_tests.c -lcunit
	../tests/run-keyboard_tests

doc :
	firefox ../doc/html/index.html

clean:
	rm -rf $(OBJ)
	rm -rf lib/$(OBJ)

mrproper: clean
	rm -rf $(EXEC)
	rm -rf ../tests/run-*