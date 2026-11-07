#define NAME_LEN 16
#define NB_SCORES 20

enum date {DAY, MONTH, YEAR};

typedef struct{
	short points;
	unsigned short difficulty;
	char name[NAME_LEN];
	unsigned int date[YEAR + 1];
}score;

#ifndef SCORE_H
#define SCORE_H

extern void get_today_date(unsigned int date[]);
extern score * load_score(const char * filename);
extern void add_new_score(score * actual_player_info);

#endif