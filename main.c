#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <time.h>
#include "hashtable.h"

void loadDictionary(FILE *input, HashTable T9, HashTable Dictionary)
{
    setlocale(LC_ALL, "");
    time_t begin, end;
    const unsigned MAX_LENGTH = 30;
    wchar_t line[MAX_LENGTH];

    begin = time(NULL);

    while (fwscanf(input, L"%ls", line) != EOF)
        InsertWord(line, convertToT9(line, T9), Dictionary);

    end = time(NULL);
    printf("Loaded the dictionary in: %fs\n", difftime(end,begin));

    fclose(input);
}

void interface(HashTable T9, HashTable Dictionary)
{
    setlocale(LC_ALL, "");
    unsigned long input;
    char auxInput;
    wchar_t phrase[1000]=L"";
    wchar_t *temp_word;
    int i=0;

    printf("** Escreva a sua mensagem **\n");
    for(;;)
    {
        scanf("%ld", &input);
        if (input == 0)
        {
            printf("Deseja sair da aplicação (s/n)? ");
            scanf(" %c", &auxInput);
            if (auxInput == 's')
                exit(0);
            else if (auxInput == 'n')
                continue;
            else{
                printf("Deseja sair da aplicação (s/n)? ");
                scanf(" %c", &auxInput);
            }
        }
        else if (input == 1)
            printf("Mensagem: %ls\n\n\n** Escreva a sua mensagem **\n", phrase);
        else
            temp_word = getWord(input, T9, Dictionary);

        if (i == 0)
            wcscat(phrase, temp_word);
        else {
            wcscat(phrase, L" ");
            wcscat(phrase, temp_word);
        }

        i++;
    }
}

int main(int argc, char const *argv[])
{

    FILE *f;
    HashTable T9 = InitializeTable(11);
    HashTable Dictionary = InitializeTable(10000000);

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

        loadDictionary(f, T9, Dictionary);
    }

    else
    {
        printf("I don't need so many arguments. Just pass the file location.\n");
        printf("usage: main file");
        exit(1);
    }
    

    interface(T9, Dictionary);
    return 0;
}