#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
using namespace std;

typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<int> vi;

int V, E;
bool memoB[110][10010], memoE[110][10010]; // this is visited
vector<vii> adjListB, adjListE;
vi timesB, timesE;

void dfsB(int u, int currW)
{
	if (memoB[u][currW]) return;
	memoB[u][currW] = 1;

	if (u == V - 1)
	{
		timesB.push_back(currW);
		return;
	}

	for (int j = 0; j < adjListB[u].size(); j++)
	{
		int v = adjListB[u][j].first, w = adjListB[u][j].second;
		if (!memoB[v][currW + w]) dfsB(v, currW + w);
	}
}

void dfsE(int u, int currW)
{
	if (memoE[u][currW]) return;
	memoE[u][currW] = 1;

	if (u == V - 1)
	{
		timesE.push_back(currW);
		return;
	}

	for (int j = 0; j < adjListE[u].size(); j++)
	{
		int v = adjListE[u][j].first, w = adjListE[u][j].second;
		if (!memoE[v][currW + w]) dfsE(v, currW + w);
	}
}

// this is combined dfs...this cannot be used because it needs
// much bigger memory for memo (memo[110][10010][10010])!
/*void dfs(int u, int currWB, int currWE)
{
	if (memo[u][currWB][currWE]) return;
	memo[u][currWB][currWE] = 1;
	
	if (u == V - 1)
	{
		timesB.push_back(currWB);
		timesE.push_back(currWE);
		return;
	}
	
	for (int i = 0; i < adjListB[u].size(); i++)
	{
		int v = adjListB[u][j].first, wb = adjListB[u][j].second, we = adjListE[u][j].second;
		if (!memo[v][currWB + wb][currWE + we]) dfs(v, currWB + wb, currWE + we);
	}
}*/

int main()
{
	ifstream in("meeting.in");
	ofstream out("meeting.out");

	in >> V >> E;
	adjListB.assign(V, vii()), adjListE.assign(V, vii());
	for (int i = 0; i < E; i++)
	{
		int u, v, wb, we; in >> u >> v >> wb >> we; u--, v--; // NOT bi-directional
		adjListB[u].push_back(ii(v, wb));
		adjListE[u].push_back(ii(v, we)); // only weight is different
	}

	dfsB(0, 0); sort(timesB.begin(), timesB.end());
	dfsE(0, 0); sort(timesE.begin(), timesE.end()); // sort is necessary

	for (const int &i : timesB)
		for (const int &j : timesE)
			if (i == j)
			{
				out << i << endl;
				return 0;
			}
	out << "IMPOSSIBLE\n";

	return 0;
}