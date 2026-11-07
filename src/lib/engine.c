#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <assert.h>
#include "engine.h"
#include "keyboard.h"
#include "display.h"
#include "set_game.h"
#include "score.h"

#define POINT_WIN 5
#define POINT_LOOSE 10

/** \fn init_pseudo_random_generator()
 *  \brief : Initialization of pseudo-random int generator.
 */
void init_pseudo_random_generator(){
	srand(time(NULL));
}

/** \fn free_board()
 *  \brief : free complete_board.
 *  \param : complete_board : the board for a complete game.
 */
void free_board(board * complete_board){
    for(unsigned short i = 0; i < NB_TURN; i++){
    	free(complete_board[i].words);
    	complete_board[i].words = NULL;
    	free(complete_board[i].letters);
    	complete_board[i].letters = NULL;
    }
    free(complete_board);
    complete_board = NULL;
}

/** \fn save_game()
 *  \brief : save the data of current game.
 *  \param : game : info of current game.
 */
void save_game(game_info * game){
	display_enter_name();
	score player_score = {game->points, game->turn, {0}, {0}};
	get_player_name(player_score.name);
	get_today_date(player_score.date);
	add_new_score(&player_score);
}

/** \fn play_turn()
 *  \brief : return the choice made by the player
 *  \param : one_turn_board :  the board for one turn.
 *  \param : game : info of current game.
 */
short play_turn(board * one_turn_board, game_info * game){
	assert(game != NULL);
	unsigned short j = 0;
	unsigned short res = 0;
	do{
		display_turn_info(game);
		display_words(one_turn_board->words, MASK + j);
		char choice = get_turn_choice();
		res = compare_choice(choice, one_turn_board->letters[j]);
		switch(res){
			case NOT_A_LETTER : display_bad_char(choice);
				flush_stdin_buffer();
				break;
			case PASS : game->points -= POINT_LOOSE;
				j = strlen(one_turn_board->letters);
				break;
			case GOOD_LETTER : game->points += POINT_WIN;
				replace_char(one_turn_board->words, MASK + j, one_turn_board->letters[j]);
				j++;
				if(j == strlen(one_turn_board->letters)){
					display_turn_info(game);
					display_words(one_turn_board->words, MASK + 3);
					flush_stdin_buffer();				}
				break;
			case BAD_LETTER : game->nb_lives--;
				display_wrong_letter(game->nb_lives, choice);
				flush_stdin_buffer(); break;
		}
	}while(j < strlen(one_turn_board->letters) && is_game_over(res, game->nb_lives));
	return res;
}

/** \fn play_game()
 *  \brief : play a game of guess my letter.
 */
void play_game(){
	game_info game = {3, 0, 0};
	board * complete_board = malloc(sizeof(board) * NB_TURN);
	assert(complete_board != NULL);
	if(complete_board == NULL){
		display_error_dynamic_allocation();
	}
	init_empty_collection(complete_board);
	set_board(complete_board);
	unsigned short choice = 0;
	do{
		game.turn++;
		choice = play_turn(&complete_board[game.turn-1], &game);
	}while(game.turn < NB_TURN && is_game_over(choice, game.nb_lives));
	display_end_game(&game);
	save_game(&game);
	flush_stdin_buffer();
	free_board(complete_board);
}

/** \fn begin_game()
 *  \brief : start the game.
 */
void begin_game(){
	display_splash_screen();
	flush_stdin_buffer();
	char choice = '3';
	while(choice != '0'){
		display_menu();
		choice = get_menu_choice();
		switch(choice){
			case '1' : display_rules();
				flush_stdin_buffer();
				break;
			case '2' : play_game();
				break;
			case '3' : display_history();
				flush_stdin_buffer();
				break;
		}
	}
	display_goodbye();
}