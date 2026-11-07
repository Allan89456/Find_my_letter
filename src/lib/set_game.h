#define NB_TURN 6
#define MASK '!'

typedef struct{
	char * words;
	char * letters;
}board;

#ifndef SET_GAME_H
#define SET_GAME_H

extern void init_empty_collection(board complete_board[]);
extern void replace_char(char words[], char old, char new);
extern void set_board(board * complete_board);

#endif