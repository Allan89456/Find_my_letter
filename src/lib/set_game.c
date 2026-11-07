#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "display.h"
#include "set_game.h"

#define NB_LETTER_IN_WORDS 6
#define LEN_MAX_ALL 50
#define NB_LINE 10

enum words_len {EASY_WORDS = 13, MEDIUM_WORDS = 19, HARD_WORDS = 25};
enum letters_len {EASY_LETTERS = 0, MEDIUM_LETTERS = 2, HARD_LETTERS = 3};

/** \fn init_words()
 *  \param : one_turn_board : the board for one turn.
 *  \param : word_len : len for one_turn_board.words
 */
void init_words(board * one_turn_board, unsigned short word_len){
	one_turn_board->words = calloc(word_len, 1);
    assert(one_turn_board->words != NULL);
    if(one_turn_board->words == NULL){
	    display_error_dynamic_allocation();
	}
}

/** \fn init_letters()
 *  \param : one_turn_board : the board for one turn.
 *  \param : letter_len : len for one_turn_board.letters
 */
void init_letters(board * one_turn_board, unsigned short letter_len){
	one_turn_board->letters = calloc(letter_len + 1, 1);
    assert(one_turn_board->letters != NULL);
	if(one_turn_board->letters == NULL){
	    display_error_dynamic_allocation();
	}
}

/** \fn init_empty_collection()
 *  \param : complete_board : the board for a complete game.
 */
void init_empty_collection(board complete_board[]){
	assert(complete_board != NULL);
    for(unsigned short i = 0; i < NB_TURN; i++){
    	if(i < EASY){
    		init_words(&complete_board[i], EASY_WORDS);
    		init_letters(&complete_board[i], EASY_LETTERS);
    	}else if(i < MEDIUM){
    		init_words(&complete_board[i], MEDIUM_WORDS);
    		init_letters(&complete_board[i], MEDIUM_LETTERS);
    	}else{
    		init_words(&complete_board[i], HARD_WORDS);
    		init_letters(&complete_board[i], HARD_LETTERS);
    	}
    }
}

/** \fn replace_char()
 *  \brief : replace a char by another.
 *  \param : words : words where old will be replace by new.
 *  \param : old : the old letter.
 *  \param : new : the letter who replaces old.
 */
void replace_char(char words[], char old, char new){
	assert(words != NULL);
	for(unsigned short j = 0; j < strlen(words); j++){
		if(words[j] == old){
			words[j] = new;
		}
	}
}

/** \fn hide_letter()
 *  \brief : place a mask on letter.
 *  \param : one_turn_board : the board for one turn.
 */
void hide_letter(board * one_turn_board){
	assert(one_turn_board != NULL);
	for(unsigned short j = 0; j < strlen(one_turn_board->letters); j++){
		replace_char(one_turn_board->words, one_turn_board->letters[j], MASK + j);
	}
}

/** \fn load()
 *  \brief : load a file into a tab.
 *  \param : tab : tab where bin will be loaded.
 *  \param : bin : file loaded.
 */
void load(char tab[][LEN_MAX_ALL], FILE * bin){
	assert(tab != NULL);
	assert(bin != NULL);
    size_t readed = fread(tab, LEN_MAX_ALL, NB_LINE, bin);
    assert(readed == NB_LINE);
    if(readed != NB_LINE){
        perror("Erreur de lecture dans le fichier\n");
    }
}

/** \fn set_words_board()
 *  \brief : initialization of words board.
 *  \param : words_and_letters : words and letters for the turn.
 *  \param : filename : name of the file where the words and letters are.
 */
void set_words_board(char words_and_letters[][LEN_MAX_ALL], const char * filename){
	assert(words_and_letters != NULL);
	assert(filename != NULL);
	FILE * bin = fopen(filename, "rb");
    assert(bin != NULL);
    if(bin == NULL){
        printf("Erreur d'ouverture du fichier %s\n", filename);
        exit(EXIT_FAILURE);
    }
    char words_tab[NB_LINE][LEN_MAX_ALL];
    load(words_tab, bin);
    fclose(bin);
    bin = NULL;
    for(unsigned short i = 0; i < 2; i++){
    	unsigned short random_word = rand() % (NB_LINE - i);
    	strcpy(words_and_letters[i], words_tab[random_word]);
    	strcpy(words_tab[random_word], words_tab[NB_LINE - 1]);
    }
}

/** \fn find_first_letter()
 *  \brief : search first letter of the slice.
 *  \param : words_and_letters : words and letters for the turn.
 *  \param : i : case who begin search.
 */
void find_first_letter(char words_and_letters[LEN_MAX_ALL], unsigned short * i){
	while(words_and_letters[*i - 1] != '\n'){
	*i = *i - 1;
	}
}

/** \fn set_letters_board()
 *  \brief : initialization of letters board.
 *  \param : words_and_letters : words and letters for the turn.
 *  \param : one_turn_board : the board for one turn.
 *  \param : nb_words : number of words for the turn.
 */
void set_letters_board(char words_and_letters[LEN_MAX_ALL], board * one_turn_board, unsigned short nb_words){
	assert(words_and_letters != NULL);
	assert(one_turn_board != NULL);
	assert(nb_words > 0);
	unsigned short j = 0;
	while(j < nb_words * NB_LETTER_IN_WORDS){
		one_turn_board->words[j] = words_and_letters[j];
		j++;
	}
	unsigned short random_letters = rand() % (strlen(words_and_letters) - j) + j;
	switch(nb_words){
		case 2 :
			if(words_and_letters[random_letters] == '\n'){
				random_letters--;
			}
			one_turn_board->letters[EASY_LETTERS] = words_and_letters[random_letters];
			break;
		case 3 :
			find_first_letter(words_and_letters, &random_letters);
			for(j = 0; j < MEDIUM_LETTERS; j++){
				one_turn_board->letters[j] = words_and_letters[random_letters + j];
			}
			break;
		case 4 :
			find_first_letter(words_and_letters, &random_letters);
			for(j = 0; j < HARD_LETTERS; j++){
				one_turn_board->letters[j] = words_and_letters[random_letters + j];
			}
			break;
	}
}

/** \fn play_complete_board()
 *  \brief : set a complete board.
 *  \param : complete_board : the board for a complete game.
 */
void set_board(board * complete_board){
	assert(complete_board != NULL);
	for(unsigned short i = 0; i < NB_TURN; i+=2){
		unsigned short nb_words = 2;
		char words[][LEN_MAX_ALL] = {{0}, {0}};
		switch(i){
			case 0 : 
				set_words_board(words, "../data/two_words.bin");
				break;
			case 2 : 
				set_words_board(words, "../data/three_words.bin");
				nb_words = 3;
				break;
			case 4 : 
				set_words_board(words, "../data/four_words.bin");
				nb_words = 4;
				break;
		}
		for(unsigned short j = 0; j < 2; j++){
			set_letters_board(words[j], &complete_board[i + j], nb_words);
			hide_letter(&complete_board[i + j]);
		}
	}
}