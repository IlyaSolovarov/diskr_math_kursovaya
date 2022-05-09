// ConsoleApplication29.cpp: определяет точку входа для консольного приложения.
//

#include <functional>
#include <queue>
#include <vector>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>

using namespace std;

//рекурсивная функция для нахождения эйлерова цикла
void euler(vector< vector<int> > tree, int from, int to, vector<int> &visited, vector<int> &cycle)
{
	visited.push_back(to);
	cycle.push_back(to);
	for(vector<int> edge : tree)
	{
		if (edge[0] == to && find(visited.begin(), visited.end(), edge[1]) == visited.end())
		{
			euler(tree, to, edge[1], visited, cycle);
		}
		else if (edge[1] == to && find(visited.begin(), visited.end(), edge[0]) == visited.end())
		{
			euler(tree, to, edge[0], visited, cycle);
		}
	}
	if (from != -1)
		cycle.push_back(from);
}


int main()
{
	// входные данные
	int n = 25;
	vector < vector<int> > g(25);
	int versh;
	const int INF = 1000000000; // значение "бесконечность"
	ifstream fin("input.txt");
	char str[1024];
	int rows = 0;
	while (fin.getline(str, 1024))
	{
		stringstream ss(str);
		int v;
		while (ss >> v)
		{
			if (v == 0)
				v = INF;
			g[rows].push_back(v);
		}
		rows++;
	}
	fin.close();
 
	// алгоритм Прима - находим остовное дерево
	vector< vector<int> > tree;
	vector<bool> used (n);
	vector<int> min_e (n, INF), sel_e (n, -1);
	min_e[0] = 0;
	for (int i=0; i<n; ++i) {
		int v = -1;
		for (int j=0; j<n; ++j)
			if (!used[j] && (v == -1 || min_e[j] < min_e[v]))
				v = j;
		if (min_e[v] == INF) {
			cout << "No MST!";
			exit(0);
		}
 
		used[v] = true;
		if (sel_e[v] != -1)
		{
			vector<int> temp(2);
			temp[0] = v;
			temp[1] = sel_e[v];
			tree.push_back(temp);
		}
 
		for (int to=0; to<n; ++to)
			if (g[v][to] < min_e[to]) {
				min_e[to] = g[v][to];
				sel_e[to] = v;
			}
	}

	//Находим Эйлеров цикл в удвоенном дереве
	vector<int> visited;
	vector<int> cycle;
	euler(tree, -1, 0, visited, cycle);	

	//Удаляем из цикла повторяющиеся вершины
	vector<int> gamilton;
	vector<int> seen;
	int size_of_cycle = cycle.size();
	for (int i = 0; i < size_of_cycle; i++)
		if (find(seen.begin(), seen.end(), cycle[i]) == seen.end())
		{
			seen.push_back(cycle[i]);
			gamilton.push_back(cycle[i]);
		}
	gamilton.push_back(cycle[0]);	

	//выводим путь
	for (int i = 0; i < n + 1; i++)
		cout << gamilton[i] + 1 << (i != n ? '-' : ' ');
	cout << "\tpath\n";
	
	//считаем длину пути
	int path_len = 0;
	int v1, v2;
	for (int i = 0; i < n; i++)
	{
		v1 = gamilton[i]; //i вершина пути
		v2 = gamilton[i+1]; //след. вершина пути
		path_len += g[v1][v2];
	}
	cout << path_len << "\tpath length";


	int key;
	cin >> key;
}