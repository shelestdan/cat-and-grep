#include "s21_cat.h"

#define STR_SIZE 10000

int main(int argc, char *argv[])
{
    int ge;
    int b = 0, e = 0, n = 0, s = 0, t = 0, v = 0;
    int lineCount = 1; // счетчик для нумерации строк
    int voidLine = 0; // шаблон пустой строки

    static struct option long_options[] =
    {
        {"number-nonblank", 0, 0, 'b'},
        {"number", 0, 0, 'n'},
        {"squeeze-blank" , 0, 0, 's'}
        
    };
    
    if (argc != 1)
    {
        while (((ge = getopt_long(argc, argv, "beEnstTv?", long_options, NULL)) != -1))
        {
            switch (ge)
            {
                case 'b': n = 0, b++; break;
                case 'v': v++; break;
                case 'E':
                case 'e': v++, e++; break;
                case 'n': n++; break;
                case 's': s++; break;
                case 'T':
                case 't': v++, t++; break;
                case '?': 
                default: printf("Флаг не распознан!\n"); exit(1);
            }
        }
        FILE *file;
        int filename = optind;

        while (filename < argc)
        {
            file = fopen(argv[filename], "r");
            if (file == NULL)
            {
                perror("Файл не найден");
                exit(1);
            }
            char lastSim = '\n';
            char lastLastSim = '0';
            char c = '0';
            for (int symCount = 0; (c = getc(file)) != EOF; symCount++)
            {   
                int endStr = 0;
                if (c == '\n') endStr += 1;

                int flag_e = 0; 
                if (e)
                {
                    if (c == '\n')
                    {
                       printf("$");
                    } 
                }
                if (v)
                {
                    if (c < 32 && c != 9 && c != 10)
                    {
                        c += 64;
                        printf("^");  
                    } else if (c == 127)
                    {
                        c = '?';
                        printf("^");  
                    }
                }
                if (s)
                {
                    if (symCount == 1 && lastSim == '\n' && c == '\n') 
                    {
                        continue;
                    }
                    if (lastLastSim == '\n' && lastSim == '\n' && c == '\n')
                    {
                        continue;
                    }
                }
                if (t != 0)
                {
                    int flag = 0;
                    if (c == '\t')
                    {
                        c = '^';
                        flag++;
                    }
                }
                if (n != 0 && b == 0)  
                {
                    if (symCount == 0 )
                    {
                        printf("%6d  ", n);
                        n++;
                }
                }
                    if (b != 0 && lastSim == '\n' && c != '\n') printf("%6d  ", b++);
                    printf("%c", c);
                    if (n != 0 && b == 0 &&  endStr != 0) printf("%6d  ", n++);
                    if (t != 0 && c == '^') printf("I");

                lastLastSim = lastSim;
                lastSim = c;
                endStr = 0;
            } 
        filename++;
        fclose(file);
        }
    }
    return 0;
}
