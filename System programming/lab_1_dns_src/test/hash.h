#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include <malloc.h>
#include <stdlib.h>
#include <stdio.h>

#define P 31

typedef struct Item {
	char *key;
	char *info;
	struct Item *next;
} Item;

typedef struct Hashtable {
	int size;
	Item **table;
} Hashtable;

Hashtable *Create(int size) {
	Hashtable *ht = NULL;
	int i;
	if (size < 1)
		return NULL;
	if ((ht = malloc(sizeof(Hashtable))) == NULL)
		return NULL;
	if ((ht->table = malloc(sizeof(Item *)*size)) == NULL)
		return NULL;
	for (i = 0; i < size; i++) {
		ht->table[i] = NULL;
	}
	ht->size = size;
	return ht;
}

int hashCode(Hashtable *ht, char *key) {

	//слишком медленно
	
	/*unsigned long int hashvalue = 0;
	int i = 0;
	while (hashvalue < ULONG_MAX && i < strlen(key)) {
		hashvalue = hashvalue << 8;
		hashvalue += key[i];
		i++;
	}
	return hashvalue % ht->size;*/
	unsigned long long hash = 0;
	int	p_pow = 1;
	for (size_t i = 0; i < strlen(key); ++i)
	{
		hash += (key[i] - 'a' + 1) * p_pow;
		p_pow *= P;
	}
	hash = hash%ht->size;
	return hash;
}

Item *CreatePair(char *key, char *info) {
	Item *newpair;
	if ((newpair = malloc(sizeof(Item))) == NULL)
		return NULL;
	if ((newpair->key = _strdup(key)) == NULL)
		return NULL;
	if ((newpair->info = _strdup(info)) == NULL)
		return NULL;
	newpair->next = NULL;
	return newpair;
}

void Add(Hashtable *ht, char *key, char *info) {
	int hash = 0;
	Item *newpair = NULL;
	Item *next = NULL;
	Item *last = NULL;

	hash = hashCode(ht, key);
	next = ht->table[hash];
	while (next != NULL && next->key != NULL && strcmp(key, next->key) > 0) {
		last = next;
		next = next->next;
	}

	if (next != NULL && next->key != NULL && strcmp(key, next->key) == 0) {
		free(next->info);
		next->info = _strdup(info);
	}
	else {
		newpair = CreatePair(key, info);
		if (next == ht->table[hash]) {
			newpair->next = next;
			ht->table[hash] = newpair;
		}
		else
			if (next == NULL) {
				last->next = newpair;
			}
			else {
				newpair->next = next;
				last->next = newpair;
			}
	}
}

char *Show(Hashtable *ht, char *key) {
	int hash = 0;
	Item *pair;

	hash = hashCode(ht, key);
	pair = ht->table[hash];
	while (pair != NULL && pair->key != NULL && strcmp(key, pair->key) > 0) {
		pair = pair->next;
	}
	if (pair == NULL || pair->key == NULL || strcmp(key, pair->key) != 0) {
		return NULL;
	}
	else {
		return pair->info;
	}
}

/*void Clear(Hashtable *ht) {
	if (ht == NULL)
		return;
	Item *tmp;
	Item *table;
	int i;
	for (i = 0; i < ht->size; i++) {
		table = ht->table[i];
		while (table) {
			tmp = table;
			table = table->next;
			free(tmp);
		}
	}
	free(ht->table);
	free(ht);
}*/