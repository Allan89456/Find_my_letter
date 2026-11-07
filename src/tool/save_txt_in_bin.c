#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define LENGTH 50
#define LINE 10

void init_empty_collection(char tab[LINE][LENGTH]){
    for(unsigned int i = 0; i < LINE; i++){
        for(unsigned int j = 0; j < LENGTH; j++){
            tab[i][j] = '0';
        }
    }
}

int get_file_size(FILE * f){
    fseek(f, 0, SEEK_END);
    int bytes = ftell(f);
    fseek(f, 0, SEEK_SET);
    return bytes;
}

void load(char tab[LINE][LENGTH], const char * filename){
    FILE * bin = fopen(filename, "rb");
    assert(bin != NULL);
    if(bin == NULL){
        printf("Erreur d'ouverture du fichier\n");
        exit(EXIT_FAILURE);
    }
    int bytes = get_file_size(bin);
    int number_of_elements = bytes / LENGTH;
    size_t readed = fread(tab, LENGTH, number_of_elements, bin);
    assert(readed == number_of_elements);
    if(readed != number_of_elements){
        perror("Erreur de lecture dans le fichier\n");
    }
    fclose(bin);
}

void save(char tab[LINE][LENGTH], const char * filename){
    FILE * bin = fopen(filename, "wb");
    if(bin == NULL){
        printf("Erreur d'ouverture du fichier\n");
        exit(EXIT_FAILURE);
    }
    size_t writed = fwrite(tab, LENGTH, LINE, bin);
    if(writed != LINE){
        perror("Erreur d'enregistrement dans le fichier\n");
    }
    fclose(bin);
    bin = NULL;
}

void save_two_words(){
    char tab[LINE][LENGTH] = {"ARBRE\nCARPE\nAR\n",
                                "PLAGE\nGLACE\nLA\n",
                                "FLORE\nFORGE\nFOR\n",
                                "BRISE\nBASSE\nBS\n",
                                "LIVRE\nVIVRE\nVRI\n",
                                "MORSE\nRAMES\nMRS\n",
                                "PORTE\nPERTE\nPERT\n",
                                "TABLE\nBLEUE\nBLE\n",
                                "DENSE\nPENSE\nENS\n",
                                "NOIRE\nRONDE\nNOR\n"};
    const char file[] = "../../data/two_words.bin";
    save(tab, file);
}

void save_three_words(){
    char tab[LINE][LENGTH] = {"RAMEN\nATOME\nMAIRE\nAM\nMA\n",
                                "FUITE\nFRUIT\nAFFUT\nFU\nUF\nFT\nTF\nTU\nUT\n",
                                "SALON\nLACET\nMETAL\nAL\nLA\n",
                                "ROUTE\nVOTRE\nSORTE\nOR\nOT\nTO\nTR\nRT\nRO\n",
                                "TAUPE\nSAUTE\nAUTOS\nAU\nUA\nAT\nTA\nTU\nUT\n",
                                "CHIEN\nCHATS\nCHAUD\nCH\nHC\n",
                                "ROUGE\nPOULE\nMOULE\nOU\nUO\nEO\nOE\nUE\nEU\n",
                                "MOTOS\nPITON\nBOITE\nOT\nTO\n",
                                "TROIS\nTRAIT\nTROUS\nTR\nRT\n",
                                "BORDS\nABORD\nBARDE\nBR\nRB\nBD\nDB\nRD\nDR\n"};
    const char file[] = "../../data/three_words.bin";
    save(tab, file);
}

void save_four_words(){
    char tab[LINE][LENGTH] = {"CRANE\nNACRE\nRANCE\nANCRE\nCRA\nCAR\nARC\nCAN\nANC\nNRC\n",
                                "CHANT\nVACHE\nACHAT\nCHAOS\nCHA\nCAH\nACH\nAHC\nHAC\nHCA\n",
                                "LAMPE\nPALME\nAMPLE\nMAGIE\nEAM\nEMA\nAEM\nAME\nMEA\nMAE\n",
                                "APERO\nTAPER\nREPOS\nPERDU\nPER\nPRE\nREP\nRPE\nERP\nEPR\n",
                                "EXTRA\nTEXTO\nEXACT\nMIXTE\nETX\nEXT\nXTE\nXET\nTEX\nTXE\n",
                                "AUTRE\nFLEAU\nSAUVE\nVEAUX\nAUE\nAEU\nEAU\nEUA\nUEA\nUAE\n",
                                "POINT\nMINOU\nPIONS\nUNION\nNOI\nNIO\nOIN\nONI\nION\nINO\n",
                                "AIMER\nPAUME\nRAMER\nAMBRE\nAME\nAEM\nMAE\nMEA\nEAM\nEMA\n",
                                "FAUTE\nFAUNE\nOEUFS\nFUMEE\nFUE\nFEU\nEUF\nUEF\nEFU\nUFE\n",
                                "HELAS\nHACHE\nPHARE\nHAVRE\nHAE\nHEA\nAHE\nAEH\nEAH\nEHA\n"};
    const char file[] = "../../data/four_words.bin";
    save(tab, file);
}

int main(void){
    save_two_words();
    save_three_words();
    save_four_words();
	return EXIT_SUCCESS;
}