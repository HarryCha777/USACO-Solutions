#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
using namespace std;

typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<int> vi;

vi r, p;

int sets;
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
	ifstream in("irrigation.in");
	ofstream out("irrigation.out");

	int n, c; in >> n >> c;
	int x[2010], y[2010];
	for (int i = 0; i < n; i++) in >> x[i] >> y[i];
	vector< pair<int, ii> > edges(0);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++) if (i != j)
		{
			int w = pow(abs(x[i] - x[j]), 2) + pow(abs(y[i] - y[j]), 2);
			if (w >= c) edges.push_back(make_pair(w, ii(i, j)));
		}
	sort(edges.begin(), edges.end());

	r.assign(n, 0);
	p.assign(n, 0); for (int i = 1; i < n; i++) p[i] = i;

	int ans = 0;
	sets = n;
	for (int i = 0; i < edges.size(); i++)
	{
		pair<int, ii> front = edges[i];
		int x = findSet(front.second.first);
		int y = findSet(front.second.second);
		if (x != y) ans += front.first, connect(x, y);
	}
	sets == 1 ? out << ans << endl : out << -1 << endl;

	return 0;
}