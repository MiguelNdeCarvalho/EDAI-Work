typedef int ElementType;

#ifndef _HashSep_H
#define _HashSep_H

struct ListNode;
typedef struct ListNode *Position;

struct HashTbl;
typedef struct HashTbl *HashTable;

HashTable InitializeTable(int TableSize);
void DestroyTable(HashTable H);

Position Find(wchar_t *Key, int Value, HashTable H);
int FindWOValue(wchar_t * Key, HashTable H);
void Insert(wchar_t *Key, int Value, HashTable H);
ElementType Retrieve(Position P);
void PrintHashTable(HashTable T);

HashTable Delete(ElementType X, HashTable T);
HashTable MakeEmpty(HashTable T);

void defineT9(HashTable T);
long convertToT9(wchar_t *input, HashTable H);

#endif