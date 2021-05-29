#include <stdlib.h>
#include <string.h>
#include "hashsep.c"

int main(int argc, char const *argv[])
{

    FILE *f;

    if(argc == 1)
    {
        printf("You forgot to pass the arguments. Use -h or --help argument to see some examples.");
        exit(1);
    }

    else if (argc >= 2)
    {
        if (strcmp( argv[1], "-h") == 0 || strcmp( argv[1], "--help") == 0)
        {
            printf("usage: main -f file \n");
            exit(0);
        }

        else if (strcmp( argv[1], "-f") == 0 || strcmp( argv[1], "--file") == 0)
        {
            if(argv[2] == NULL)
            {
                printf("You didn't pass a file.\n");
                printf("Try 'main -h' for more information.");
                exit(1);
            }

            else {
                f = fopen(argv[2], "r");

                if(f == NULL)
                {
                    printf("File not found!\nCheck if the path of the file is correct.");
                    return 1;
                }
            }
        }

        else
        {
            printf("Unknown option: %s\n", argv[1]);
            printf("Try 'main -h' for more information.");
            exit(1);
        } 

    }

    else if(argc > 3)
    {
        printf("I don`t need so many arguments. Use -h or --help argument to see some examples.");
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
