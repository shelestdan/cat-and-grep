#ifndef SRC_S21_CAT_H
#define SRC_S21_CAT_H
#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <unistd.h>

void opt(char fell, int argc);
void read_file(int argc, char** argv, int optind);
void flag_start(char symbol);

static struct option long_options[] = {
        {"number-nonblank", no_argument, no_argument, 'b'},
        {"number", no_argument, no_argument, 'n'},
        {"squeeze-blank", no_argument, no_argument, 's'}
};

char symbol;
char old_symbol = '0';
int numb_symbol = 1;
int new_str = 0;
int s_test = 0;
int t_test = 0;
int v_test = 0;
int num = 1;

int fell;
int testing = 0;

int b_flag = 0;
int e_flag = 0;
int n_flag = 0;
int s_flag = 0;
int t_flag = 0;
int v_flag = 0;

#endif  // SRC_S21_CAT_H_