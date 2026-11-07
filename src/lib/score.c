#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>
#include "score.h"

/** \fn get_today_date()
 *  \brief : return today's date
 *  \param : date : tab for current date.
 */
void get_today_date(unsigned int date[]){
    time_t timestamp = time(NULL);
    struct tm * now = localtime(&timestamp);
    date[DAY] = now->tm_mday;
    date[MONTH] = now->tm_mon+1;
    date[YEAR] = now->tm_year+1900;
}

/** \fn save_score()
 *  \brief : save score into filenam.
 *  \param : array : adress of struct array.
 *  \param : filename : file to save.
 */
void save_score(score * array, const char * filename){
    FILE * bin = fopen(filename, "wb");
    assert(bin != NULL);
    if(bin == NULL){
        printf("Erreur d'ouverture du fichier %s\n", filename);
        exit(EXIT_FAILURE);
    }
    size_t writed = fwrite(array, sizeof(score), NB_SCORES, bin);
    if(writed != NB_SCORES){
        perror("Erreur d'enregistrement dans le fichier\n");
    }
    fclose(bin);
    bin = NULL;
}

/** \fn get_file_size()
 *  \brief : return size of file. 
 *  \param : f : file who want size.
 */
int get_file_size(FILE * f){
    fseek(f, 0, SEEK_END);
    int bytes = ftell(f);
    fseek(f, 0, SEEK_SET);
    return bytes;
}

/** \fn load_score()
 *  \brief : load the file filename into new_array.
 *  \param : filename : file to load.
 */
score * load_score(const char * filename){
    FILE * bin = fopen(filename, "rb");
    assert(bin != NULL);
    if(bin == NULL){
        printf("Erreur d'ouverture du fichier %s\n", filename);
        exit(EXIT_FAILURE);
    }
    int bytes = get_file_size(bin);
    score * new_array = malloc(sizeof(score *) * bytes);
    assert(new_array != NULL);
    if(new_array == NULL){
        printf("Erreur d'allocation mémoire pour new_array\n");
        exit(EXIT_FAILURE);
    }
    size_t readed = fread(new_array, sizeof(score), NB_SCORES, bin);
    assert(readed == NB_SCORES);
    if(readed != NB_SCORES){
        perror("Erreur de lecture dans le fichier\n");
    }
    fclose(bin);
    bin = NULL;
    return new_array;
}

/** \fn replace()
 *  \brief : replace a score by another.
 *  \param : old_score : the old score.
 *  \param : new_score : the score who replaces old_score.
 */
void replace(score * old_score, score * new_score){
    old_score->points = new_score->points;
    old_score->difficulty = new_score->difficulty;
    strcpy(old_score->name, new_score->name);
    for(unsigned short i = 0; i <= YEAR; i++){
        old_score->date[i] = new_score->date[i];
    }
}

/** \fn search_place_new_score()
 *  \brief : return the place for the new score to save. 
 *  \param : actual_player_info : score of the player at save.
 *  \param : all_player_infos : score of all ancient players.
 */
unsigned short search_place_new_score(score * actual_player_info, score * all_player_infos){
    unsigned short i = 0;
    while(i < NB_SCORES && actual_player_info->points < (all_player_infos+i)->points && (all_player_infos+i)->date[DAY] != 0){
        i++;
    }
    return i;
}

/** \fn search_most_old()
 *  \brief : return the place of the oldest score.
 *  \param : all_player_infos : score of all ancient players.
 */
unsigned short search_most_old(score * all_player_infos){
    unsigned short most_old = NB_SCORES - 1;
    for(short i = most_old - 1; i >= 0; i--){
        for(short j = YEAR; j >= DAY; j--){
            if((all_player_infos+i)->date[j] < (all_player_infos+most_old)->date[j]){
                most_old = i;
                j = DAY;
            }else if((all_player_infos+i)->date[j] > (all_player_infos+most_old)->date[j]){
                j = DAY;
            }
        }  
    }
    return most_old;
}

/** \fn shift_score()
 *  \brief : shift ancient player info and delete the most old.
 *  \param : all_player_infos : score of all ancient players.
 *  \param : begin : first case to shift.
 *  \param : end : last case to shift.
 */
void shift_score(score * all_player_infos, unsigned short begin, unsigned short end){
    while(begin > end){
        replace((all_player_infos+begin), (all_player_infos+begin-1));
        begin--;
    }
    while(begin < end){
        replace((all_player_infos+begin), (all_player_infos+begin+1));
        begin++;
    }
}

/** \fn add_new_score()
 *  \brief : add the score of the current player at the history.
 *  \param : actual_player_info : score of player.
 */
void add_new_score(score * actual_player_info){
    const char file[] = "../data/score.bin";
    score * all_player_infos = load_score(file);
    if((all_player_infos+NB_SCORES-1)->date[DAY] == 0){
        unsigned short place_of_new_score = search_place_new_score(actual_player_info, all_player_infos);
        if((all_player_infos+place_of_new_score)->date[DAY] != 0){
            short j = NB_SCORES-1;
            while((all_player_infos+j)->date[DAY] == 0){
                j--;
            }
            shift_score(all_player_infos, j+1, place_of_new_score);
        }
        replace((all_player_infos+place_of_new_score), actual_player_info);
    }else{
        unsigned short most_old = search_most_old(all_player_infos);
        unsigned short place_of_new_score = search_place_new_score(actual_player_info, all_player_infos);
        if(place_of_new_score == NB_SCORES){
            place_of_new_score--;
        }
        if(most_old > place_of_new_score){
            shift_score(all_player_infos, most_old, place_of_new_score);
        }else if(most_old < place_of_new_score){
            place_of_new_score--;
            shift_score(all_player_infos, most_old, place_of_new_score);
        }
        replace((all_player_infos+place_of_new_score), actual_player_info);
    }
    save_score(all_player_infos, file);
    free(all_player_infos);
    all_player_infos = NULL;
}