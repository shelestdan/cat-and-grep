#include "s21_grep.h"

int main(int argc, char **argv) {
  options flags = {0};
  int opt;
  while ((opt = getopt_long(argc, argv, short_options, long_options, NULL)) !=
         -1) {
    Flags(opt, argv, &flags);
  }
  pattern(argv, &flags);
  Read_file(argv, argc, optind, &flags);
  return 0;
}

void Flags(char f, char **argv, options *flags) {
  switch (f) {
  case 'e':
    flags->flag_e = 1;
    pattern(argv, flags);
    break;
  case 'i':
    flags->flag_i = 1;
    break;
  case 'v':
    flags->flag_v = 1;
    break;
  case 'c':
    flags->flag_c = 1;
    break;
  case 'l':
    flags->flag_l = 1;
    break;
  case 'n':
    flags->flag_n = 1;
    break;
  case 'h':
    flags->flag_h = 1;
    break;
  case 's':
    flags->flag_s = 1;
    break;
  case 'f':
    flags->flag_f = 1;
    pattern(argv, flags);
    break;
  case 'o':
    flags->flag_o = 1;
    break;
  case '?':
    default:
      fprintf(stderr, "Флаг не найден\n");
      exit(1);
}
}

void Read_file(char **argv, int argc, int optind, options *flags) {
  FILE *fileop;
  char *names;
  int i = optind;
  while ((names = argv[i]) != NULL) {
    if (names != 0 || strcmp(names, "-") != 0) {
      if ((fileop = fopen(names, "r"))) {
        kolizz(fileop, argc, names, flags);
        fclose(fileop);
      } else {
        if (!flags->flag_s) {
          perror("Ошибка чтения");
          exit(1);
        }
      }
    }
    i++;
  }
}

void pattern(char **argv, options *flags) {
  char buffer[9000] = {0};
  if (!flags->flag_e && !flags->flag_f) {
    snprintf(patt, sizeof(patt), "%s", argv[optind]);
    optind++;
  }
  if (flags->flag_e && !flags->flag_f) {
      if (patt[0] == 0) {
        snprintf(patt, sizeof(patt), "%s", optarg);
      } else {
        snprintf(buffer, sizeof(patt), "|%s", optarg);
        strcat(patt, buffer);
      }
  }
  if (flags->flag_f) {
    FILE *fileop_f;
    char *p = optarg;
    char line_f[1010] = {0};
    if (p != NULL) {
      if ((fileop_f = fopen(p, "r"))) {
        while ((fgets(line_f, 1000, fileop_f)) != NULL) {
          if (line_f[strlen(line_f) - 1] == 10) {
            line_f[strlen(line_f) - 1] = 0;
          }
          if (patt[0] == 0) {
            snprintf(patt, sizeof(patt), "%s", line_f);
          } else {
            snprintf(buffer, sizeof(patt), "|%s", line_f);
            strcat(patt, buffer);
          }
        }
      } else {
        if (!flags->flag_s) {
        perror("Ошибка чтения");
        exit(1);
      }
      }
    }
  }
}

void kolizz(FILE *fileop, int argc, char *p, options *flags) {
 c_line = 0;
 complete = 0;
 complete_c = 0;
  Reg_memory(flags); 
  while (((re_ez = getline(&t_line, &line, fileop)) != EOF)) {
    c_line++;
    if ((complete = regexec(&regex, t_line, n_mat, p_mat, 0)) == 0)
      complete_c++;
    if (t_line[strlen(t_line) - 1] == 10)
      (t_line[strlen(t_line) - 1] = 0);
    if (complete == 0 && !flags->flag_v && !flags->flag_c && !flags->flag_l && !flags->flag_o) {
        No_Flag_H(argc, p, flags);
        if (flags->flag_n) {
          printf("%d:", c_line);
        }
      printf("%s\n", t_line);
    }
    if (flags->flag_v) {
      Flag_V(argc, p, flags);
    }
    if (flags->flag_o) {
      Flag_O(argc, p, flags);
    }
  }
  if (!flags->flag_v && flags->flag_c && !flags->flag_l) {
    No_Flag_H(argc, p, flags);
    printf("%d\n", complete_c);
  }
  if (flags->flag_v && flags->flag_c && !flags->flag_l) {
    No_Flag_H(argc, p, flags);
   printf("%d\n", (c_line - complete_c));
  }
  if (!flags->flag_v && flags->flag_c && flags->flag_l) {
    No_Flag_H(argc, p, flags);
    if (complete_c > 0)
      printf("%d\n", 1);
    else
      printf("%d\n", 0);
  }
  if (flags->flag_v && flags->flag_c && flags->flag_l) {
    No_Flag_H(argc, p, flags);
    if ((c_line - complete_c) > 0)
      printf("%d\n", 1);
    else
      printf("%d\n", 0);
  }
  if (flags->flag_l && complete_c > 0)
    printf("%s\n", p, flags);
  if (flags->flag_l && flags->flag_v && complete_c == 0)
    printf("%s\n", p, flags);
  if (t_line)
    free(t_line);
  regfree(&regex);
}

void Flag_V(int argc, char *p, options *flags) {
  if (complete != 0 && flags->flag_v && !flags->flag_c && !flags->flag_l) {
    No_Flag_H(argc, p, flags);
    if (flags->flag_n) {
      printf("%d:", c_line);
    }
   printf("%s\n", t_line);
  }
}

void Flag_O(int argc, char *p, options *flags) {
  if (complete == 0 && flags->flag_o && !flags->flag_v && !flags->flag_c && !flags->flag_l) {
    No_Flag_H(argc, p, flags);
    if (flags->flag_n)
      printf("%d:", c_line);
    char *t_line_o = t_line;
    for (unsigned int i = 0; i < strlen(t_line_o); i++) {
      if (regexec(&regex, t_line_o, n_mat, p_mat, 0))
        break;
      unsigned int of = 0;
      for (size_t k = 0; k <= n_mat; k++) {
        if (p_mat[k].rm_so == -1)
          break;
        if (k == 0)
          of = p_mat[k].rm_eo;
        char line_c[strlen(t_line_o) + 1];
        strcpy(line_c, t_line_o);
        line_c[p_mat[k].rm_eo] = 0;
        printf("%s\n", (line_c + p_mat[k].rm_so));
      }
      t_line_o += of;
    }
  }
}

void No_Flag_H(int argc, char *p, options *flags) {
  if ((argc - optind) > 1 && !(flags -> flag_h))
    printf("%s:", p);
}

void Reg_memory(options *flags) {
  if (flags->flag_i) {
    if ((reg_c = regcomp(&regex, patt, REG_ICASE)) != 0) {
      printf("failed %d", reg_c);
      exit(1);
    }
  } else {
    if ((reg_c = regcomp(&regex, patt, REG_EXTENDED)) != 0) {
      printf("failed %d", reg_c);
      exit(1);
    }
  }
  t_line = (char *)malloc(line + 1);
  if (t_line == NULL) {
    exit(1);
  }
}