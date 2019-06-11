#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

#define INF 1000000000

int main()
{
	ifstream in("vacation.in");
	ofstream out("vacation.out");

	int V, E, K, Q, adjMat[210][210]; in >> V >> E >> K >> Q;
	for (int i = 0; i < V; i++)
		for (int j = 0; j < V; j++)
			i == j ? adjMat[i][j] = 0 : adjMat[i][j] = INF;
	for (int i = 0; i < E; i++)
	{
		int u, v, w; in >> u >> v >> w; u--, v--;
		adjMat[u][v] = w;
	}

	for (int k = 0; k < V; k++)
		for (int i = 0; i < V; i++)
			for (int j = 0; j < V; j++)
				adjMat[i][j] = min(adjMat[i][j], adjMat[i][k] + adjMat[k][j]);

	long long count = 0, cost = 0;
	for (int i = 0; i < Q; i++)
	{
		int u, v; in >> u >> v; u--, v--; // source and destination
		int minCost = INF;
		for (int j = 0; j < K; j++)
			minCost = min(minCost, adjMat[u][j] + adjMat[j][v]);
		if (minCost != INF) count++, cost += minCost;
	}
	out << count << endl;
	out << cost << endl;

	return 0;
}




















































































































/*

#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

#define INF 1000000000

int main()
{
	ifstream in("vacation.in");
	ofstream out("vacation.out");

	int V, E, K, Q, adjMatrix[210][210];
	in >> V >> E >> K >> Q;
	for (int i = 0; i < V; i++)
	{
		for (int j = 0; j < V; j++)
			adjMatrix[i][j] = INF;
		adjMatrix[i][i] = 0;
	}

	for (int i = 0; i < E; i++)
	{
		int u, v, w; in >> u >> v >> w; u--, v--;
		adjMatrix[u][v] = w;
	}
	
	for (int k = 0; k < V; k++)
		for (int i = 0; i < V; i++)
			for (int j = 0; j < V; j++)
				adjMatrix[i][j] = min(adjMatrix[i][j], adjMatrix[i][k] + adjMatrix[k][j]);

	int valid = 0;
	long long sum = 0;
	for (int i = 0; i < Q; i++)
	{
		int s, d; in >> s >> d; s--, d--; // source and destination
		int minCost = INF;
		for (int j = 0; j < K; j++)
			minCost = min(minCost, adjMatrix[s][j] + adjMatrix[j][d]);
		if (minCost != INF) valid++, sum += minCost;
	}
	out << valid << endl;
	out << sum << endl;

	return 0;
}*/

// Below is wrong. For some reason, it doesn't count some answers (and a little too slow.)
/*

#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

#define INF 1000000000

int K, adjMatrix[210][210], p[210][210];

bool hasHub(int i, int j)
{
	if (j < K) return true;
	if (i == j) return false;
	return hasHub(i, p[i][j]);
}

int main()
{
	ifstream in("vacation.in");
	ofstream out("vacation.out");

	int V, E, Q, oriInput[210][210];
	in >> V >> E >> K >> Q;
	for (int i = 0; i < V; i++)
	{
		for (int j = 0; j < V; j++)
			oriInput[i][j] = INF;
		oriInput[i][i] = 0;
	}

	int edges[10010][3];
	for (int i = 0; i < E; i++)
	{
		int u, v, w; in >> u >> v >> w; u--, v--;
		oriInput[u][v] = w;
		edges[i][0] = u; edges[i][1] = v; edges[i][2] = w;
	}
	int s[10010], d[10010]; // source and destination
	for (int i = 0; i < Q; i++) in >> s[i] >> d[i], s[i]--, d[i]--;

	int minCost[10010];
	for (int i = 0; i < Q; i++) minCost[i] = 2000000000;
	for (int i = 0; i < Q; i++)
		for (int j = 0; j < E; j++) // checking from edges (like last row of sample)
			if (edges[j][0] == s[i] && edges[j][1] == d[i] && (s[i] < K || d[i] < K))
				minCost[i] = min(minCost[i], edges[j][2]);
	// maybe above takes too long...maybe use vector inside a vector (size using push_back)

	for (int i = 0; i < V; i++) // setting adjMatrix to oriInput
		for (int j = 0; j < V; j++)
			adjMatrix[i][j] = oriInput[i][j];
	for (int i = 0; i < V; i++) // initializing p
		for (int j = 0; j < V; j++)
			p[i][j] = i;

	for (int k = 0; k < V; k++) // also checking by optimizing adjMatrix
		for (int i = 0; i < V; i++)
			for (int j = 0; j < V; j++)
				if (adjMatrix[i][j] > adjMatrix[i][k] + adjMatrix[k][j])
				{
					adjMatrix[i][j] = adjMatrix[i][k] + adjMatrix[k][j];
					p[i][j] = p[k][j];
					for (int a = 0; a < Q; a++)
						if (i == s[a] && j == d[a] && hasHub(i, j))
							minCost[a] = min(minCost[a], adjMatrix[i][j]);
				}

	int valid = 0, sum = 0;
	for (int i = 0; i < Q; i++) if (minCost[i] != 2000000000) valid++, sum += minCost[i];
	
	out << valid << endl;
	out << sum << endl;

	return 0;
}*/