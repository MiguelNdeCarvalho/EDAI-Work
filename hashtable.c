#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <locale.h>
#include <math.h>
#include <stdbool.h> 
#include <time.h>
#include "fatal.h"
#include "hashtable.h"

#define MinTableSize (10)
typedef unsigned int Index;
typedef Position List;

struct ListNode
{
    wchar_t *Element;
    Position    Next;
};

struct HashTbl
{
    int TableSize;
    List *TheLists;
};


static int NextPrime( int N )
{
    if(N % 2 == 0)
        N++;
    for(;;N += 2)
    {
        for(int i = 3; i * i <= N; i += 2)
            if(N % i == 0)
                goto ContOuter;
        return N;
    ContOuter:;
    }
}

long Hash ( unsigned long Key, int TableSize ){
    return Key % TableSize;
}


HashTable InitializeTable(int TableSize)
{
    HashTable H;
    int i;

    if(TableSize < MinTableSize)
    {
        Error("Table size too small");
        return NULL;
    }

    /* Allocate table */
    H = malloc(sizeof(struct HashTbl));
    if(H == NULL)
        FatalError( "Out of space!!!" );

    H->TableSize = NextPrime(TableSize);

    /* Allocate array of lists */
    H->TheLists = malloc(sizeof(List) * H->TableSize);
    if(H->TheLists == NULL)
        FatalError("Out of space!!!");

    /* Allocate list headers */
    for(i = 0; i < H->TableSize; i++)
    {
        H->TheLists[i] = malloc(sizeof(struct ListNode));
        if(H->TheLists[i] == NULL)
            FatalError("Out of space!!!");
        else
            H->TheLists[i]->Next = NULL;
    }
    return H;
}

Position Find(wchar_t *Key, unsigned long Value, HashTable H)
{
    List L = H->TheLists[Value];
    Position P = L->Next;

    while(P != NULL && wcscmp(P->Element, Key) != 0)
        P = P->Next;
    
    return P;
}

int FindWOValue(wchar_t Key, HashTable H)
{
    for(int i=0 ; i < H->TableSize ; i++)
    {
        Position P = H->TheLists[i]->Next;
        if(P != NULL)
        {
            while(P != NULL)
            {
                if(Key == P->Element[0])
                    return i;
                
                P = P->Next;
            }
        }
    }
    return 0;
}


/* Insert the Element Key passed as argument in HashTable H */
void Insert(wchar_t *Key, unsigned long Value, HashTable H)
{
    Position Pos, NewCell;
    List L;

    Pos = Find(Key, Value, H);

    /* Key is not found */
    if(Pos == NULL){  
        NewCell = malloc(sizeof(struct ListNode));

        if(NewCell == NULL)
            FatalError( "Out of space!!!" );
        
        else
        {
            L = H->TheLists[Value];

            while (L != NULL ) {
                if(L-> Next == NULL)
                    break;
                L = L-> Next;                
            }
            
            NewCell->Next = L->Next;
            NewCell->Element = malloc(sizeof(wchar_t*) * wcslen(Key));
            wcpcpy(NewCell->Element, Key);
            L->Next = NewCell;
            //print_element(NewCell->Element);
        }
    }
}

void InsertWord(wchar_t *Key, unsigned long K9_Value, HashTable H)
{
    Position Pos, NewCell;
    List L;

    unsigned long Value = Hash(K9_Value, H->TableSize);
    Pos = Find(Key, Value, H);

    /* Key is not found */
    if(Pos == NULL){  
        NewCell = malloc(sizeof(struct ListNode));

        if(NewCell == NULL)
            FatalError( "Out of space!!!" );
        
        else
        {
            L = H->TheLists[Value];

            while (L != NULL ) {
                if(L-> Next == NULL)
                    break;
                L = L-> Next;                
            }

            NewCell->Next = L->Next;
            NewCell->Element = malloc(sizeof(wchar_t*) * wcslen(Key));
            wcpcpy(NewCell->Element, Key);
            L->Next = NewCell;
        }
    }
}


wchar_t Retrieve(Position P)
{
    return *P->Element;
}

void DestroyTable(HashTable H)
{
    int i;

    for(i = 0; i < H->TableSize; i++)
    {
        Position P = H->TheLists[i];
        Position Tmp;

        while(P != NULL)
        {
            Tmp = P->Next;
            free(P);
            P = Tmp;
        }
    }

    free(H->TheLists);
    free(H);
}

HashTable MakeEmpty(HashTable T)
{
    /*for(int i=0 ; i<T->TableSize; i++)
    {
        Position P = T->TheLists[i];
        while(P->Next != NULL)
        {
            P = P->Next;
            free(P);
        }
    }*/

    printf("\nTODO()\n");
    return T;
}


void PrintHashTable(HashTable T)
{
    printf("* Printing HashTable *\n");

    for(int i=0 ; i < T->TableSize ; i++)
    {   
        Position P = T->TheLists[i]->Next;
        if(P != NULL)
        {
            printf("%d\t[", i);
            while(P != NULL)
            {
                setlocale(LC_ALL, "");
                printf("%ls", P->Element);
                P = P->Next;

                //If is not the last element
                if(P != NULL)
                    printf(", ");
            }
            printf("]\n");
        }
        else
            printf("%d\t[%s]\n", i, "");
    }
}

// Load default T9Keys

void LoadT9Keys(HashTable T)
{
    // key 2
    Insert(L"a", 2, T);
    Insert(L"b", 2, T);
    Insert(L"c", 2, T);
    Insert(L"á", 2, T);
    Insert(L"à", 2, T);
    Insert(L"â", 2, T);
    Insert(L"ã", 2, T);
    Insert(L"ç", 2, T);
    // key 3
    Insert(L"d", 3, T);
    Insert(L"e", 3, T);
    Insert(L"f", 3, T);
    Insert(L"é", 3, T);
    Insert(L"ê", 3, T);
    // key 4
    Insert(L"g", 4, T);
    Insert(L"h", 4, T);
    Insert(L"i", 4, T);
    Insert(L"í", 4, T);
    // key 5
    Insert(L"j", 5, T);
    Insert(L"k", 5, T);
    Insert(L"l", 5, T);
    // key 6
    Insert(L"m", 6, T);
    Insert(L"n", 6, T);
    Insert(L"o", 6, T);
    Insert(L"ó", 6, T);
    Insert(L"ô", 6, T);
    Insert(L"õ", 6, T);
    // key 7
    Insert(L"p", 7, T);
    Insert(L"q", 7, T);
    Insert(L"r", 7, T);
    Insert(L"s", 7, T);
    // key 8
    Insert(L"t", 8, T);
    Insert(L"u", 8, T);
    Insert(L"v", 8, T);
    Insert(L"ú", 8, T);
    // key 9
    Insert(L"w", 9, T);
    Insert(L"x", 9, T);
    Insert(L"y", 9, T);
    Insert(L"z", 9, T);
}

// Load Words from dictionary to the Hashtable
void LoadDictionary(FILE *input, HashTable T9, HashTable Dictionary)
{
    setlocale(LC_ALL, "");
    time_t begin, end;
    const unsigned MAX_LENGTH = 30;
    wchar_t line[MAX_LENGTH];

    begin = time(NULL);

    while (fwscanf(input, L"%ls", line) != EOF)
        InsertWord(line, ConvertWordToT9Keys(line, T9), Dictionary);

    end = time(NULL);
    printf("Loaded the dictionary in: %fs\n", difftime(end,begin));

    fclose(input);
}

//Check if we find a special character "'" and returns his position or 0 when there isn't
int CheckExistenceOfSpecialCharacter(wchar_t *input)
{
    wchar_t *pass = L"'";

    for (size_t i=0; i<wcslen(input); i++) 
    {
        if(input[i] == pass[0])
        {
            return i; //return the index of the array where it is
        }
    }
    return 0;
}

//Convert the Word into T9Keys
unsigned long ConvertWordToT9Keys(wchar_t *input, HashTable H)
{
    unsigned long total=0; //Converted in T9Keys
    int specialCharacterLine = CheckExistenceOfSpecialCharacter(input);
    bool containsSpecialCharacters;
    
    if(CheckExistenceOfSpecialCharacter(input) == 0)
        containsSpecialCharacters = false;
    else
        containsSpecialCharacters = true;

    for (size_t i=0; i<wcslen(input); i++) 
    {
        int value = FindWOValue(input[i], H); // Index of special character

        if(containsSpecialCharacters == true && (int) i < specialCharacterLine)
            total+= (value * pow(10,wcslen(input)-i-2)); // -2, because it doesn't count with the special character
        else
            total+= (value * pow(10,wcslen(input)-i-1));
    }
    return total; //return the value of the word converted
}

wchar_t* SuggestWord(unsigned long input, HashTable T9, HashTable Dictionary)
{
    unsigned long index = Hash(input, Dictionary->TableSize);
    char choice; // Register user interaction (s/n)
    wchar_t *inputWord= malloc(sizeof(wchar_t*) * 30); //Allocate space for the word that user wants to add (not on the dictionary)

    Position P = Dictionary->TheLists[index]->Next;

    if(P != NULL)
    {
        while(P != NULL)
        {   
            printf("Sugestão: %ls, aceita (s/n)? ", P->Element);
            scanf(" %c", &choice);
            
            if (choice == 's')
            {
                return P->Element;
                break;
            }
            else if (choice == 'n')
            {
                P = P->Next;
                if (P == NULL)
                { //Fazer scan da nova palavra e adicionar na Hashtable
                    setlocale(LC_ALL, "");
                    printf("Não existem mais sugestões; introduza a palavra do teclado.\n");
                    scanf("%ls", inputWord);
                    InsertWord(inputWord, ConvertWordToT9Keys(inputWord, T9), Dictionary);
                    return inputWord;
                }
            }
            else
            {
                printf("Sugestão: %ls, aceita (s/n)? ", P->Element);
                scanf("%c", &choice);
            }
        }
    }
    return L"";//Return nothing, just to fix warnings by GCC
}

// Where the prompted interface that user sees is.
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
            printf("Mensagem: %ls\n\n** Escreva a sua mensagem **\n", phrase);
        else
            temp_word = SuggestWord(input, T9, Dictionary);

        if (i == 0)
            wcscat(phrase, temp_word);
        else {
            wcscat(phrase, L" ");
            wcscat(phrase, temp_word);
        }

        i++;
    }
}