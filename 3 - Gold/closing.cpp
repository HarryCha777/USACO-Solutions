#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <vector>
using namespace std;

typedef vector<int> vi;

int sets;
vi p, r;

int findSet(int i) { if (p[i] == i) return i; return p[i] = findSet(p[i]); }
void connect(int x, int y)
{
	sets--;

	if (r[x] > r[y]) p[y] = x;
	else if (r[x] < r[y]) p[x] = y;
	else p[x] = y, r[y]++;
}

int main()
{
	ifstream in("closing.in");
	ofstream out("closing.out");

	int n, m; in >> n >> m;
	vector<vi> adjList(n);
	for (int i = 0; i < m; i++)
	{
		int u, v; in >> u >> v; u--, v--;
		adjList[u].push_back(v);
		adjList[v].push_back(u); // bi-directional
	}
	vi order(n);
	for (int i = n - 1; i >= 0; i--) in >> order[i], order[i]--;  // reverse order

	r.assign(n, 0);
	p.assign(n, 0); for (int i = 0; i < n; i++) p[i] = i;

	bool exists[200010] = {};
	vector<string> ans(n);
	for (int i = 0; i < n; i++)
	{
		int curr = order[i];
		exists[curr] = 1;
		sets++;

		for (int j = 0; j < adjList[curr].size(); j++)
			if (exists[adjList[curr][j]])
			{
				int a = findSet(order[i]);
				int b = findSet(adjList[curr][j]);
				if (a != b) connect(a, b);
			}

		sets == 1 ? ans[i] = "YES" : ans[i] = "NO";
	}
	for (int i = n - 1; i >= 0; i--) out << ans[i] << endl;

	return 0;
}