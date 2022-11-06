#include "s21_cat.h"

#define BUFFER_SIZE 4095

int main(int argc, char *argv[])
{
    int b_flag = 0;
    int e_flag = 0;
    int n_flag = 0;
    int s_flag = 0;
    int t_flag = 0;
    int v_flag = 0;
    int new_Line;
    int line_Counter_B;
    int line_Counter_C;
    int optional;


    static struct option long_options[] = {
            {"number-nonblank", no_argument, no_argument, 'b'},
            {"number", no_argument, no_argument, 'n'},
            {"squeeze-blank", no_argument, no_argument, 's'}
    };

    if (argc != 1) {
        while ((optional = getopt_long(argc, argv, "beEnsTvt?", long_options, NULL)) != -1)
        {
            switch (optional)
            {
                case 'b':
                    b_flag = (n_flag = 0) + 1;
                    break;
                case 'e':
                case 'E':
                    e_flag++;
                    v_flag++;
                    break;
                case 'n':
                    n_flag = b_flag ? 0 : 1;
                    break;
                case 's':
                    s_flag++;
                    break;
                case 'T':
                case 't':
                    t_flag++;
                    v_flag++;
                    break;
                case 'v':
                    v_flag++;
                    break;
                default:
                    exit(1);
            }
        }

        int current_File = optind;

        FILE *file_op;

        while (optind++ < argc)
        {
            file_op = fopen(argv[optind - 1], "r");
            if (file_op == NULL)
            {
                perror("No some file is shit");
                exit(0);
            }
            for (char sym = '0'; (sym = getc(file_op)) !=EOF;)
            {
                int line_blank = 0;
                if (s_flag && line_Counter_C == 0 && sym == '\n')
                {
                    line_Counter_C += 1;
                } else if (line_Counter_C != 0 && sym == '\n')
                {
                    line_Counter_C += 1;
                    line_blank = 1;
                } else if (line_Counter_C > 1 && sym != '\n')
                {
                    line_Counter_C = 0;
                    e_flag ? printf("$\n") : printf("\n");
                    if (n_flag != 0) printf("%6d\t", n_flag++);
                } else
                {
                    line_Counter_C = 0;
                }
                if (n_flag != 0 || b_flag != 0)
                {
                    if (new_Line == 1 && !(new_Line = 0))
                    {
                        printf("%6d\t", n_flag++);
                    }
                    if (n_flag == 1) printf("%6d\t", n_flag++);
                    if (sym == '\n' && n_flag != 0 && line_blank == 0)
                    {
                        new_Line = 1;
                    }
                    if (sym == '\n' && b_flag != 0) line_Counter_B += 1;
                    if (sym != '\n' && line_Counter_B != 0 && line_Counter_C == 0)
                    {
                        if (!(line_Counter_B = 0))
                            printf("%6d\t", b_flag++);
                    }
                }
                if (sym == '\n' && e_flag && line_blank == 0) printf("$");
                if (v_flag)
                {
                    if (sym < 32 && sym != 9 && sym != 10)
                    {
                        if (sym += 64) printf("^");
                    }
                    if (sym == 127)
                    {
                        if ((sym = '?'))
                            printf("^");
                    }
                }
                if (t_flag && sym == '\t')
                {
                    if ((sym = 'I'))
                        printf("^");
                }
                if (line_blank == 0)
                    printf("%c", sym);
            }
            fclose(file_op);
            current_File++;
        }
    }
    return 0;
}
