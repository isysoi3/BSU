#pragma comment(linker, "/STACK:33554432")

#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

ifstream fin("input.txt");
ofstream fout("output.txt");

void solve(int pos, int** adjacency_list, int* F0, int* F1, int* nodes)
{
	for (auto j = 1; j <= adjacency_list[pos][0]; j++)
	{
		if (nodes[adjacency_list[pos][j]] == -1 && adjacency_list[pos][j] != 0)
		{
			nodes[adjacency_list[pos][j]] = pos;
			solve(adjacency_list[pos][j], adjacency_list, F0, F1, nodes);
		}
	}

	if (adjacency_list[pos][0] != 1 || pos == 0) {
		for (int i = 1; i <= adjacency_list[pos][0]; i++) {
			if (nodes[adjacency_list[pos][i]] == pos) {
				F0[pos] += F1[adjacency_list[pos][i]];
				F1[pos] += min(F0[adjacency_list[pos][i]], F1[adjacency_list[pos][i]]);
			}
		}
	}
}

int main()
{
	int n, k, tmp;
	fin >> n;
	int** adjacency_list = new int*[n];
	int* F0 = new int[n];
	int* F1 = new int[n];
	int* nodes = new int[n];
	for (auto i = 0; i < n; i++) {
		F0[i] = 0;
		F1[i] = 1;
		nodes[i] = -1;
		fin >> k;
		adjacency_list[i] = new int[k + 1];
		adjacency_list[i][0] = k;
		for (auto j = 1; j <= k; j++)
		{
			fin >> tmp;
			adjacency_list[i][j] = tmp - 1;
		}
	}

	solve(0, adjacency_list, F0, F1, nodes);

	fout << min(F0[0], F1[0]);
	fin.close();
	fout.close();
	delete[] F0;
	delete[] F1;
	delete[] nodes;
	for (auto j = 0; j < n; j++) {
		delete[] adjacency_list[j];
	}
	return 0;
}
