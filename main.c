#include "hashsep.c"

int main(int argc, char const *argv[])
{
    HashTable H = InitializeTable(50);

    Insert(1, H);
    Insert(2, H);
    PrintHashTable(H);

    FILE *f = fopen("portuguese-large.txt", "rb");
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
