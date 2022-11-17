#ifndef SRC_S21_CAT_H
#define SRC_S21_CAT_H
#define _GNU_SOURCE

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct {
  char symbol;
  char old_symbol;
  int numb_symbol;
  int new_str;
  int s_test;
  int t_test;
  int v_test;
  int num;
  int testing;
} line;

typedef struct {
  int b_flag;
  int e_flag;
  int n_flag;
  int s_flag;
  int t_flag;
  int v_flag;
} options;

static struct option long_options[] = {
    {"number-nonblank", no_argument, no_argument, 'b'},
    {"number", no_argument, no_argument, 'n'},
    {"squeeze-blank", no_argument, no_argument, 's'}};

void opt(char fell, int argc, options *flags);
void read_file(int argc, char **argv, int optind, options *flags, line *names);
void flag_start_s_n(options *flags, line *names);
void flag_start_b_s_e(options *flags, line *names);
void flag_start_s_v(options *flags, line *names);
void fails(void);

#endif  // SRC_S21_CAT_H_