#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

typedef vector<int> vi;

int b, e, p, V, E;
vector<vi> adjList;
vi pB, pE, pathB, pathE;

int bfsB()
{
	int s = 0;
	vi dist(V, -1); dist[s] = 0;
	queue<int> q; q.push(s);
	pB.assign(V, -1);

	while (!q.empty())
	{
		int u = q.front(); q.pop();
		for (int j = 0; j < adjList[u].size(); j++)
		{
			int v = adjList[u][j];
			if (dist[v] == -1)
			{
				dist[v] = dist[u] + b;
				pB[v] = u;
				q.push(v);
			}
		}
	}
	return dist[V - 1];
}

int bfsE()
{
	int s = 1;
	vi dist(V, -1); dist[s] = 0;
	queue<int> q; q.push(s);
	pE.assign(V, -1);

	while (!q.empty())
	{
		int u = q.front(); q.pop();
		for (int j = 0; j < adjList[u].size(); j++)
		{
			int v = adjList[u][j];
			if (dist[v] == -1)
			{
				dist[v] = dist[u] + e;
				pE[v] = u;
				q.push(v);
			}
		}
	}
	return dist[V - 1];
}

void makePathB(int u)
{
	if (u == 0) { return; }
	makePathB(pB[u]);
	pathB.push_back(u);
}

void makePathE(int u)
{
	if (u == 1) { return; }
	makePathE(pE[u]);
	pathE.push_back(u);
}

int main()
{
	ifstream in("piggyback.in");
	ofstream out("piggyback.out");

	in >> b >> e >> p >> V >> E;
	adjList.assign(V, vi());
	for (int i = 0; i < E; i++)
	{
		int u, v; in >> u >> v; u--; v--;
		adjList[u].push_back(v);
		adjList[v].push_back(u); // bi-directional
	}

	int resB = bfsB();
	int resE = bfsE(); // combining bfsB and bfsE can cause many confusing problems.
	makePathB(V - 1); // path from 0 to V - 1 (excluding 0)
	makePathE(V - 1); // path from 1 to V - 1 (excluding 1)

	cout << resB << " " << resE << endl;
	for (int i = 0; i < pathB.size(); i++) cout << pathB[i] << " "; cout << endl;
	for (int i = 0; i < pathE.size(); i++) cout << pathE[i] << " "; cout << endl;
	cin.get();

	// find out the route they travel through p. if there is any barn they go through together,
	// they are doing piggyback starting from that barn to the end in the same route.
	// but if they don't have any barn commonly shared in their routes, just combine resB and resE;

	for (int i = 0; i < pathB.size() - 1; i++) // - 1 so that V-1 doesn't count
		for (int j = 0; j < pathE.size() - 1; j++) // - 1 so that V-1 doesn't count
			if (pathB[i] == pathE[j])
			{
				out << (i * b) + (j * e) + ((pathB.size() - i) * p) << endl;
				// ((pathB.size() - i) * p) is same as ((pathE.size() - j) * p)
				return 0;
			}
	out << resB + resE << endl; // this is same as pathB.size()*b + pathE.size()*e.

	// RIGHT NOW, THIS CODE IS WRONG...TRY THE CODE RIGHT BELOW THIS ONE.

	return 0;
}

































































































































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

int b, e, p, n, m, piggyAns, bessieAlone, elsieAlone;
vector<vi> adjList;
vi distB, distE, closestPoints;

void bfs(int s, int key)
{
	vi dist(n, -1); dist[s] = 0; // if unreachable, it'll stay -1. By key 1 & 2, it'll be -b or -e.
	queue<int> q; q.push(s);

	while (!q.empty())
	{
		int u = q.front(); q.pop();
		if (key != 3 && u == n - 1) continue; // don't go on if it's n-1 point (except key 3)
		for (int j = 0; j < adjList[u].size(); j++)
		{
			int v = adjList[u][j];
			if (dist[v] == -1)
			{
				dist[v] = dist[u] + 1;
				q.push(v);
			}
		}
	}

	if (key == 1)
	{
		bessieAlone = dist[n - 1] * b;
		for (int i = 0; i < n; i++)
			distB[i] = dist[i];
	}
	if (key == 2)
	{
		elsieAlone = dist[n - 1] * e;
		for (int i = 0; i < n; i++)
			distE[i] = dist[i];
	}
	if (key == 3)
	{
		// work backwards. this turns "closestPoints.size() bfs" into a single bfs
		int minDist = 2000000000;
		for (const int &i : closestPoints)
			minDist = min(minDist, dist[i]);
		piggyAns += minDist * p; // notice "+="
	}
}

int main()
{
	ifstream in("piggyback.in");
	ofstream out("piggyback.out");

	in >> b >> e >> p >> n >> m;
	adjList.assign(n, vi(0));
	for (int i = 0; i < m; i++)
	{
		int u, v; in >> u >> v; u--; v--; // bi-directional
		adjList[u].push_back(v);
		adjList[v].push_back(u);
	}
	
	distB.assign(n, 0); bfs(0, 1); // bessie
	distE.assign(n, 0); bfs(1, 2); // elsie
	vi pointEner(n), pointDist(n);
	for (int i = 0; i < n; i++)
		if (distB[i]*b >= 0 || distE[i]*e >= 0)
			pointEner[i] = distB[i]*b + distE[i]*e;
		else // if this cannot be reached by Bessie or Elsie or both,
			pointEner[i] = 2000000000;

	//cout << "B-------------\n";
	//for (int i = 0; i < n; i++)
	//	cout << pointEnerB[i] << endl;
	//cout << "E-------------\n";
	//for (int i = 0; i < n; i++)
	//	cout << pointEnerE[i] << endl;
	//cout << "B F--------END\n";
	//cout << "POINTENER-------------\n";
	//for (int i = 0; i < n; i++)
	//	cout << pointEner[i] << " ";
	//cout << "POINTENER----------END\n";
	//cin.get();

	int minEner = 2000000000;
	for (int i = 0; i < n; i++)
	{
		if (pointEner[i] < minEner)
		{
			minEner = pointEner[i];
			closestPoints.assign(0, 0);
			closestPoints.push_back(i);
		}
		else if (pointEner[i] == minEner) // (MUST be "else if")
		{
			closestPoints.push_back(i);
		}
	}

	piggyAns = minEner; // energy it takes to gather together
	bfs(n - 1, 3); // start from the destination(n - 1)
	out << min(piggyAns, bessieAlone + elsieAlone) << endl;
	//cout << bessieAlone + elsieAlone << endl; cin.get();

	return 0;
}*/

// below is failed attempt of trying to implement dist of the code above.
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

int b, e, p, n, m, piggyAns1, piggyAns2, bessieAlone, elsieAlone;
vector<vi> adjList;
vi distB, distE, closestPointEner, closestPointDist;

void bfs(int s, int key)
{
	vi dist(n, -1); dist[s] = 0; // if unreachable, it'll stay -1. By key 1 & 2, it'll be -b or -e.
	queue<int> q; q.push(s);

	while (!q.empty())
	{
		int u = q.front(); q.pop();
		if (key != 3 && key != 4 && u == n - 1) continue; // don't go on if it's n-1 point (except key 3 & 4)
		for (int j = 0; j < adjList[u].size(); j++)
		{
			int v = adjList[u][j];
			if (dist[v] == -1)
			{
				dist[v] = dist[u] + 1;
				q.push(v);
			}
		}
	}

	if (key == 1)
	{
		bessieAlone = dist[n - 1] * b;
		for (int i = 0; i < n; i++)
			distB[i] = dist[i];
	}
	if (key == 2)
	{
		elsieAlone = dist[n - 1] * e;
		for (int i = 0; i < n; i++)
			distE[i] = dist[i];
	}
	if (key == 3)
	{
		// work backwards. this turns "closestPointEner.size() bfs" into a single bfs
		int minDist = 2000000000;
		for (const int &i : closestPointEner)
			minDist = min(minDist, dist[i]);
		piggyAns1 += minDist * p; // notice "+="
	}
	if (key == 4)
	{
		// work backwards. this turns "closestPointEner.size() bfs" into a single bfs
		int minDist = 2000000000;
		for (const int &i : closestPointDist)
			minDist = min(minDist, dist[i]);
		piggyAns2 += minDist * p; // notice "+="
	}
}

int main()
{
	ifstream in("piggyback.in");
	ofstream out("piggyback.out");

	in >> b >> e >> p >> n >> m;
	adjList.assign(n, vi(0));
	for (int i = 0; i < m; i++)
	{
		int u, v; in >> u >> v; u--; v--; // bi-directional
		adjList[u].push_back(v);
		adjList[v].push_back(u);
	}
	
	distB.assign(n, 0); bfs(0, 1); // bessie
	distE.assign(n, 0); bfs(1, 2); // elsie
	vi pointEner(n), pointEner2(n), pointDist(n);
	for (int i = 0; i < n; i++)
	{
		if (distB[i]*b >= 0 || distE[i]*e >= 0)
			pointEner[i] = distB[i]*b + distE[i]*e;
		else // if this cannot be reached by Bessie or Elsie or both,
			pointEner[i] = 2000000000;

		if (distB[i] >= 0 || distE[i] >= 0)
			pointEner2[i] = distB[i]*b + distE[i]*e, pointDist[i] = distB[i] + distE[i];
		else // if this cannot be reached by Bessie or Elsie or both,
			pointEner2[i] = 2000000000, pointDist[i] = 2000000000;
	}

	int minEner = 2000000000;
	for (int i = 0; i < n; i++)
	{
		if (pointEner[i] < minEner)
		{
			minEner = pointEner[i];
			closestPointEner.assign(0, 0);
			closestPointEner.push_back(i);
		}
		else if (pointEner[i] == minEner) // (MUST be "else if")
		{
			closestPointEner.push_back(i);
		}
	}
	int minEner2 = 2000000000, minDist = 2000000000;
	for (int i = 0; i < n; i++)
	{
		if (pointDist[i] < minDist)
		{
			minDist = pointDist[i];
			minEner2 = pointEner2[i];
			closestPointDist.assign(0, 0);
			closestPointDist.push_back(i);
		}
		else if (pointDist[i] == minDist) // (MUST be "else if")
		{
			closestPointDist.push_back(i);
		}
	}

	piggyAns1 = minEner; // energy it takes to gather together
	piggyAns2 = minEner2;
	bfs(n - 1, 3); // start from the destination(n - 1)
	bfs(n - 1, 4);
	out << min(min(piggyAns1, piggyAns2), bessieAlone + elsieAlone) << endl;
	//cout << bessieAlone + elsieAlone << endl; cin.get();

	//cout << piggyAns1 << " " << piggyAns2 << endl; cin.get();

	return 0;
}
*/