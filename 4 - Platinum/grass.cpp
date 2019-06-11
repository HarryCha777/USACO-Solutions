#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
using namespace std;

typedef pair<int, int> ii;
typedef vector<int> vi;

int V, E, k, q;

int main()
{
	ifstream in("grass.in");
	ofstream out("grass.out");

	in >> V >> E >> k >> q;
	vector< pair<int, ii> > edges;
	for (int i = 0; i < E; i++)
	{
		int u, v, w; in >> u >> v >> w; u--, v--;
		edges.push_back(make_pair(w, ii(u, v)));
	}
	sort(edges.begin(), edges.end());

	vi values(V);
	for (int i = 0; i < V; i++) in >> values[i];

	for (int a = 0; a < q; a++)
	{
		int index, newValue; in >> index >> newValue; index--;
		values[index] = newValue;

		for (int i = 0; i < edges.size(); i++)
		{
			int u = edges[i].second.first;
			int v = edges[i].second.second;

			if (values[u] != values[v])
			{
				out << edges[i].first << endl;
				break;
			}
		}
	}

	return 0;
}

/*

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
using namespace std;

int V, E, k, q;
int adjMatrix[5000][5000], values[5000];

int main()
{
	ifstream in("grass.in");
	ofstream out("grass.out");

	in >> V >> E >> k >> q;

	for (int i = 0; i < V; i++)
	{
		for (int j = 0; j < V; j++)
			adjMatrix[i][j] = 200000000;
		adjMatrix[i][i] = 0;
	}
	for (int i = 0; i < E; i++)
	{
		int u, v, w; in >> u >> v >> w; u--, v--;
		adjMatrix[u][v] = w;
		adjMatrix[v][u] = w;
	}
	for (int i = 0; i < V; i++) in >> values[i];

	for (int k = 0; k < V; k++)
		for (int i = 0; i < V; i++)
			for (int j = 0; j < V; j++)
				adjMatrix[i][j] = min(adjMatrix[i][j], adjMatrix[i][k] + adjMatrix[k][j]);

	for (int a = 0; a < q; a++)
	{
		int u, newValue; in >> u >> newValue; u--;
		values[u] = newValue;

		//for (int b = 0; b < V; b++) cout << values[b] << " "; cout << endl;

		int minDist = 2000000000;
		for (int i = 0; i < V; i++)
			for (int j = 0; j < V; j++)
				if (values[i] != values[j]) minDist = min(minDist, adjMatrix[i][j]);
		out << minDist << endl;
	}

	return 0;
}*/