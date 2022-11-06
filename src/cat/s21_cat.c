#include "s21_cat.h"

int main(int argc, char *argv[])
{
    int fell;
    int testing = 0;

    int b_flag = 0;
    int e_flag = 0;
    int n_flag = 0;
    int s_flag = 0;
    int t_flag = 0;
    int v_flag = 0;

    static struct option long_options[] = {
        {"number-nonblank", no_argument, no_argument, 'b'},
        {"number", no_argument, no_argument, 'n'},
        {"squeeze-blank", no_argument, no_argument, 's'}
    };

    if (argc != 1) {
        while (testing == 0 && (fell = getopt_long(argc, argv, "+ETtensbv", long_options, NULL)) != EOF) {
            switch (fell) {
                case 'b':
                    b_flag = (n_flag = 0) + 1;
                    b_flag++;
                    break;
                case 'e':
                case 'E':
                    v_flag++;
                    e_flag++;
                    break;
                case 'n':
                    n_flag = b_flag ? 0 : 1;
                    n_flag++;
                    break;
                case 's':
                    s_flag++;
                    break;
                case 'v':
                    v_flag++;
                    break;
                case 'T':
                case 't':
                    t_flag++;
                    v_flag++;
                    break;
                default:
                    exit(0);
            }
        }
        while (optind < argc)
        {
            int fileArg = optind;
            FILE *fileop;

            if ((fileop = fopen(argv[fileArg], "r")) == NULL) {
                perror("File enum");
                exit(0);
            }

            char symbol;
            char old_symbol = '0';
            int numb_symbol = 1;
            int new_str = 0;
            int s_test = 0;
            int t_test = 0;
            int v_test = 0;
            int num = 1;

            while ((symbol = getc(fileop)) != EOF) {
                if (symbol == '\n') {
                    new_str = new_str + 1;
                }
                if (s_flag) {
                    if (new_str == 1 && numb_symbol == 1) {
                        new_str = 2;
                        s_test = 1;
                    }
                    if (new_str < 3) {
                        s_test = 1;
                        if (symbol != '\n') new_str = 0;
                    } else if (symbol != '\n') {
                        new_str = 0;
                        s_test = 1;
                    }
                }
                if (n_flag && !b_flag) {
                    if ((old_symbol == '\n' || numb_symbol == 1) && !s_flag) {
                        printf("%6.d\t", num);
                        num++;
                    } else if (s_flag && (old_symbol == '\n' || numb_symbol == 1)) {
                        if (s_test) {
                            printf("%6.d\t", num);
                            num++;
                        }
                    }
                }
                if (b_flag) {
                    if (!s_flag && (numb_symbol == 1 || old_symbol == '\n') && symbol != '\n') {
                        printf("%6.d\t", num);
                        num++;
                    }
                    if (s_flag && (old_symbol == '\n' || numb_symbol == 1)) {
                        if (symbol != '\n' && s_test) {
                            printf("%6.d\t", num);
                            num++;
                        }
                    }
                }
                if (e_flag) {
                    if (!s_flag && symbol == '\n') {
                        printf("$");
                    } else if (s_test && symbol == '\n') {
                        printf("$");
                    }
                }

                if (t_flag) {
                    if (symbol == 9) t_test = 1;
                }

                if (v_flag) {
                    if (symbol >= 0 && symbol != 9 && symbol != 10 && symbol < 32) {
                        printf("^%c", symbol + 64);
                        v_test = 1;
                    } else if (symbol == 127) {
                        printf("^?");
                        v_test = 1;
                    }
                }

                if (s_flag && s_test) {
                    if (t_test) {
                        printf("^I");
                        s_test = 0;
                        t_test = 0;
                    } else if (v_test) {
                        v_test = 0;
                    } else {
                        printf("%c", symbol);
                        s_test = 0;
                    }
                } else if (!s_flag) {
                    if (t_test) {
                        printf("^");
                        printf("I");
                        t_test = 0;
                    } else if (v_test) {
                        v_test = 0;
                    } else {
                        printf("%c", symbol);
                    }
                }
                old_symbol = symbol;
                numb_symbol++;
            }
            fclose(fileop);
            optind++;
        }
    }
    return 0;
}
