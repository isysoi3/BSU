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

unsigned long* Hash(const char* str)//Хеш функция
{
	static unsigned long mas[2];
	unsigned long hash = 5381;
	int c;
	while ((c = *str++))
		hash += c * 33;
	mas[0] = hash % SIZE;
	mas[1] = hash;
	return mas;
}

void Insert(Hash_Table* ht, char* str, char* ip)
{
	Hash_Table* p;
	unsigned int IP = IPtoDecimal(ip);
	unsigned long *hash = Hash(str);
	if (ht[hash[0]].hostName == NULL)//проверка коллизии
	{
		ht[hash[0]].hostName = (char*)malloc(sizeof(char) * (strlen(str) + 1));
		strcpy(ht[hash[0]].hostName, str);
		ht[hash[0]].ip = IP;
		ht[hash[0]].hash = hash[1];

	}
	else//решение с помощью цепочек
	{
		p = (Hash_Table*)malloc(sizeof(Hash_Table));
		p->hostName = (char*)malloc(sizeof(char) * (strlen(str) + 1));
		strcpy(p->hostName, str);
		p->ip = IP;
		p->hash=  hash[1];
		p->next_pair = ht[hash[0]].next_pair;
		ht[hash[0]].next_pair = p;

	}
}

unsigned int Find(Hash_Table* ht, const char* str)
{
	unsigned long *hash = Hash(str);
	Hash_Table* it = &ht[hash[0]];
	while (it->hash != hash[1] ||  strcmp(it->hostName, str) != 0)//ищем в цепочке 
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