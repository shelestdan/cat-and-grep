#ifndef SRC_S21_CAT_H_
#define SRC_S21_CAT_H_

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <getopt.h>
#include <regex.h>

typedef struct {
    int flag_e; // Шаблон
    int flag_i; // Игнорирует различия регистра.
    int flag_v; // Инвертирует смысл поиска соответствий.
    int flag_c; // Выводит только количество совпадающих строк.
    int flag_l; // Выводит только совпадающие файлы.
    int flag_n; // Предваряет каждую строку вывода номером строки из файла ввода.
    int flag_h; // Выводит совпадающие строки, не предваряя их именами файлов.
    int flag_s; // Подавляет сообщения об ошибках о несуществующих или нечитаемых
                // файлах.
    int flag_f; // Получает регулярные выражения из файла.
    int flag_o; // Печатает только совпадающие (непустые) части совпавшей строки.
} options;

const char *short_options = "e:ivclnhsf:o?";
static struct option long_options[] = {
    {NULL, 0, NULL, 0},
};

void Read_file(char **argv, int argc, int optind, options *flags); //чтение файла
void Flags(char f, char **argv, options *flags);                   // выбор флага
void pattern(char **argv, options *flags);
void kolizz(FILE *fileop, int argc, char *p, options *flags); //функция отработки флагов
void Flag_V(int argc, char *p, options *flags);
void Flag_O(int argc, char *p, options *flags);
void No_Flag_H(int argc, char *p, options *flags);
void Reg_memory(options *flags);



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



#endif // SRC_GREP_H_
