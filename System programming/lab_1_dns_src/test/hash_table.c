#include "hash_table.h"
#include "dns.h"

unsigned int Init()//выделение памяти 
{
	return (unsigned int)(Hash_Table*)calloc(SIZE, sizeof(Hash_Table));
}


unsigned int IPtoDecimal(char* ip)//перевод ip из строки в число
{
	unsigned int bytes[4];
	sscanf(ip, "%d.%d.%d.%d", &bytes[0], &bytes[1], &bytes[2], &bytes[3]);
	return (unsigned int)(bytes[3] | bytes[2] << 8 | bytes[1] << 16 | bytes[0] << 24);
}

unsigned int Hash(const char* str)//Хеш функция
{
	unsigned long hash = 5381;
	int c;
	while ((c = *str++))
		hash += c * 33;
		//hash = hash << 5 + hash + c;

	return hash % SIZE;
}

void Insert(Hash_Table* ht, char* str, char* ip)
{
	Hash_Table* p;
	unsigned int IP = IPtoDecimal(ip);
	unsigned int hash = Hash(str);
	if (ht[hash].hostName == NULL)//проверка коллизии
	{
		ht[hash].hostName = (char*)malloc(sizeof(char) * (strlen(str) + 1));
		strcpy(ht[hash].hostName, str);
		ht[hash].ip = IP;
	}
	else//решение с помощью цепочек
	{
		p = (Hash_Table*)malloc(sizeof(Hash_Table));
		p->hostName = (char*)malloc(sizeof(char) * (strlen(str) + 1));
		strcpy(p->hostName, str);
		p->ip = IP;
		p->next_pair = ht[hash].next_pair;
		ht[hash].next_pair = p;

	}
}

unsigned int Find(Hash_Table* ht, const char* str)
{
	unsigned int hash = Hash(str);
	Hash_Table* it = &ht[hash];
	while (it != NULL && strcmp(it->hostName, str) != 0)//ищем в цепочке 
	{
		it = it->next_pair;
	}
	if (it != NULL)
		return it->ip;
	return INVALID_IP_ADDRESS;
}

void Delete(Hash_Table* ht)
{
	Hash_Table* tmp1;
	Hash_Table* tmp2;
	for (int i = 0; i < SIZE; i++) {
		tmp1 = &ht[i];
		while (tmp1 != NULL)
		{
			tmp2 = tmp1;
			tmp1 = tmp1->next_pair;
			free(tmp2->hostName);
			free(tmp2);
		}
	}
}