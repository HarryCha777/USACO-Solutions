#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<int> vi;

int n;
vector<vii> adjList1, adjList2, adjList3;
vector<vi> dist;

void dijkstra(int index, int s)
{
	vector<vii> currAdjList;
	if (index == 1) currAdjList = adjList1;
	if (index == 2) currAdjList = adjList2;
	if (index == 3) currAdjList = adjList3;
	queue<int> q; q.push(s);
	dist[index][s] = 0;

	while (!q.empty())
	{
		int u = q.front(); q.pop();
		for (int j = 0; j < currAdjList[u].size(); j++)
		{
			int v = currAdjList[u][j].first;
			int w = currAdjList[u][j].second;
			if (dist[index][v] > dist[index][u] + w)
			{
				dist[index][v] = dist[index][u] + w;
				q.push(v);
			}
		}
	}
}

int main()
{
	ifstream in("gpsduel.in");
	ofstream out("gpsduel.out");

	int m; in >> n >> m;
	adjList1.assign(n, vii()), adjList2.assign(n, vii()), adjList3.assign(n, vii());
	dist.assign(4, vi(n, 1000000000)); // dist[0] is not used
	for (int i = 0; i < m; i++)
	{
		int a, b, p, q; in >> a >> b >> p >> q; a--, b--;
		adjList1[b].push_back(ii(a, p));
		adjList2[b].push_back(ii(a, q));
	}

	dijkstra(1, n - 1);
	dijkstra(2, n - 1);

	for (int u = 0; u < n; u++)
		for (int j = 0; j < adjList1[u].size(); j++)
		{
			int v = adjList1[u][j].first;
			int w1 = adjList1[u][j].second, w2 = adjList2[u][j].second, w3 = 0;
			if (dist[1][v] - dist[1][u] != w1) w3++;
			if (dist[2][v] - dist[2][u] != w2) w3++;
			adjList3[v].push_back(ii(u, w3));
		}

	for (int i = 0; i < n; i++)
	{
		cout << i + 1 << ": ";
		for (int j = 0; j < adjList3[i].size(); j++)
			printf("(%d, %d) ", adjList3[i][j].first + 1, adjList3[i][j].second);
		cout << endl;
	} cin.get();

	dijkstra(3, 0);
	out << dist[3][n - 1] << endl;

	return 0;
}

/*

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<int> vi;

int n;
vector<vii> adjList1, adjList2;
vi p, path1, path2;

void makePath(bool b, int s, int u)
{
	if (!b)
	{
		if (u == s) { path1.push_back(u); return; }
		makePath(b, s, p[u]);
		path1.push_back(u);
	}
	else
	{
		if (u == s) { path2.push_back(u); return; }
		makePath(b, s, p[u]);
		path2.push_back(u);
	}
}

void dijkstra(bool b, int s)
{
	vector<vii> currAdjList;
	!b ? currAdjList = adjList1 : currAdjList = adjList2;
	vi dist(n, 1000000000); dist[s] = 0;
	queue<int> q; q.push(s);
	p.assign(n, -1);

	while (!q.empty())
	{
		int u = q.front(); q.pop();
		for (int j = 0; j < currAdjList[u].size(); j++)
		{
			int v = currAdjList[u][j].first;
			int w = currAdjList[u][j].second;
			if (dist[v] > dist[u] + w)
			{
				dist[v] = dist[u] + w;
				q.push(v);
				p[v] = u;
			}
		}
	}

	!b ? path1.assign(0, 0) : path2.assign(0, 0);
	makePath(b, s, n - 1);
}

int solve(int s)
{
	dijkstra(0, s);
	dijkstra(1, s);
	
	cout << s << endl;
	for (int i = 0; i < path1.size(); i++) cout << path1[i] << " "; cout << endl;
	for (int i = 0; i < path2.size(); i++) cout << path2[i] << " "; cout << endl << endl;

	for (int i = 0; i < path1.size(); i++) // what if path2 ends before path1?
		if (path1[i] != path2[i]) // || i == path2.size()
		{
			cout << "!!!\n";
			cout << path1[i] << " " << path2[i] << endl;
			return min(solve(path1[i]) + 1, solve(path2[i]) + 1);
		}
	return 0;
}

int main()
{
	ifstream in("gpsduel.in");
	ofstream out("gpsduel.out");

	int m; in >> n >> m;
	adjList1.assign(n, vii()), adjList2.assign(n, vii());
	for (int i = 0; i < m; i++)
	{
		int a, b, p, q; in >> a >> b >> p >> q; a--, b--;
		adjList1[a].push_back(ii(b, p));
		adjList2[a].push_back(ii(b, q));
	}

	out << solve(0) << endl;
	//cin.get();

	return 0;
}*/