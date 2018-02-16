// labirint.cpp: определяет точку входа для консольного приложения.
//

#include <iostream>
#include <fstream>
#include <queue>

using namespace std;

typedef pair<int,int> Cell;

int i = 0;
ifstream fin("maze.in"); 
ofstream fout("maze.out");
void print(Cell **from, Cell end,Cell begin){

	if (from[end.first][end.second] != from[begin.first][begin.second]) {
		i++;
		print(from,from[end.first][end.second],begin);
		fout << from[end.first][end.second].first + 1 << " " << from[end.first][end.second].second + 1 << endl;
	}
	else{
		fout << i << endl;
	}
}


int main() { 
	 

	queue <Cell> q; 
	int M, N; 
	Cell start,finish;
	fin >> M >> N; 
	fin >> start.first >> start.second >> finish.first >> finish.second; 

	start.first--; 
	start.second--; 
	finish.first--; 
	finish.second--; 

	Cell **from = new Cell*[M]; 
	bool **visited = new bool*[M];
	bool **maze = new bool* [M]; 
	for (int i = 0; i < M; i++) {
		maze[i] = new bool[N]; 
		from[i] = new Cell[N];
		visited[i] = new bool[N]; 
	}	

	for (int i = 0; i < M; i++){ 
		for (int j = 0; j < N; j++) { 
			fin >> maze[i][j];
			visited[i][j] = false; 
		} 
	} 

	if (start == finish) { 
		fout << 0 << endl; 
		fout << start.first + 1 << ' ' << start.second  + 1 << endl; 
		return 0; 
	} 
	q.push(start); 
	int x = 0, y = 0;
	while (q.front() != finish ) {
		x = q.front().first;
		y = q.front().second;
		visited[x][y] = true; 
		if (x - 1 >= 0 && maze[x - 1][y] == 1 && visited[x - 1][y] == false) { 
			visited[x - 1][y] = true; 
			from[x - 1][y] = make_pair(x, y); 
			q.push(make_pair(x - 1, y)); 

		} 
		
		if (y - 1 >= 0 && maze[x][y - 1] == 1 && visited[x][y - 1] == false) { 
			visited[x][y - 1] = true;
			from[x][y - 1] = make_pair(x, y);
			q.push(make_pair(x, y - 1)); 

		} 

		if (x + 1 < M && maze[x + 1][y] == 1 && visited[x + 1][y] == false) { 
			visited[x + 1][y] = true; 
			from[x + 1][y] = make_pair(x, y); 
			q.push(make_pair(x + 1, y)); 

		} 
	
		if (y + 1 < N && maze[x][y + 1] == 1 && visited[x][y + 1] == false) { 
			visited[x][y + 1] = true;
			from[x][y + 1] = make_pair(x, y); 
			q.push(make_pair(x, y + 1)); 

		} 
		q.pop();
		if (q.empty())
			break;
	} 
	if (q.empty()) 
		fout << -1; 

	else{ 
		print(from,finish, start);
		fout << finish.first + 1 << ' ' << finish.second + 1 << endl;
	} 


	for (int i = 0; i < M; i++){ 
		delete []maze[i];
		delete []from[i];
		delete []visited[i];

	}
	fin.close();
	fout.close();
	return 0; 
}






//------------------------------------
//int main()
//{
//	ifstream fin("maze.in");
//	ofstream fout("maze.out");
//
//	int str, col;
//	fin » str » col;
//	int sX, sY, fX, fY;
//	fin » sX » sY » fX » fY;
//
//	sX -= 1;
//	sY -= 1;
//	fX -= 1;
//	fY -= 1;
//
//	queue <cell> q;
//	bool **maze = new bool*[str];
//	for (int i = 0; i < str; i++)
//		maze[i] = new bool[col];
//
//	cell **from = new cell*[str];
//	for (int i = 0; i < str; i++)
//		from[i] = new cell[col];
//
//	bool **visited = new bool*[str];
//	for (int i = 0; i < str; i++)
//		visited[i] = new bool[col];
//
//	for (int i = 0; i < str; i++)
//	{
//		for (int j = 0; j < col; j++)
//		{
//			visited[i][j] = false;
//		}
//	}
//
//	for (int i = 0; i < str; i++)
//	{
//		for (int j = 0; j < col; j++)
//		{
//			fin » maze[i][j];
//		}
//	}
//
//	if (sX == fX && sY == fY)
//	{
//		fout « 0 « endl;
//		fout « sX + 1 « ' ' « sY + 1 « endl;
//		return 0;
//	}
//
//	q.push(make_pair(sX, sY));
//	while (!(q.front().first == fX && q.front().second == fY))
//	{
//		visited[q.front().first][q.front().second] = true;
//
//		if (q.front().first - 1 >= 0
//			&& maze[q.front().first - 1][q.front().second] == 1
//			&& visited[q.front().first - 1][q.front().second] == false)
//		{
//			q.push(make_pair(q.front().first - 1, q.front().second));
//			visited[q.front().first - 1][q.front().second] = true;
//			from[q.front().first - 1][q.front().second]
//				= make_pair(q.front().first, q.front().second);
//		}
//		if (q.front().second - 1 >= 0
//			&& maze[q.front().first][q.front().second - 1] == 1
//			&& visited[q.front().first][q.front().second - 1] == false)
//		{
//			q.push(make_pair(q.front().first, q.front().second - 1));
//			visited[q.front().first][q.front().second - 1] = true;
//			from[q.front().first][q.front().second - 1]
//				= make_pair(q.front().first, q.front().second);
//		}
//		if (q.front().first + 1 < str
//			&& maze[q.front().first + 1][q.front().second] == 1
//			&& visited[q.front().first + 1][q.front().second] == false)
//		{
//			q.push(make_pair(q.front().first + 1, q.front().second));
//			visited[q.front().first + 1][q.front().second] = true;
//			from[q.front().first + 1][q.front().second]
//				= make_pair(q.front().first, q.front().second);
//		}
//		if (q.front().second + 1 < col
//			&& maze[q.front().first][q.front().second + 1] == 1
//			&& visited[q.front().first][q.front().second + 1] == false)
//		{
//			q.push(make_pair(q.front().first, q.front().second + 1));
//			visited[q.front().first][q.front().second + 1] = true;
//			from[q.front().first][q.front().second + 1]
//				= make_pair(q.front().first, q.front().second);
//		}
//		q.pop();
//		if (q.empty())
//			break;
//	}
//	if (q.empty())
//		fout « "-1";
//	else
//	{
//		//FIXME: здесь должен быть вывод
//	}
//	return 0;
//}