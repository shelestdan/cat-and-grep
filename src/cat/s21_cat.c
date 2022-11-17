#include "s21_cat.h"

int main(int argc, char *argv[]) {
  int fell;
  options flags = {0};
  line names = {0, '0', 1, 0, 0, 0, 0, 1, 0};
  while (names.testing == 0 &&
         (fell = getopt_long(argc, argv, "+ETtensbv?", long_options, NULL)) !=
             EOF) {
    opt(fell, argc, &flags);
  }
  read_file(argc, argv, optind, &flags, &names);
  return 0;
}

void opt(char fell, int argc, options *flags) {
  if (argc != 1) {
    switch (fell) {
      case 'b':
        flags->b_flag = (flags->n_flag = 0) + 1;
        flags->b_flag = 1;
        break;
      case 'e':
      case 'E':
        flags->v_flag = 1;
        flags->e_flag = 1;
        break;
      case 'n':
        flags->n_flag = flags->b_flag ? 0 : 1;
        flags->n_flag = 1;
        break;
      case 's':
        flags->s_flag = 1;
        break;
      case 'v':
        flags->v_flag = 1;
        break;
      case 'T':
      case 't':
        flags->t_flag = 1;
        flags->v_flag = 1;
        break;
      case '?':
      default:
        exit(0);
    }
  }
}

void read_file(int argc, char **argv, int optind, options *flags, line *names) {
  while (optind < argc) {
    FILE *fileop;
    int fileArg = optind;
    if ((fileop = fopen(argv[fileArg], "r")) == NULL) {
      perror("File enum");
      exit(0);
    }
    while ((names->symbol = getc(fileop)) != EOF) {
      flag_start(flags, names);
      names->old_symbol = names->symbol;
      names->numb_symbol++;
    }
    optind++;
    fclose(fileop);
    names->num = 1;
  }
}

void flag_start(options *flags, line *names) {
  if (names->symbol == '\n') {
    names->new_str = names->new_str + 1;
  }
  if (flags->s_flag) {
    if (names->new_str == 1 && names->numb_symbol == 1) {
      names->new_str = 2;
      names->s_test = 1;
    }
    if (names->new_str < 3) {
      names->s_test = 1;
      if (names->symbol != '\n') names->new_str = 0;
    } else if (names->symbol != '\n') {
      names->new_str = 0;
      names->s_test = 1;
    }
  }
  if (flags->n_flag && !flags->b_flag) {
    if ((names->old_symbol == '\n' || names->numb_symbol == 1) &&
        !flags->s_flag) {
      printf("%6.d\t", names->num);
      names->num++;
    } else if (flags->s_flag &&
               (names->old_symbol == '\n' || names->numb_symbol == 1)) {
      if (names->s_test) {
        printf("%6.d\t", names->num);
        names->num++;
      }
    }
  }
  if (flags->b_flag) {
    if (!flags->s_flag &&
        (names->numb_symbol == 1 || names->old_symbol == '\n') &&
        names->symbol != '\n') {
      printf("%6.d\t", names->num);
      names->num++;
    }
    if (flags->s_flag &&
        (names->old_symbol == '\n' || names->numb_symbol == 1)) {
      if (names->symbol != '\n' && names->s_test) {
        printf("%6.d\t", names->num);
        names->num++;
      }
    }
  }
  if (flags->e_flag) {
    if (!flags->s_flag && names->symbol == '\n') {
      printf("$");
    } else if (names->s_test && names->symbol == '\n') {
      printf("$");
    }
  }

  if (flags->t_flag) {
    if (names->symbol == 9) names->t_test = 1;
  }

  if (flags->v_flag) {
    if (names->symbol >= 0 && names->symbol != 9 && names->symbol != 10 &&
        names->symbol < 32) {
      printf("^%c", names->symbol + 64);
      names->v_test = 1;
    } else if (names->symbol == 127) {
      printf("^?");
      names->v_test = 1;
    }
  }

  if (flags->s_flag && names->s_test) {
    if (names->t_test) {
      printf("^I");
      names->s_test = 0;
      names->t_test = 0;
    } else if (names->v_test) {
      names->v_test = 0;
    } else {
      printf("%c", names->symbol);
      names->s_test = 0;
    }
  } else if (!flags->s_flag) {
    if (names->t_test) {
      printf("^");
      printf("I");
      names->t_test = 0;
    } else if (names->v_test) {
      names->v_test = 0;
    } else {
      printf("%c", names->symbol);
    }
  }
}
