#ifndef KEYBOARD_H
#define KEYBOARD_H

enum possible_choice {NOT_A_LETTER, PASS, GOOD_LETTER, BAD_LETTER, QUIT};

extern void flush_stdin_buffer();
extern char get_menu_choice();
extern void get_player_name(char name[]);
extern unsigned short compare_choice(char choice, char letter);
extern char get_turn_choice();
extern char is_game_over(unsigned short choice, unsigned short lives);

#endif