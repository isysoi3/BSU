#include <fstream>
#include <list>
#include <iostream>
#include <algorithm>
using namespace std;
ifstream fin("huffman.in");
ofstream fout("huffman.out");

class Node
{
public:
	long long int value;
	Node* leftSon;
	Node* rightSon;

	Node(long long int v, Node* l = NULL, Node* r = NULL)
	{
		value = v;
		leftSon = l;
		rightSon = r;
	}

	~Node()
	{
		delete leftSon;
		delete rightSon;
	}

	bool isLeaf() const
	{
		return leftSon == NULL && rightSon == NULL;
	}
};

long long int count(Node* node, long long int i = -1)
{
	i++;
	long long int rez = 0;
	if (node->isLeaf())
		return  i*node->value;
	rez += count(node->rightSon, i);
	rez += count(node->leftSon, i);
	return rez;
}



int main() {
	long long int n;
	list<Node*> nodes;
	fin >> n;
	long long int* mas = new long long int[n];
	for (int i = 0; i < n; i++)
	{
		fin >> mas[i];
	}

	for (int i = 0; i < n; i++)
	{
		if (nodes.empty() || (i < n - 1 && (mas[i] < nodes.front()->value && mas[i + 1] < nodes.front()->value)))
		{
			auto leave1 = new Node(mas[i]);
			auto leave2 = new Node(mas[i + 1]);
			nodes.push_back(new Node(leave1->value + leave2->value, leave1, leave2));
			i++;
		}
		else if (nodes.size() == 1)
		{
			auto leave = new Node(mas[i]);
			auto tmp = nodes.front();
			nodes.pop_front();
			nodes.push_back(new Node(tmp->value + leave->value, tmp, leave));
		}
		else
		{
			if (nodes.front()->value < mas[i])
			{
				auto firstNode = nodes.front();
				nodes.pop_front();
				if (nodes.front()->value < mas[i])
				{
					auto secondNode = nodes.front();
					nodes.pop_front();
					nodes.push_back(new Node(firstNode->value + secondNode->value, firstNode, secondNode));
					i--;
					continue;
				}
				nodes.push_front(firstNode);
			}
			auto leave = new Node(mas[i]);
			auto tmp = nodes.front();
			nodes.pop_front();
			nodes.push_back(new Node(tmp->value + leave->value, tmp, leave));


		}
	}

	while (nodes.size() != 1) {
		auto tmp1 = nodes.front();
		nodes.pop_front();
		auto tmp2 = nodes.front();
		nodes.pop_front();
		nodes.push_back(new Node(tmp1->value + tmp2->value, tmp1, tmp2));
	}

	fout << count(nodes.back());
	fout.close();
	fin.close();
	return 0;
}