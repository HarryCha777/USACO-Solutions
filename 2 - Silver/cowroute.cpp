#include <iostream>
#include <fstream>
#include <algorithm>
#include <cstring>
#include <vector>
using namespace std;

#define MAXV 1010
typedef long long ll;

bool vis[MAXV];
pair<ll, int> cost_a2u[MAXV];
pair<ll, int> cost[MAXV][MAXV];

int main()
{
	ifstream in("cowroute.in");
	ofstream out("cowroute.out");

	int A, B, N;
	in >> A >> B >> N;

	/* Initialize cost matrix to infinity. */
	memset(cost, 0x3F, sizeof(cost));
	for (int i = 0; i < MAXV; i++) cost[i][i] = make_pair(0, 0);

	for (int i = 0; i < N; i++)
	{
		ll route_cost;
		int route_len;
		in >> route_cost >> route_len;

		vector<int> route(route_len);
		for (int j = 0; j < route_len; j++)
		{
			in >> route[j];

			/* Update the cost from everything before this city to this city. */
			for (int k = 0; k < j; k++)
				cost[route[k]][route[j]] = min(cost[route[k]][route[j]],
					make_pair(route_cost, j - k));
		}
	}

	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			if (4557430888798830399 == cost[i][j].first) out << "(X, X), ";
			else out << "(" << cost[i][j].first << ", " << cost[i][j].second << "), ";
		}
		out << endl;
	}

	/* Perform Dijkstra without a heap in O(V^2) time. */
	memset(vis, 0, sizeof(vis));
	memset(cost_a2u, 0x3F, sizeof(cost_a2u));
	cost_a2u[A] = make_pair(0, 0);
	for (int i = 0; i < MAXV; i++)
	{
		/* Find the closest unvisited vertex. */
		int u = -1;
		for (int j = 0; j < MAXV; j++) if (!vis[j])
			if (u == -1 || cost_a2u[j] < cost_a2u[u])
				u = j;

		/* Relax vertex u. */
		vis[u] = true;
		for (int j = 0; j < MAXV; j++)
		{
			pair<ll, int> rlx = cost_a2u[u];
			rlx.first += cost[u][j].first;
			rlx.second += cost[u][j].second;
			cost_a2u[j] = min(cost_a2u[j], rlx);
		}
	}

	/* Output the cheapest cost and length if possible. */
	cost_a2u[B].second <= MAXV ?
		out << cost_a2u[B].first << ' ' << cost_a2u[B].second << endl : out << "-1 -1\n";

	return 0;
}

/*
#include <fstream>

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<long> vl;
#define INF 1000000000

int main()
{
	ifstream in("cowroute.in");
	ofstream out("cowroute.out");

	int a, b, n; in >> a >> b >> n; // a is the source
	vector<vii> adjList(1100, vii());
	vector<vl> indexList(1100, vl(0));
	vector<vl> input(1100, vl(0));
	for (int i = 0; i < n; i++)
	{
		int cost, citiesNum, prevCity; in >> cost >> citiesNum;
		for (int j = 0; j < citiesNum; j++)
		{
			int currCity; in >> currCity;
			if (j) { adjList[prevCity].push_back(ii(currCity, cost));          indexList[prevCity].push_back(i); }
			prevCity = currCity;
			input[i].push_back(currCity); // save for later use
		}
	}

	// print adjList
	for (int i = 0; i < 10; i++)
	{ printf("index %d:   ", i);
		for (int j = 0; j < adjList[i].size(); j++) printf("(%d, %d) ", adjList[i][j].first, adjList[i][j].second);
		printf("\n"); }
	// print indexList
	for (int i = 0; i < 10; i++)
	{
		printf("index %d:   ", i);
		for (int j = 0; j < indexList[i].size(); j++)
			cout << indexList[i][j] << " "; printf("\n");
	} printf("\n");

	vl dist(1100, INF); dist[a] = 0;
	priority_queue<ii> pq; pq.push(ii(0, a)); // if <ii> doesn't seem to work, try < ii, vector<ii>, greater<ii> > pq;
	long long countFlights = 0; // or in vl like dist?
	while (!pq.empty())
	{
		ii front = pq.top(); pq.pop();
		int d = front.first, u = front.second;
		if (d > dist[u]) continue;
		for (int j = 0; j < adjList[u].size(); j++)
		{
			ii v = adjList[u][j];
			int distValue = dist[u];
			bool foundU = false;
			for (int k = 0; k < input[indexList[u][j]].size(); k++) // see if it's in same plane
			{
				if (input[indexList[u][j]][k] == u) foundU = true; // this should come first
				if (foundU && input[indexList[u][j]][k] == v.second)
				{
					printf("u: %d v: %d\n", u, v.first);
					distValue = 0;
					break;
				}
			}
			if (dist[v.first] > distValue + v.second)
			{
				dist[v.first] = distValue + v.second;
				pq.push(ii(dist[v.first], v.first));
			}
		}
	}

	dist[b] == INF ? cout << -1 << " " << -1 : cout << dist[b] << " " << countFlights;
	while (1);

	return 0;
}

// use long long for the total cost*/