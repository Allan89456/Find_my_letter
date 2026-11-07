#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#define NAME_LEN 16
#define NB_SCORES 20

typedef struct{
	short points;
	int difficulty;
	char name[NAME_LEN];
	int date[3];
}score;

/** \fn init_empty_collection()
 *  \param : all_player_empty : the score of all players.
 */
void init_empty_collection(score all_player_empty[]){
    for(unsigned short i = 0; i < NB_SCORES; i++){
        all_player_empty[i] = (score) {0, 0, {0}, {0}};
    }
}

/** \fn save()
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
 */
int get_file_size(FILE * f){
    fseek(f, 0, SEEK_END);
    int bytes = ftell(f);
    fseek(f, 0, SEEK_SET);
    return bytes;
}

/** \fn load_score()
 *  \brief : load the file filename into new_array. 
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

int main(void){
    const char file[] = "../../data/score.bin";
	score all_player_empty[NB_SCORES];
	init_empty_collection(all_player_empty);
	save_score(all_player_empty, file);
	return EXIT_SUCCESS;
}