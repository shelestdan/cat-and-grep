#ifndef SRC_S21_CAT_H_
#define SRC_S21_CAT_H_

#define  _GNU_SOURCE

#include <unistd.h>
#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char *short_options = "e:ivclnhsf:o";
static struct option long_options[] = {
        {NULL, 0, NULL, 0},
};

void Read_file(char **argv, int argc, int optind); //чтение файла
void usage(void); // функция ошибки
void Flags(char f, char **argv); // свитч для выбора флага
void pattern(char **argv);
void kolizz(FILE *fileop, int argc, char *p);

char patt[7000] = {0}; //?
int flag_e; // Шаблон
int flag_i; // Игнорирует различия регистра.
int flag_v; // Инвертирует смысл поиска соответствий.
int flag_c; // Выводит только количество совпадающих строк.
int flag_l; // Выводит только совпадающие файлы.
int flag_n; // Предваряет каждую строку вывода номером строки из файла ввода.
int flag_h; // Выводит совпадающие строки, не предваряя их именами файлов.
int flag_s; // Подавляет сообщения об ошибках о несуществующих или нечитаемых файлах.
int flag_f; // Получает регулярные выражения из файла.
int flag_o; // Печатает только совпадающие (непустые) части совпавшей строки.

#endif // SRC_MYLIB_H_
