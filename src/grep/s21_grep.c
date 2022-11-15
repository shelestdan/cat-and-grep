#include "s21_grep.h"

int main(int argc, char **argv) {
  int opt;
  while ((opt = getopt_long(argc, argv, short_options, long_options, NULL)) !=
         -1) {
    Flags(opt, argv);
  }
  pattern(argv);
  Read_file(argv, argc, optind);
  return 0;
}

void Flags(char f, char **argv) {
  switch (f) {
  case 'e':
    flag_e++;
    pattern(argv);
    break;
  case 'i':
    flag_i++;
    break;
  case 'v':
    flag_v++;
    break;
  case 'c':
    flag_c++;
    break;
  case 'l':
    flag_l++;
    break;
  case 'n':
    flag_n++;
    break;
  case 'h':
    flag_h++;
    break;
  case 's':
    flag_s++;
    break;
  case 'f':
    pattern(argv);
    break;
  case 'o':
    flag_o++;
    break;
  default:
    exit(1);
  }
}

void Read_file(char **argv, int argc, int optind) {
  FILE *fileop;
  char *names;
  while ((names = argv[optind]) != NULL) {
    if (names != 0 || strcmp(names, "-") != 0) {
      if ((fileop = fopen(names, "r"))) {
        kolizz(fileop, argc, names);
        fclose(fileop);
      } else {
        if (!flag_s)
          printf("Ошибка чтения");
      }
    }
    optind++;
  }
}

void pattern(char **argv) {
  char buffer[7000] = {0};
  if (!flag_e && !flag_f) {
    snprintf(patt, sizeof(patt), "%s", argv[optind]);
    optind++;
  }
  if (flag_e) {
    if (!flag_f) {
      if (patt[0] == 0) {
        snprintf(patt, sizeof(patt), "%s", optarg);
      } else {
        snprintf(buffer, sizeof(patt), "|%s", optarg);
        strcat(patt, buffer);
      }
    }
  }
  if (flag_f) {
    int k = 0;
    FILE *fileop_f;
    char *p = optarg;
    char line_f[1000] = {0};
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
          k++;
        }
      } else if (!flag_s)
        printf("Ошибка чтения");
    }
  }
}

void kolizz(FILE *fileop, int argc, char *p) {
  Reg_memory(); 
  while (((re_ez = getline(&t_line, &line, fileop)) != EOF)) {
    if ((complete = regexec(&regex, t_line, n_mat, p_mat, 0)) == 0)
      complete_c++;
    if (t_line[strlen(t_line) - 1] == 10)
      (t_line[strlen(t_line) - 1] = 0);
    if (complete == 0) {
      if (!flag_v && !flag_c && !flag_l && !flag_o) {
        if ((argc - optind) > 1 && !flag_h)
          printf("%s:", p);
        if (flag_n)
          printf("%d:", c_line + 1);
        printf("%s\n", t_line);
      }
    }
    if (flag_v) {
      Flag_V(argc, p);
    }
    if (flag_o) {
      Flag_O(argc, p);
    }
    c_line++;
  }
  if (!flag_v && flag_c && !flag_l) {
    No_Flag_H(argc, p);
    printf("%d\n", complete_c);
  }
  if (flag_v && flag_c && !flag_l) {
    No_Flag_H(argc, p);
    printf("%d\n", (c_line - complete_c));
  }
  if (!flag_v && flag_c && flag_l) {
    No_Flag_H(argc, p);
    if (complete_c > 0)
      printf("%d\n", 1);
    else
      printf("%d\n", 0);
  }
  if (flag_v && flag_c && flag_l) {
    No_Flag_H(argc, p);
    if ((c_line - complete_c) > 0)
      printf("%d\n", 1);
    else
      printf("%d\n", 0);
  }
  if (flag_l && complete_c > 0)
    printf("%s\n", p);
  if (flag_l && flag_v && complete_c == 0)
    printf("%s\n", p);
  if (t_line)
    free(t_line);
  regfree(&regex);
}

void Flag_V(int argc, char *p) {
  if (complete != 0 && flag_v && !flag_c && !flag_l && !flag_o) {
    No_Flag_H(argc, p);
    if (flag_n)
      printf("%d:", c_line + 1);
    printf("%s\n", t_line);
  }
}

void Flag_O(int argc, char *p) {
  if (complete == 0 && flag_o && !flag_v && !flag_c && !flag_l) {
    No_Flag_H(argc, p);
    if (flag_n)
      printf("%d:", c_line + 1);
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

void No_Flag_H(int argc, char *p) {
  if ((argc - optind) > 1 && !flag_h)
    printf("%s:", p);
}

void Reg_memory() {
  if (flag_i && !flag_e) {
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