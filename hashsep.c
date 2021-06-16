#include "fatal.h"
#include "hashsep.h"
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <locale.h>

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


/* Return next prime; assume N >= MinTableSize */
static int NextPrime( int N )
{
    if(N % 2 == 0)
        N++;
    for(;;N += 2)
    {
        for(int i = 3; i * i <= N; i += 2)
            if(N % i == 0)
                goto ContOuter;  /* Sorry about this! */
        return N;
    ContOuter:;
    }
}

/* Hash function for ints */
Index Hash( ElementType Key, int TableSize ){
    return Key % TableSize;
}


/* Initialize the Table, 
making the correspondent malloc() and allocate the array of lists and them Headers 
to use on HashTable positions */
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

/* Find a Key in HashTable */
Position Find(wchar_t *Key, int Value, HashTable H)
{
    List L = H->TheLists[Value];
    Position P = L->Next;

    while(P != NULL && wcscmp(P->Element, Key) != 0)
        P = P->Next;
    
    return P;
}

Position FindWOValue(wchar_t *Key, HashTable H)
{
    List L = H->TheLists[Hash(*Key, H->TableSize)];
    Position P = L->Next;

    while(P != NULL && wcscmp(P->Element, Key) != 0)
        P = P->Next;
    
    return P;
}


/* Insert the Element Key passed as argument in HashTable H */
void Insert(wchar_t *Key, int Value, HashTable H)
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
            NewCell->Next = L->Next;
            NewCell->Element = malloc(sizeof(Key));
            wcpcpy(NewCell->Element, Key);
            L->Next = NewCell;
            //print_element(NewCell->Element);
        }
    }
    /* Key is found in HashTable */
    else
    {   
        //If the key is found in HT, we need to create another node 
        //to insert the element inside the list of the current hashtable position
        NewCell = malloc( sizeof( struct ListNode ) );
        Pos->Next = NewCell;
        NewCell->Element = malloc(sizeof(Key));
        wcpcpy(NewCell->Element, Key);
        NewCell->Next = NULL;
    }
}

/* Print the Element in Node P */
wchar_t Retrieve(Position P)
{
    return *P->Element;
}

/* Free the ram occupied from HashTable */
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


// /* Removes the Element X from the HashTable */
// HashTable Delete(ElementType X, HashTable T){
    
//     // Find the key of the Element X
//     int key = Hash(X, T->TableSize);

//     //Key finded
//     if(key != -1)
//     {
//         //If the key is finded we need to iterate over the List of that Key Hashtable Position to find the X
//         Position prevP = T->TheLists[key];
//         Position P = T->TheLists[key]->Next;

//         //X finded 
//         while(P != NULL)
//         {
//             if(P->Element == X && P->Next != NULL)
//             {   
//                 printf("Deleted %d at index %d from HashTable\n", P->Element, key);
//                 prevP->Next = P->Next->Next;
//                 return T;
//             }

//             else if(P->Element == X && P->Next == NULL)
//             {
//                 prevP->Next = NULL;
//                 printf("Deleted %d at index %d from HashTable\n", P->Element, key);
//                 return T;
//             }

//             prevP = P;
//             P = P->Next;       
//         }
//     }

//     //Key not finded 
//     else
//         FatalError("Element not present in HashTable");
    
//     return T;
// }


/* Free the allocated memory of Hashtable */
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


/* Display HashTable in Terminal */
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

void defineT9(HashTable T)
{
    // key 2
    Insert(L"ç", 2, T);
    Insert(L"ã", 2, T);
    Insert(L"â", 2, T);
    Insert(L"à", 2, T);
    Insert(L"á", 2, T);
    Insert(L"c", 2, T);
    Insert(L"b", 2, T);
    Insert(L"a", 2, T);
    // key 3
    Insert(L"ê", 3, T);
    Insert(L"é", 3, T);
    Insert(L"f", 3, T);
    Insert(L"e", 3, T);
    Insert(L"d", 3, T);
    // key 4
    Insert(L"í", 4, T);
    Insert(L"i", 4, T);
    Insert(L"h", 4, T);
    Insert(L"g", 4, T);
    // key 5
    Insert(L"l", 5, T);
    Insert(L"k", 5, T);
    Insert(L"j", 5, T);
    // key 6
    Insert(L"õ", 6, T);
    Insert(L"ô", 6, T);
    Insert(L"ó", 6, T);
    Insert(L"o", 6, T);
    Insert(L"n", 6, T);
    Insert(L"m", 6, T);
    // key 7
    Insert(L"s", 7, T);
    Insert(L"r", 7, T);
    Insert(L"q", 7, T);
    Insert(L"p", 7, T);
    // key 8
    Insert(L"ú", 8, T);
    Insert(L"v", 8, T);
    Insert(L"u", 8, T);
    Insert(L"t", 8, T);
    // key 9
    Insert(L"z", 9, T);
    Insert(L"y", 9, T);
    Insert(L"x", 9, T);
    Insert(L"w", 9, T);
}

long convertToT9(wchar_t *input)
{
    setlocale(LC_ALL, "");
    for (int i=0; i<wcslen(input); i++) {
        //printf("%d",FindWOValue(input[i], T9));
        
        //printf("%lc\n", input[i]);
    }
    //printf("\n");
    return 0;
}