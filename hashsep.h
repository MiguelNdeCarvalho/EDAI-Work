typedef int ElementType;

#ifndef _HashSep_H
#define _HashSep_H

struct ListNode;
typedef struct ListNode *Position;

struct HashTbl;
typedef struct HashTbl *HashTable;

HashTable InitializeTable(int TableSize);
void DestroyTable(HashTable H);

Position Find(wchar_t Key, int Value, HashTable H);
void Insert(wchar_t Key, int Value, HashTable H);
ElementType Retrieve(Position P);
void PrintHashTable(HashTable T);

HashTable Delete(ElementType X, HashTable T);
HashTable MakeEmpty(HashTable T);

#endif