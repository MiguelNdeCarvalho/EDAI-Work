#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <time.h>
#include "hashsep.c"

int main(int argc, char const *argv[])
{

    FILE *f;
    const unsigned MAX_LENGTH = 30;
    wchar_t line[MAX_LENGTH];
    setlocale(LC_ALL, "");
    time_t begin, end;
    HashTable T9 = InitializeTable(11);

    defineT9(T9);

    if(argc == 1)
    {
        printf("You need to pass a file name.\n");
        printf("usage: main file");
        exit(1);
    }

    else if(argc == 2)
    {
        f = fopen(argv[1], "r");

        if(f == NULL)
        {
            printf("File not found!\nCheck if the path of the file is correct.");
            exit(1);
        }
    }

    else
    {
        printf("I don't need so many arguments. Just pass the file location.\n");
        printf("usage: main file");
        exit(1);
    }
    
    begin = time(NULL);

    while (fwscanf(f, L"%ls", line) != EOF)
        convertToT9(line);
    
    end = time(NULL);
    printf("Loaded the dictionary in: %fs\n", difftime(end,begin));

    fclose(f);
    return 0;
}

