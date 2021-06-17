#include <stdio.h>
#include <stdlib.h>
#include "hashtable.h"

int main(int argc, char const *argv[])
{
    FILE *f;
    HashTable T9 = InitializeTable(11); //Create T9 Hashtable
    HashTable Dictionary = InitializeTable(10000000); //Create Dictionary Hashtable

    if(argc == 1) //When user didn't pass args
    {
        printf("You need to pass a file name.\n");
        printf("usage: main file");
        exit(1);
    }

    else if(argc == 2)
    {
        f = fopen(argv[1], "r");

        if(f == NULL) //Check if file exists
        {
            printf("File not found!\nCheck if the path of the file is correct.");
            exit(1);
        }

        LoadT9Keys(T9);
        LoadDictionary(f, T9, Dictionary);
    }

    else //When user passed more then 1 arg
    {
        printf("I don't need so many arguments. Just pass the file location.\n");
        printf("usage: main file");
        exit(1);
    }
    

    interface(T9, Dictionary);
    return 0;
}