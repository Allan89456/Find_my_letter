#ifndef DISPLAY_H
#define DISPLAY_H

enum difficulty_by_turn {EASY = 2, MEDIUM = 4, HARD = 6};

typedef struct{
	unsigned short nb_lives;
	short points;
	unsigned short turn;
}game_info;

extern void clear_display();
extern void display_splash_screen();
extern void display_menu();
extern void display_rules();
extern void display_history();
extern void display_error_dynamic_allocation();
extern void display_enter_name();
extern void display_turn_info(game_info * game);
extern void display_words(char words[], char mask);
extern void display_bad_char(char letter);
extern void display_wrong_letter(unsigned short lives, char letter);
extern void display_end_game(game_info * game);
extern void display_goodbye();

#endif