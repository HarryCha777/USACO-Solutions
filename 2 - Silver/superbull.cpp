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
	ifstream in("superbull.in");
	ofstream out("superbull.out");

	int n; in >> n;
	vi input(n);
	for (int i = 0; i < n; i++) in >> input[i];

	vector< pair<int, ii> > edges(0);
	for (int i = 0; i < n; i++)
		for (int j = i + 1; j < n; j++)
			edges.push_back(make_pair(input[i] ^ input[j], ii(i, j)));
	sort(edges.rbegin(), edges.rend());

	r.assign(n, 0);
	p.assign(n, 0); for (int i = 1; i < n; i++) p[i] = i;

	long long ans = 0;
	for (int i = 0; i < edges.size(); i++)
	{
		pair<int, ii> front = edges[i];
		int x = findSet(front.second.first);
		int y = findSet(front.second.second);
		if (x != y) ans += front.first, connect(x, y);
	}
	out << ans << endl;

	return 0;
}

/*

#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

int n, input[2010], memo[2010][2010][2];
bool lost[2010];

int findMax()
{
	// no parameters here...memo...???
	// i, j, win/lost memo is wrong.
	// lost + curr is probably correct but requires too mush memory...and curr is indefinite

	int maxV = 0;
	for (int i = 0; i < n - 1; i++) if (!lost[i])
	{
		for (int j = i + 1; j < n; j++) if (!lost[j]) // i and j will never be the same
		{
			lost[i] = 1;
			maxV = max(maxV, findMax() + (input[i]^input[j]));
			lost[i] = 0;

			lost[j] = 1;
			maxV = max(maxV, findMax() + (input[i] ^ input[j]));
			lost[j] = 0;
		}
	}
	return maxV;
}

int main()
{
	ifstream in("superbull.in");
	ofstream out("superbull.out");

	in >> n;
	for (int i = 0; i < n; i++) in >> input[i];

	out << findMax() << endl;

	return 0;
}*/