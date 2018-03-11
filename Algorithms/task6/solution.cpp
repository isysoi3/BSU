#include <fstream>
#include <vector>
#include <queue>
#include <iostream>
#include <stack>

using namespace std;
ifstream fin("input.txt");
ofstream fout("output.txt");

int main()
{
	int n, a, b;
	vector<int> deg(7, 0);
	vector < vector<int> > graph(7, vector<int>(7, 0));
	fin >> n;
	for (int i = 0; i < n; i++)
	{
		fin >> a >> b;
		graph[a][b]++;
		graph[b][a]++;
	}

	for (int i = 0; i < 7; ++i)
		for (int j = 0; j < 7; ++j)
			deg[i] += graph[i][j];

	bool flag = false;
	for (int i = 0; i < 7; ++i)
		if (deg[i] % 2 != 0) {
			fout << "No";
			fin.close();
			fout.close();
			return 0;
		}

	int first = 0;
	while (!deg[first])
		++first;

	stack<int> st;
	st.push(first);
	while (!st.empty())
	{
		int v = st.top();
		int i;
		for (i = 0; i < 7; ++i)
			if (graph[v][i])
				break;
		if (i == 7)
		{
			st.pop();
		}
		else
		{
			--graph[v][i];
			--graph[i][v];
			st.push(i);
		}
	}

	for (int i = 0; i < 7; ++i)
		for (int j = 0; j < 7; ++j)
			if (graph[i][j])
				flag = true;

	if (flag)
		fout << "No";
	else
		fout << "Yes";



	fin.close();
	fout.close();
	return 0;


}