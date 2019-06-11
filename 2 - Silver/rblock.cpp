#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

#define INF 1000000000
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<int> vi;

int V;
vector<vii> adjList;

int bfs()
{
	int s = 0;
	vi dist(V, INF); dist[s] = 0;
	queue<int> q; q.push(s);

	while (!q.empty())
	{
		int u = q.front(); q.pop();
		for (int j = 0; j < adjList[u].size(); j++)
		{
			int v = adjList[u][j].first, w = adjList[u][j].second;
			if (dist[v] > dist[u] + w)
			{
				dist[v] = dist[u] + w;
				q.push(v);
			}
		}
	}
	return dist[V - 1];
}

int main()
{
	ifstream in("rblock.in");
	ofstream out("rblock.out");

	int E; in >> V >> E;
	vector< pair<int, ii> > edges;
	adjList.assign(V, vii());
	for (int i = 0; i < E; i++)
	{
		int u, v, w; in >> u >> v >> w; u--, v--;
		edges.push_back(make_pair(w, ii(u, v)));
		adjList[u].push_back(ii(v, w));
		adjList[v].push_back(ii(u, w)); // bi-directional
	}
	int ori = bfs();

	int maxChange = 0;
	for (int i = 0; i < E; i++)
	{
		adjList.assign(V, vii());
		for (int j = 0; j < E; j++)
		{
			int u = edges[j].second.first, v = edges[j].second.second, w = edges[j].first;
			if (j == i) w *= 2;
			adjList[u].push_back(ii(v, w));
			adjList[v].push_back(ii(u, w)); // bi-directional
		}
		maxChange = max(maxChange, bfs() - ori);
	}
	out << maxChange << endl;

	return 0;
}