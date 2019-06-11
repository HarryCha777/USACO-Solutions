#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
using namespace std;

typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<int> vi;

vi r, p;

int findSet(int i) { if (p[i] == i) return i; return p[i] = findSet(p[i]); }
void connect(int x, int y)
{
	if (r[x] > r[y]) p[y] = x;
	else if (r[x] < r[y]) p[x] = y;
	else p[x] = y, r[y]++;
}

int main()
{
	ifstream in("fencedin.in");
	ofstream out("fencedin.out");

	int a, b, n, m, linesN[2010] = {}, linesM[2010] = {};
	in >> a >> b >> n >> m;
	for (int i = 0; i < n; i++) in >> linesN[i]; linesN[n] = 0; linesN[n + 1] = a;
	for (int i = 0; i < m; i++) in >> linesM[i]; linesM[m] = 0; linesM[m + 1] = b;
	sort(linesN, linesN + n + 2);
	sort(linesM, linesM + m + 2);

	vector<pair<int, ii>> edges(0);
	for (int i = 0; i < n + 1; i++)
	{
		for (int j = 0; j < m + 1; j++)
		{
			int u = i*(m+1) + j;
			if (i + 1 != n + 1) edges.push_back(make_pair(linesM[j + 1] - linesM[j], ii(u, u + m + 1)));
			if (j + 1 != m + 1) edges.push_back(make_pair(linesN[i + 1] - linesN[i], ii(u, u + 1)));
		}
	}
	sort(edges.begin(), edges.end());

	//for (int i = 0; i < edges.size(); i++)
	//	printf("%d (%d, %d)\n", edges[i].first, edges[i].second.first, edges[i].second.second);
	//cin.get();

	r.assign((n+1)*(m+1), 0);
	p.assign((n+1)*(m+1), 0); for (int i = 1; i < (n+1)*(m+1); i++) p[i] = i;

	int ans = 0;
	for (int i = 0; i < edges.size(); i++)
	{
		pair<int, ii> currEdge = edges[i];
		int x = findSet(currEdge.second.first), y = findSet(currEdge.second.second);
		if (x != y)
		{
			ans += currEdge.first;
			connect(x, y);
		}
	}
	out << ans << endl;

	return 0;
}