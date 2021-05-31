#include <stdlib.h>
#include <string.h>
#include "hashsep.c"

int main(int argc, char const *argv[])
{

    FILE *f;

    if(argc == 1)
    {
        printf("You need to pass a file name.\n");
        printf("usage: main file");
        exit(1);
    }

    else if (argc == 2)
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
        printf("I don`t need so many arguments. Just pass the file location.\n");
        printf("usage: main file");
        exit(1);
    }
    
    HashTable H = InitializeTable(50);

    Insert(1, H);
    Insert(2, H);
    PrintHashTable(H);
    
    fseek(f, 0, SEEK_END);
    long fsize = ftell(f);
    fseek(f, 0, SEEK_SET);  /* same as rewind(f); */

    char *string = malloc(fsize + 1);
    fread(string, 1, fsize, f);

    printf("%s", string);

    fclose(f);

    string[fsize] = 0;

    return 0;
}
