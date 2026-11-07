#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "display.h"
#include "score.h"

enum value_points {ZERO, HALF = 30, PERFECT = 60};
#define COLOR_GREEN "\x1b[32m"
#define COLOR_RESET "\x1b[0m"

/** \fn clear_display()
 *  \brief : clear screen.
 */
void clear_display(){
	system("@cls||clear");
}

/** \fn display_splash_screen()
 *  \brief : display a splash screen.
 */
void display_splash_screen(){
	clear_display();
	FILE * splash_screen = fopen("../data/splash_screen.txt", "r");
	assert(splash_screen != NULL);
	if(splash_screen == NULL){
		printf("Erreur lors de l'ouverture de ../data/splash_screen.txt");
		exit(EXIT_FAILURE);
	}
	char c = fgetc(splash_screen);
	while(c != EOF){
		putchar(c);
		c = fgetc(splash_screen);
	}
	fclose(splash_screen);
	splash_screen = NULL;
}

/** \fn display_menu()
 *  \brief : display start menu.
 */
void display_menu(){
	clear_display();
	printf("\tMenu\n");
	printf("1 : règles\n");
	printf("2 : jouer\n");
	printf("3 : historique\n");
	printf("0 : quitter\n\n");
	printf("Votre choix : ");
}

/** \fn rules_display()
 *  \brief : display rules of game.
 */
void display_rules(){
	clear_display();
	printf("Le but est de retrouver la/les lettre(s) manquante(s) dans les mots.\n");
	printf("Les accents ne sont pas pris en compte.\n\n");
	printf("Un masque sera appliqué sur les lettres à retrouver.\n");
	printf("Une lettre masquée verra toutes ses occurrences cachées par le même masque.\n");
	printf("Si plusieurs lettres sont à retrouver, chacune aura son propre masque.\n\n");
	printf("Vous avez 3 vies. Vous perdez une vie lorsque vous vous trompez de lettre.\n\n");
	printf("À chaque bonne réponse, vous gagnez 5 points.\n");
	printf("Vous pouvez passer le tour, vous perdrez alors 10 points.\n\n");
	printf("Appuyez sur enter pour revenir au menu.");
}

/** \fn display_score()
 *  \brief : display score of one player.
 *  \param : one_player_info : score of one player.
 */
void display_score(score * one_player_info){
	printf("%s\t  %d\t", one_player_info->name, one_player_info->points);
		for(unsigned short j = 0; j < YEAR + 1; j++){
			if(one_player_info->date[j] < 10){
				printf(" 0%d", one_player_info->date[j]);
			}else{
				printf(" %d", one_player_info->date[j]);
			}
		}
		printf("\t   ");
		if(one_player_info->difficulty <= EASY){
			printf("  Facile");
		}else if(one_player_info->difficulty <= MEDIUM){
			printf("  Moyen");
		}else{
			printf("Difficile");
		}
		printf("\n");
}

/** \fn display_history()
 *  \brief : display history of 20 last games.
 */
void display_history(){
	clear_display();
	score * all_player_infos = load_score("../data/score.bin");
	unsigned short i = 0;
	if((all_player_infos+i)->date[DAY] == 0){
		printf("Aucune partie jouée\n");
	}else{
		printf("        Noms\t\tPoints\t    Date\tDifficulté atteinte\n");
		while(i < NB_SCORES && (all_player_infos+i)->date[DAY] != 0){
			printf("%2d) ", i + 1);
			display_score(&all_player_infos[i]);
			i++;
		}
	}
	printf("\nAppuyez sur enter pour revenir au menu.");
	free(all_player_infos);
	all_player_infos = NULL;
}

/** \fn display_error_dynamic_allocation()
 *  \brief : display a error message if dynamic allocation is fail.
 */
void display_error_dynamic_allocation(){
	printf("Erreur d'allocation dynamique\n");
	exit(EXIT_FAILURE);
}

/** \fn display_enter_name()
 *  \brief : ask the user to enter a nickname.
 */
void display_enter_name(){
	printf("Entrez votre pseudonyme (maximum 15 caractères) : ");
}

/** \fn display_turn_info()
 *  \brief : display info of current turn.
 *  \param : game : info of the current game.
 */
void display_turn_info(game_info * game){
	clear_display();
	printf("Vies restantes : %d\tNombre de points : %d\n", game->nb_lives, game->points);
	printf("\tTour %d/6\t\t", game->turn);
	if(game->turn <= EASY){
		printf("Facile\n\n");
	}else if(game->turn <= MEDIUM){
		printf("Moyen\n\n");
	}else{
		printf("Difficile\n\n");
	}
}

/** \fn display_words()
 *  \brief : display words.
 *  \param : words : words of current turn.
 *  \param : mask : mask of letter who user need to find.
 */
void display_words(char words[], char mask){
	for(unsigned short i = 0; i < strlen(words); i++){
		if(words[i] == mask){
			printf("%s%c%s", COLOR_GREEN, words[i], COLOR_RESET);
		}else{
			printf("%c", words[i]);
		}
	}
	if(mask < '!' + 3){
		printf("\n1 : passer\n0 : retourner au menu\n\n");
		printf("Entrez la lettre masquée par '%s%c%s' ", COLOR_GREEN, mask, COLOR_RESET);
	}else{
		printf("\nTour réussi ! Appuyez sur enter pour passer au tour suivant.");
	}
}


/** \fn display_bad_char()
 *  \brief : display a bad character was entered.
 *  \param : bad_char : character entered by the user.
 */
void display_bad_char(char bad_char){
	clear_display();
	printf("Oups ! '%c' n'est pas une touche valide !\n", bad_char);
	printf("Seules les lettres ainsi que 1 et 0 sont autorisées.\n\n");
	printf("Appuyez sur enter pour continuer.");
}

/** \fn display_wrong_letter()
 *  \brief : display a wrong letter was entered.
 *  \param : lives : nb lives of player remaining.
 *  \param : letter : letter entered by the user.
 */
void display_wrong_letter(unsigned short lives, char letter){
	clear_display();
	printf("Oh non ! '%c' n'était pas la bonne lettre !\n", letter);
	printf("Il vous reste %d vies.\n\n", lives);
	printf("Appuyez sur enter pour continuer.");
}

/** \fn display_end_game()
 *  \brief : display the end of the game.
 *  \param : game : info of the current game.
 */
void display_end_game(game_info * game){
	clear_display();
	printf("La partie est terminée ! ");
	if(game->nb_lives == 0){
		printf("Vous n'avez plus de vies.");
	}else{
		printf("Il vous restait %d vies.", game->nb_lives);
	}
	printf("\nVotre score est de %d points. ", game->points);
	if(game->points == PERFECT){
		printf("Ouah, c'est un score parfait ! Félicitations !");
	}else if(game->points >= HALF){
		printf("Plus de la moitié, bien joué !");
	}else if(game->points >= ZERO){
		printf("Ça ira mieux la prochaine fois !");
	}else{
		printf("Le but du jeu est de trouver les lettres, pas de passer les tours...");
	}
	printf("\n\n");
}

/** \fn display_goodbye()
 *  \brief : display an end message.
 */
void display_goodbye(){
	clear_display();
	printf("Merci d'avoir joué ! À la prochaine !\n");
}