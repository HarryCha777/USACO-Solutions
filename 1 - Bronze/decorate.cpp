#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

typedef vector<int> vi;

int main()
{
	ifstream in("decorate.in");
	ofstream out("decorate.out");

	int n, m; in >> n >> m;
	vector<vi> adjList(n, vi());
	for (int i = 0; i < m; i++)
	{
		int u, v; in >> u >> v; u--, v--;
		adjList[u].push_back(v);
		adjList[v].push_back(u); // bi-directional
	}

	int s = 0, countJ = 0;
	vi sign(n, 0); sign[s] = 1; // 1 is F and 2 is J
	queue<int> q; q.push(s);
	while (!q.empty())
	{
		int u = q.front(); q.pop();
		for (int j = 0; j < adjList[u].size(); j++)
		{
			int v = adjList[u][j];
			if (sign[v] == 0)
			{
				if (sign[u] == 1) sign[v] = 2, countJ++;
				else sign[v] = 1;

				q.push(v);
			}
			else
			{
				if ((sign[u] == 1 && sign[v] == 1) || (sign[u] == 2 && sign[v] == 2))
					// remove ()?
				{
					out << -1 << endl;
					return 0;
				}
			}
		}
	}
	int countF = n - countJ;
	out << min(countF, countJ) << endl; // flip if more than half.

	return 0;
}