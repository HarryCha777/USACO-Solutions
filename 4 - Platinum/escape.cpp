//#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <bitset>
#include <sstream>
using namespace std;

#define INF 1000000000
#define rep(i, n) for (int i = 0; i < n; i++)
#define D(x) cout << #x " is " << x << endl
#define pb push_back
#define F first
#define S second

typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> ii;
typedef vector<ii> vii;

int findSet(vi p, int i) { if (p[i] == i) return i; return p[i] = findSet(p, p[i]); }
void connect(vi r, vi p, vi setSize, int a, int b)
{
	if (r[a] > r[b]) p[b] = a, setSize[a] += setSize[b];
	else if (r[a] < r[b]) p[a] = b, setSize[b] += setSize[a];
	else p[a] = b, r[b]++, setSize[b] += setSize[a];
}

int horiz[30010][10] = {}, vert[30010][10] = {};
vector< pair<int, ii> > edges;
int minCostDiscovered = INF, minCostCounter = 0;

void mst(vector<bool> usedEdges, vi r, vi p, vi setSize, int i, int numSets, ll minCost)
{
    if (i == edges.size())
    {
        if (numSets == 1)
        {
            if (minCost == minCostDiscovered) minCostCounter++;
            else if (minCost < minCostDiscovered) minCostCounter = 1, minCostDiscovered = minCost;
        }
        return;
    }

    mst(usedEdges, r, p, setSize, i + 1, numSets, minCost);

	pair<int, ii> front = edges[i];
	int a = findSet(p,front.S.F); int b = findSet(p, front.S.S);
    usedEdges[i] = 1, minCost += front.F % 1000000007, minCost %= 1000000007, connect(r, p, setSize, a, b), numSets--;
    mst(usedEdges, r, p, setSize, i + 1, numSets, minCost);
}

int main()
{
    ifstream in("escape.in");
    ofstream out("escape.out");

    int N, K; in >> N >> K;
    vi minExitEdges;

    rep(i, K - 1) { int w; in >> w; minExitEdges.pb(w); }
    rep(i, N - 2)
        rep(j, K - 1)
            in >> horiz[i][j];
    rep(i, K - 1) { int w; in >> w; minExitEdges.pb(w); }

    rep(i, N - 1) { int w; in >> w; minExitEdges.pb(w); }
    rep(i, K - 2)
        rep(j, N - 1)
            in >> vert[i][j];
    rep(i, N - 1) { int w; in >> w; minExitEdges.pb(w); }

    sort(minExitEdges.begin(), minExitEdges.end());
    int minExitEdgesCounter = 1, prev = minExitEdges[0]; // minExitEdgesCounter to be multiplied to the answer.
    while (prev == minExitEdges[minExitEdgesCounter]) minExitEdgesCounter++;

    //for (int i = 0; i < 5; i++, cout << endl) rep(j, 5) cout << vert[i][j] << " "; cout << endl;
    //for (int i = 0; i < 5; i++, cout << endl) rep(j, 5) cout << horiz[i][j] << " "; cout << endl;

    N--, K--;
    int V = N * K;
    rep(u, V)
    {
        int row = u / K, col = u % K;
        //D(u); D(row); D(col);
        if (col + 1 <  K) edges.pb(make_pair(vert[col][row], ii(u, u + 1)));
        if (row + 1 <  N) edges.pb(make_pair(horiz[row][col], ii(u, u + K)));
    }
    //rep(i, edges.size())
    //    printf("%d to %d in weight %d\n", edges[i].S.F, edges[i].S.S, edges[i].F);

    sort(edges.begin(), edges.end());
    vi r, p, setSize; // r is used to keep tree short. r meaning: "rank," p meaning: "parent."
    r.assign(V, 0); // init. r.
	p.assign(V, 0); for (int i = 1; i < V; i++) p[i] = i; // init. p.
	setSize.assign(V, 1); // init. setSize.
	int numSets = V;
	ll minCost = 0;

    mst(vector<bool>(edges.size(), 0), r, p, setSize, 0, V, 0);
	out << minCostCounter * minExitEdgesCounter << endl; // minExitEdgesCounter to be multiplied to the answer.

    return 0;
}
