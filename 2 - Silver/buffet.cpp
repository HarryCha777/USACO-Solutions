#include <iostream>
#include <fstream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>
using namespace std;

#define MAXN 1010

int quality[MAXN], DP[MAXN], dist[MAXN];
vector<int> E[MAXN];

int main()
{
	ifstream in("buffet.in");
	ofstream out("buffet.out");

	int N, w; in >> N >> w;
	for (int i = 0; i < N; i++)
	{
		int D; in >> quality[i] >> D;
		for (int j = 0; j < D; j++)
		{
			int v; in >> v;
			E[i].push_back(v - 1);
		}
	}

	vector<int> PI;
	for (int i = 0; i < N; i++) PI.push_back(i);
	sort(PI.begin(), PI.end(), [&](int x, int y) { return quality[x] < quality[y]; });

	//for (int i = 0; i < N; i++) cout << PI[i] << " "; cout << endl; cin.get();

	int ans = 0;
	for (int i = N - 1; i >= 0; i--)
	{
		int s = PI[i];
		queue<int> q; q.push(s);
		memset(dist, -1, sizeof(dist));
		dist[s] = 0;
		while (!q.empty())
		{
			int u = q.front(); q.pop();
			for (int j = 0; j < E[u].size(); j++)
			{
				int v = E[u][j];
				if (dist[v] == -1) dist[v] = dist[u] + 1, q.push(v);
			}
		}

		int currRes = quality[s];
		for (int j = 0; j < N; j++) if (dist[j] != -1)
			currRes = max(currRes, quality[s] + DP[j] - w * dist[j]);
		DP[s] = currRes;
		ans = max(ans, currRes);
	}
	out << ans << endl;

	return 0;
}

/*

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
using namespace std;

typedef pair<int, int> ii;
typedef vector<int> vi;

int n, e, maxV;
vector<vi> adjList, connected;
vi values, visited;

void dfs(int s, int u)
{
	connected[s].push_back(u);
	visited[u] = 1;
	for (int j = 0; j < adjList[u].size(); j++)
	{
		int v = adjList[u][j];
		if (!visited[v]) dfs(s, v);
	}
}

// (not visited is not needed?) bigger, possible! destination(param.) (less than destination dont eat)
int main()
{
	ifstream in("buffet.in");
	ofstream out("buffet.out");

	in >> n >> e;
	adjList.assign(n, vi());
	for (int i = 0; i < n; i++)
	{
		int value, neighbors; in >> value >> neighbors;
		values.push_back(value);
		for (int j = 0; j < neighbors; j++)
		{
			int v; in >> v; v--;
			adjList[i].push_back(v);
		}
	}
	connected.assign(n, vi());
	for (int s = 0; s < n; s++)
	{
		visited.assign(n, 0);
		dfs(s, s);
	}

	return 0;
}*/

/*

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
using namespace std;

typedef pair<int, int> ii;
typedef vector<int> vi;

int n, e, maxV;
vector<vi> adjList;
vi values, visited;

void dfs(int u, int prevV, int currTotalV, int stack)
{
	if (currTotalV < 0 || stack > 2*n) return;
	maxV = max(maxV, currTotalV);

	for (int i = 0; i < adjList[u].size(); i++)
	{
		int v = adjList[u][i];
		dfs(v, prevV, currTotalV - e, stack + 1);

		if (!visited[v] && values[v] > prevV)
		{
			visited[v] = 1;
			dfs(v, values[v], currTotalV + values[v] - e, stack + 1);
			visited[v] = 0;
		}
	}
}

int main()
{
	ifstream in("buffet.in");
	ofstream out("buffet.out");

	in >> n >> e;
	adjList.assign(n, vi());
	for (int i = 0; i < n; i++)
	{
		int value, neighbors; in >> value >> neighbors;
		values.push_back(value);
		for (int j = 0; j < neighbors; j++)
		{
			int v; in >> v; v--;
			adjList[i].push_back(v);
		}
	}

	visited.assign(n, 0);
	for (int i = 0; i < n; i++)
	{
		//cout << i << endl;
		visited[i] = 1;
		dfs(i, values[i], values[i], 0);
		visited[i] = 0;
	}
	out << maxV << endl;

	return 0;
}*/