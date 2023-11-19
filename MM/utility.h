#ifndef _UTILITY_H_
#define _UTILITY_H_
#include "data.h"

void put_time();
int file_exists(const char *path);
void init_struct(moneyData *a);
void make_dir();
int count_lines(const char *path);
void set_today();

#endif