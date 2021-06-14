#include <stdlib.h>
#include <string.h>
#include "hashsep.c"

void defineT9()
{
    HashTable T9 = InitializeTable(11);
    // key 2
    Insert(L'a', 2, T9);
    Insert(L'b', 2, T9);
    Insert(L'c', 2, T9);
    Insert(L'á', 2, T9);
    Insert(L'à', 2, T9);
    Insert(L'â', 2, T9);
    Insert(L'ã', 2, T9);
    Insert(L'ç', 2, T9);
    // key 3
    Insert(L'd', 3, T9);
    Insert(L'e', 3, T9);
    Insert(L'f', 3, T9);
    Insert(L'é', 3, T9);
    Insert(L'ê', 3, T9);
    // key 4
    Insert(L'g', 4, T9);
    Insert(L'h', 4, T9);
    Insert(L'i', 4, T9);
    Insert(L'í', 4, T9);
    // key 5
    Insert(L'j', 5, T9);
    Insert(L'k', 5, T9);
    Insert(L'l', 5, T9);
    // key 6
    Insert(L'm', 6, T9);
    Insert(L'n', 6, T9);
    Insert(L'o', 6, T9);
    Insert(L'ó', 6, T9);
    Insert(L'ô', 6, T9);
    Insert(L'õ', 6, T9);
    // key 7
    Insert(L'p', 7, T9);
    Insert(L'q', 7, T9);
    Insert(L'r', 7, T9);
    Insert(L's', 7, T9);
    // key 8
    Insert(L't', 8, T9);
    Insert(L'u', 8, T9);
    Insert(L'v', 8, T9);
    Insert(L'ú', 8, T9);
    // key 9
    Insert(L'w', 9, T9);
    Insert(L'x', 9, T9);
    Insert(L'y', 9, T9);
    Insert(L'z', 9, T9);

    PrintHashTable(T9);
}

int main(int argc, char const *argv[])
{

    FILE *f;

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
    
    //HashTable H = InitializeTable(50);

    //Insert(1, H);
    //Insert(2, H);
    //PrintHashTable(H);
    
    fseek(f, 0, SEEK_END);
    long fsize = ftell(f);
    fseek(f, 0, SEEK_SET);  /* same as rewind(f); */

    char *string = malloc(fsize + 1);
    fread(string, 1, fsize, f);

    //printf("%s", string);

    fclose(f);

    string[fsize] = 0;

    defineT9();

    return 0;
}

