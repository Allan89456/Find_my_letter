#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "keyboard.h"

/** \fn flush_stdin_buffer()
 *  \brief : flush stdin.
 */
void flush_stdin_buffer(){
	int c = -1;
	do{
		c = getchar();
	}while(c != '\n' && c != EOF);
}

/** \fn get_menu_choice()
 *  \brief : retrun the choice of the user for the menu
 */
char get_menu_choice(){
	char choice = getchar();
	flush_stdin_buffer();
	return choice;
}

/** \fn get_player_name()
 *  \brief : retrun the name of the player.
 *  \param : name : name of the player
 */
void get_player_name(char name[]){
	assert(name != NULL);
	scanf("%15s", name);
	for(unsigned short j = strlen(name); j < 15; j++){
		name[j] = ' ';
	}
}

/** \fn compare_choice()
 *  \brief : retrun 0 if not a letter, 1 for pass,
 *  2 for good letter, 3 for bad letter and 4 for quit.
 *  \param : choice : choice of the player.
 *  \param : letter : letter masked and seek.
 */
unsigned short compare_choice(char choice, char letter){
	unsigned short res = NOT_A_LETTER;
	if(choice == '0'){
		res = QUIT;
	}else if((choice >= 'a' && choice <= 'z') || (choice >= 'A' && choice <= 'Z')){
		if(choice == letter || choice == letter + 'a' - 'A'){
			res = GOOD_LETTER;
		}else{
			res = BAD_LETTER;
		}
	}else if(choice == '1'){
		res = PASS;
	}
	return res;
}

/** \fn get_turn_choice()
 *  \brief : retrun 0 if not a letter, 1 for pass,
 *  2 for good letter, 3 for bad letter and 4 for quit.
 *  \param : letter : letter masked and seek.
 */
char get_turn_choice(){
	char choice = getchar();
	flush_stdin_buffer();
	return choice;
}

/** \fn is_game_over()
 *  \brief : return true if the game is not finish.
 *  \param : choice : choice of player.
 *  \param : lives : nb lives of player remaining.
 */
char is_game_over(unsigned short choice, unsigned short lives){
	return (choice != QUIT && lives != 0);
}