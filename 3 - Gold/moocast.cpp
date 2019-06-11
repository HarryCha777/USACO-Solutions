#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
using namespace std;

typedef pair<int, int> ii;
typedef vector<int> vi;

vi p, r;

int findSet(int i) { if (p[i] == i) return i; return p[i] = findSet(p[i]); }
void connect(int x, int y)
{
	if (r[x] > r[y]) p[y] = x;
	else if (r[x] < r[y]) p[x] = y;
	else p[x] = y, r[y]++;
}

int x[1010], y[1010];

int main() // 2016 DEC. GOLD 1
{
	ifstream in("moocast.in");
	ofstream out("moocast.out");

	int n; in >> n;
	for (int i = 0; i < n; i++) in >> x[i] >> y[i];

	vector< pair<int, ii> > edges;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++) if (i != j)
			edges.push_back(make_pair
			(abs((x[i] - x[j]) * (x[i] - x[j])) + abs((y[i] - y[j]) * (y[i] - y[j])), ii(i, j)));
	sort(edges.begin(), edges.end());

	r.assign(n, 0);
	p.assign(n, 0); for (int i = 1; i < n; i++) p[i] = i;

	int longestEdge = 0;
	for (int i = 0; i < edges.size(); i++)
	{
		pair<int, ii> front = edges[i];
		int x = findSet(front.second.first);
		int y = findSet(front.second.second);
		if (x != y) connect(x, y), longestEdge = max(longestEdge, front.first);
	}
	out << longestEdge << endl;

	return 0;
}

/*

#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

int x[1010], y[1010];

int main()
{
	ifstream in("moocast.in");
	ofstream out("moocast.out");

	int n; in >> n;
	for (int i = 0; i < n; i++) in >> x[i] >> y[i];

	int ans = 0;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++) if (i != j)
			ans = max(ans, abs((x[i] - x[j]) * (x[i] - x[j])) + abs((y[i] - y[j]) * (y[i] - y[j])))
			, cout << i << " " << j << "   " << ans << endl;
	out << ans << endl; cin.get();

	return 0;
}*/