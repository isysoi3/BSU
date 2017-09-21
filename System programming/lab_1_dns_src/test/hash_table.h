#ifndef _HASH_TABLE_H_
#define _HASH_TABLE_H_
#define _CRT_SECURE_NO_WARNINGS
#define SIZE 15000

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct pair {
	char *hostName;
	unsigned int ip;
	unsigned long hash;
	struct pair* next_pair;
} Hash_Table;


unsigned int Init();

void Insert(Hash_Table* ht, char* str, char* ip);

unsigned int Find(Hash_Table* ht, const char* str);

void Delete(Hash_Table* ht);

#endif 