#ifndef SRC_S21_CAT_H_
#define SRC_S21_CAT_H_

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <getopt.h>
#include <regex.h>

const char *short_options = "e:ivclnhsf:o?";
static struct option long_options[] = {
    {NULL, 0, NULL, 0},
};

void Read_file(char **argv, int argc, int optind); //чтение файла
void Flags(char f, char **argv);                   // выбор флага
void pattern(char **argv);
void kolizz(FILE *fileop, int argc, char *p); //функция отработки флагов
void Flag_V(int argc, char *p);
void Flag_O(int argc, char *p);
void No_Flag_H(int argc, char *p);
void Reg_memory();


int reg_c;
int re_ez;
int c_line = 0;
int complete = 0;
int complete_c = 0;
char *t_line = NULL;
regex_t regex;
size_t line = 1000;
size_t n_mat = 4;
regmatch_t p_mat[4];
char patt[9000] = {0}; //буфер для шаблона

int flag_e = 0; // Шаблон
int flag_i = 0; // Игнорирует различия регистра.
int flag_v = 0; // Инвертирует смысл поиска соответствий.
int flag_c = 0; // Выводит только количество совпадающих строк.
int flag_l = 0; // Выводит только совпадающие файлы.
int flag_n = 0; // Предваряет каждую строку вывода номером строки из файла ввода.
int flag_h = 0; // Выводит совпадающие строки, не предваряя их именами файлов.
int flag_s = 0; // Подавляет сообщения об ошибках о несуществующих или нечитаемых
            // файлах.
int flag_f = 0; // Получает регулярные выражения из файла.
int flag_o = 0; // Печатает только совпадающие (непустые) части совпавшей строки.

#endif // SRC_GREP_H_
