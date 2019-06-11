#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <cstring>
using namespace std;

#define INF 1000000000
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<int> vi;

int n, V, memo[100010][2];
vii xy;

int solve(int u, bool dir) // dir is recent direction...dir 0 is horiz., dir 1 is vert
{
	if (u == 0) return 0;
	if (memo[u][dir] != -1) return memo[u][dir];

	if (!dir)
	{
		int ret = INF;
		for (int j = 0; j < V; j++) if (j != u && xy[u].second == xy[j].second)
			ret = min(ret, solve(j, !dir) + 1);
		memo[u][dir] = ret;
		return ret;
	}
	else
	{
		int ret = INF;
		for (int j = 0; j < V; j++)
		{
			if (j != u && xy[u].first == xy[j].first)
				ret = min(ret, solve(j, !dir) + 1);
			if (j != 0 && xy[u].first < xy[j].first)
			{
				if (xy[u].first == xy[V - 1].first) ret = min(ret, solve(V - 1, !dir) + 1);
				break;
			}
		}
		memo[u][dir] = ret;
		return ret;
	}
}

int main() // 2016 DEC. GOLD 3
{
	ifstream in("lasers.in");
	ofstream out("lasers.out");

	in >> n;
	xy.assign(n + 2, ii()), xy.assign(n + 2, ii());
	in >> xy[0].first >> xy[0].second >> xy[n + 1].first >> xy[n + 1].second;
	for (int i = 0; i < n; i++) in >> xy[i + 1].first >> xy[i + 1].second;
	V = n + 2;
	sort(xy.begin() + 1, xy.end() - 1);

	memset(memo, -1, sizeof memo);
	int ans = min(solve(V - 1, 0), solve(V - 1, 1)) - 1; // BOTH DIRECTIONS HERE!
	ans == INF - 1 ? out << -1 << endl : out << ans << endl;

	return 0;
}

// this below code is same as above EXCEPT for sorting...
// VERY LITTLE BIT SLOWER but easier to see. (same AC result in USACO)
/*

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <cstring>
using namespace std;

#define INF 1000000000
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<int> vi;

int n, V, memo[100010][2];
vii xy;

int solve(int u, bool dir) // dir is recent direction...dir 0 is horiz., dir 1 is vert
{
	if (u == 0) return 0;
	if (memo[u][dir] != -1) return memo[u][dir];

	if (!dir)
	{
		int ret = INF;
		for (int j = 0; j < V; j++) if (j != u && xy[u].second == xy[j].second)
			ret = min(ret, solve(j, !dir) + 1);
		memo[u][dir] = ret;
		return ret;
	}
	else
	{
		int ret = INF;
		for (int j = 0; j < V; j++) if (j != u && xy[u].first == xy[j].first)
			ret = min(ret, solve(j, !dir) + 1);
		memo[u][dir] = ret;
		return ret;
	}
}

int main()
{
	ifstream in("lasers.in");
	ofstream out("lasers.out");

	in >> n;
	xy.assign(n + 2, ii());
	in >> xy[0].first >> xy[0].second >> xy[n + 1].first >> xy[n + 1].second;
	for (int i = 0; i < n; i++) in >> xy[i + 1].first >> xy[i + 1].second;
	V = n + 2;
	//sort(xy.begin() + 1, xy.end() - 1);

	memset(memo, -1, sizeof memo);
	int ans = min(solve(V - 1, 0), solve(V - 1, 1)) - 1; // BOTH DIRECTIONS HERE!
	ans == INF - 1 ? out << -1 << endl : out << ans << endl;

	return 0;
}*/

/*

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

int main()
{
	ifstream in("lasers.in");
	ofstream out("lasers.out");

	int n; in >> n;
	vii xy(n + 2);
	in >> xy[0].first >> xy[0].second >> xy[n + 1].first >> xy[n + 1].second;
	for (int i = 0; i < n; i++) in >> xy[i + 1].first >> xy[i + 1].second;
	int V = n + 2;

	vi dist(V, 1000000000); dist[V - 1] = 0;
	queue<int> q; q.push(V - 1);
	vector<bool> visited(V, 0);
	while (!q.empty())
	{
		int u = q.front(); q.pop();
		if (visited[u]) continue;
		visited[u] = 1;
		for (int j = 0; j < V; j++)
			if (j != u && (xy[u].first == xy[j].first || xy[u].second == xy[j].second))
			{
				int v = j;
				if (dist[v] > dist[u] + 1)
					dist[v] = dist[u] + 1, q.push(v);
			}
	}
	dist[0] == 1000000000 ? out << -1 << endl : out << dist[0] - 1 << endl;

	return 0;
}*/

/*

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <cstring>
using namespace std;

#define INF 1000000000
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<int> vi;

int n, memo[100010][2];
vector<vi> adjListX, adjListY;

int solve(int u, bool dir) // dir is recent direction...dir 0 is horiz., dir 1 is vert
{
	if (u == 0) return 0;
	if (memo[u][dir] != -1) return memo[u][dir];

	if (!dir)
	{
		int ret = INF;
		for (int j = 0; j < adjListY[u].size(); j++)
			ret = min(ret, solve(adjListY[u][j], !dir) + 1);
		memo[u][dir] = ret;
		return ret;
	}
	else
	{
		int ret = INF;
		for (int j = 0; j < adjListX[u].size(); j++)
			ret = min(ret, solve(adjListX[u][j], !dir) + 1);
		memo[u][dir] = ret;
		return ret;
	}
}

int main()
{
	ifstream in("lasers.in");
	ofstream out("lasers.out");

	in >> n;
	vii xy(n + 2);
	in >> xy[0].first >> xy[0].second >> xy[n + 1].first >> xy[n + 1].second;
	for (int i = 0; i < n; i++) in >> xy[i + 1].first >> xy[i + 1].second;
	int V = n + 2;

	adjListX.assign(V, vi()), adjListY.assign(V, vi());
	for (int i = 0; i < V; i++)
		for (int j = 0; j < V; j++) if (i != j)
		{
			if (xy[i].first == xy[j].first)
				adjListX[i].push_back(j); // , adjListX[j].push_back(i);
			if (xy[i].second == xy[j].second)
				adjListY[i].push_back(j); // , adjListY[j].push_back(i);
			// bi-directional?
		}

	memset(memo, -1, sizeof memo);
	int ans = min(solve(V - 1, 0), solve(V - 1, 1)) - 1; // BOTH DIRECTIONS HERE!
	ans == INF - 1 ? out << -1 << endl : out << ans << endl;
	
	return 0;
}*/

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

int main()
{
	ifstream in("lasers.in");
	ofstream out("lasers.out");

	int n; in >> n;
	vii xy(n + 2); // n + 2  // get rid of 100000?
	in >> xy[0].first >> xy[0].second >> xy[n + 1].first >> xy[n + 1].second;
	for (int i = 0; i < n; i++) in >> xy[i + 1].first >> xy[i + 1].second;
	int V = n + 2;

	vector<vi> adjList(V, vi());
	for (int i = 0; i < V; i++)
		for (int j = 0; j < V; j++) if (i != j)
			if (xy[i].first == xy[j].first || xy[i].second == xy[j].second)
			{
				// size? skip.
				adjList[i].push_back(j);
				//adjList[j].push_back(i); // bi-directional?
			}

	//for (int i = 0; i < V; i++)
	//{
	//	cout << i << ":   ";
	//	for (int j = 0; j < adjList[i].size(); j++)
	//		cout << adjList[i][j] << " ";
	//	cout << endl;
	//} cin.get();

	vi dist(V, 1000000000); dist[0] = 0; // get rid of 100000?
	queue<int> q; q.push(0);
	vector<bool> visited(V, 0);
	while (!q.empty())
	{
		int u = q.front(); q.pop();
		if (visited[u]) continue;
		visited[u] = 1;
		for (int j = 0; j < adjList[u].size(); j++)
		{
			int v = adjList[u][j];
			if (dist[v] > dist[u] + 1)
				dist[v] = dist[u] + 1, q.push(v);
		}
	}
	dist[V - 1] == 1000000000 ? out << -1 << endl : out << dist[V - 1] - 1 << endl;
	//out << 1 << endl;

	// bi-directional?
	// new way?

	// n or V issue?
	// - index?
	// circling forever?
	// go opposite way?

	return 0;
}*/

// long long?
// bfs (save prev. direction in queue too!)
// working backwards recursion depth (looking for vert. OR horiz. (but AND for fisrt (last)))
//vector<vii> listX(1000000010, vii()), listY(1000000010, vii()); // use map?