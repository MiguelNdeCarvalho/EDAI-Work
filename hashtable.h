typedef int ElementType;

#ifndef _HashSep_H
#define _HashSep_H

struct ListNode;
typedef struct ListNode *Position;

struct HashTbl;
typedef struct HashTbl *HashTable;

HashTable InitializeTable(int TableSize);
void DestroyTable(HashTable H);

long Hash ( unsigned long Key, int TableSize );
Position Find(wchar_t *Key, unsigned long Value, HashTable H);
int FindWOValue(wchar_t Key, HashTable H);
void Insert(wchar_t *Key, unsigned long Value, HashTable H);
void InsertWord(wchar_t *Key, unsigned long K9_Value, HashTable H);
ElementType Retrieve(Position P);
void PrintHashTable(HashTable T);

HashTable Delete(ElementType X, HashTable T);
HashTable MakeEmpty(HashTable T);

void LoadT9Keys(HashTable T);
void LoadDictionary(FILE *input, HashTable T9, HashTable Dictionary);
int CheckExistenceOfSpecialCharacter(wchar_t *input);
unsigned long ConvertWordToT9Keys(wchar_t *input, HashTable H);
wchar_t* SuggestWord(unsigned long input, HashTable T9, HashTable Dictionary);
void interface(HashTable T9, HashTable Dictionary);
#endif