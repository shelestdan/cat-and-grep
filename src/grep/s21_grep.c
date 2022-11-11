#include "s21_gper.h"

int main(int argc, char **argv) {
    int opt;
    while ((opt = getopt_long(argc, argv, short_options, long_options, NULL)) != -1) {
        Flags(opt, argv);
    }
    pattern(argv);
    Read_file(argv, argc, optind);
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
            flag_f++;
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
    int o = optind;
    while ((names = argv[o]) != NULL) {
        if (names != 0 || strcmp(names, "-") != 0) {
            if ((fileop = fopen(names, "r"))) {
                kolizz(fileop, argc, names);
                fclose(fileop);
            } else {
                if (!flag_s) printf("Ошибка чтения", names);
            }
        }
        o++;
    }
}

void pattern(char **argv) {
    char buffer[5000] = {0};
    if (!flag_e && !flag_f) {
        sprintf(patt, sizeof(patt), "%s", argv[optind]);
        optind++;
    }
    if (flag_e && !flag_f) {
        if (patt[0] == 0) sprintf(patt, sizeof(patt), "%s", optarg);
        else {
            sprintf(buffer, sizeof(patt), "|%s0", optarg);
            strcat(patt, buffer);
        }
    }
    if(flag_f) {
        int k = 0;
        FILE *fileop_f;
        char *p = optarg;
        char line_f[1000] = {0};
        if (p != 0) {
            if ((fileop_f = fopen(p, "r"))) {
                while ((fgets(line_f, 1000, fileop_f)) != 0) {
                    if (line_f[strlen(line_f) - 1] == 10) {
                        line_f[strlen(line_f) - 1] = 0;
                    }
                    if (patt[0] == 0) {
                        snprintf(patt, sizeof(patt), "%s", line_f);
                    } else {
                        snprintf(patt, sizeof(patt), "|%s", line_f);
                        strcat(patt, buffer);
                    }
                    k++;
                }
            } else {
                if (!flag_s) {
                    printf("Ошибка чтения", p);
                }
            }
        }
    }
}


void kolizz(FILE *fileop, int argc, char *p) {
    int reg_c;
    int c_line = 0;
    int complete = 0;
    int complete_c = 0;
    char *t_line = NULL;
    regex_t regex;
    size_t line = 1000;
    size_t n_mat = 4;
    regmatch_t p_mat[4];

    if(flag_i && !flag_e) {
        if ((reg_c = regcomp(&regex, patt, REG_ICASE)) != 0) {
            printf("Failed", reg_c);
            exit(1);
        }
    } else {
        if ((reg_c = regcomp(&regex, patt, REG_EXTENDED)) != 0) {
            printf("Error!", reg_c);
            exit(1);
        }
    }

    t_line = (char*)malloc(line + 1);
    if (t_line == NULL) exit(1);

    if (t_line[strlen(t_line) - 1] == 10) {
        (t_line[strlen(t_line) - 1] = 0);
    }
    if (complete == 0) {
        if (!flag_v && !flag_c && !flag_l) {
            if ((argc - optind) > 1 && !flag_h) {
                printf("%s:", p);
            }
            if (flag_n) {
                printf("%d: ", c_line + 1);
            }
            printf("%s", t_line);
        }
    }
    if (complete && flag_v) {
        if ((argc - optind) > 1 && !flag_h) {
            printf("%s:", t_line);
        }
        printf("%s\n", t_line);
    }
    if (flag_f) {
        printf("%s\n",t_line);
    }
    if (flag_l) { printf("%s\n", fileop); }
    if (flag_c) {
        printf("%d", complete);
    }
    if (t_line != NULL) {
        free(t_line);
    } else {}
    regfree(&regex);
}
