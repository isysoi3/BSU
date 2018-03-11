#include <fstream>
#include <vector>
#include <queue>

using namespace std;
ifstream fin("input.txt");
ofstream fout("output.txt");


int turn(pair<int, int> a, pair<int, int> b, pair<int, int> c)
{
	if (a.first == c.first && a.second == c.second)
		return 1;
	if (a.first == b.first && a.second == b.second) {
		pair<int, int> tmp = make_pair(a.first, a.second - 1);
		if ((tmp.first * a.second + a.first * c.second + tmp.second * c.first) - (c.first * a.second + c.second * tmp.first + tmp.second * a.first) > 0)
			return 2;
	}
	if ((a.first * b.second + a.second * c.first + b.first * c.second) - (c.first * b.second + b.first * a.second + c.second * a.first) > 0)
		return 3;
	return 0;
}


int main()
{
	ios_base::sync_with_stdio(false);
	int n, m, k, a, b, t;
	fin >> n >> m >> k;
	vector <pair<int, int>> cordinats(n);
	priority_queue<pair<long long, pair<int, int>>> heap;
	vector<vector<int>> graph(n);
	vector<int> intersection(n);

	for (int i = 0; i < n; i++)
	{
		graph[i].resize(n, -1);
		fin >> a >> b;
		cordinats[i] = { a, b };
	}
	for (int i = 0; i < m; i++) {
		fin >> a >> b >> t;
		a--;
		b--;
		graph[a][b] = t;
		graph[b][a] = t;
		intersection[a]++;
		intersection[b]++;
	}

	fin >> a >> b;
	a--;
	b--;

	heap.push(make_pair(0, make_pair(a, a)));
	pair<long long, pair<int, int>> node;

	while (!heap.empty())
	{
		while (!heap.empty()) {
			node = heap.top();
			heap.pop();
			if (graph[node.second.first][node.second.second] != -1) {
				graph[node.second.first][node.second.second] = -1;
				break;
			}
		}

		if (node.second.second == b) {
			fout << "Yes\n" << -node.first;
			return 0;
		}

		for (int i = 0; i < n; i++) {
			if (graph[node.second.second][i] == -1)
				continue;
			long long way = -node.first + graph[node.second.second][i];
			int tmp = turn(cordinats[node.second.first], cordinats[node.second.second], cordinats[i]);
			if (tmp != 0)
				if (tmp == 1 || tmp == 3)
					way += k * intersection[node.second.second];
				else if (tmp == 2)
					way += k * intersection[node.second.first];
			heap.push({ -way,{ node.second.second,i} });
		}
	}

	fout << "No";
	fin.close();
	fout.close();
	return 0;
}