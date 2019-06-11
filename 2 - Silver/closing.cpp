#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
using namespace std;

typedef vector<int> vi;

int n, m, visitedCount;
bool exists[3100], visited[3100];
vector<vi> adjList;

void dfs(int u)
{
	visitedCount++;
	visited[u] = 1;
	for (int i = 0; i < adjList[u].size(); i++)
	{
		int v = adjList[u][i];
		if (!visited[v]) dfs(v);
	}
}

int main()
{
	ifstream in("closing.in");
	ofstream out("closing.out");

	in >> n >> m;
	adjList.assign(n, vi());
	for (int i = 0; i < m; i++)
	{
		int u, v; in >> u >> v; u--; v--; // bi-directional
		adjList[u].push_back(v);
		adjList[v].push_back(u);
	}
	for (int i = 0; i < n; i++) exists[i] = 1;

	dfs(0); visitedCount == n ? out << "YES\n" : out << "NO\n";
	vi totalErased(0);
	for (int i = 0; i < n - 2; i++)
	{
		int erase; in >> erase; erase--;
		totalErased.push_back(erase);
		exists[erase] = 0;

		for (int j = 0; j < n; j++) visited[j] = 0;
		for (int j = 0; j < totalErased.size(); j++) visited[totalErased[j]] = 1;
		visitedCount = totalErased.size();

		for (int j = 0; j < n; j++)
			if (!visited[j])
			{ dfs(j); break; }
		visitedCount == n ? out << "YES\n" : out << "NO\n";
	}
	out << "YES\n";

	return 0;
}





































































































// the code below is accepted code that has some speed-ups
// all the speed-ups here are actually not necessary to pass the problem's time limit.

/*#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

typedef vector<int> vi;

vector<vi> adjList;
vi visited;
int countTrue;

void dfs(int here)
{
	visited[here] = true;
	countTrue++;

	for (int i = 0; i < adjList[here].size(); i++)
	{
		int there = adjList[here][i];
		if (!visited[there]) dfs(there);
	}
}

int main()
{
	ifstream in("closing.in");
	ofstream out("closing.out");

	int n, m;   in >> n >> m;
	adjList.assign(n, vi());
	for (int i = 0; i < m; i++)
	{
		int a, b;
		in >> a >> b;
		a--; b--;
		adjList[a].push_back(b); // what if it's connected to itself?
		adjList[b].push_back(a);
	}
	
	visited.assign(n, 0);
	int count = 0;
	for (int i = 0; i < n; i++)
	{
		if (!visited[i])
		{
			count++;
			if (count == 2) break;
			dfs(i);
		}
	}

	bool possiblyConnected = true; // speed up by not cainting dsf when not necessary
	int countFalse;
	if (count == 1) out << "YES\n";
	else
	{
		out << "NO\n";
		possiblyConnected = false;
		countFalse = n - countTrue;
	}

	vi deletedRooms;
	for (int i = 0; i < n - 2; i++)
	{
		int room;   in >> room;   room--;
		deletedRooms.push_back(room);
		
		if (!possiblyConnected) // give a chance for possiblyConnected to become true
		{
			if (visited[room]) countTrue--;
			else countFalse--;

			if (!countTrue || !countFalse)
				possiblyConnected = true;
			else out << "NO\n";
		}
		
		if (possiblyConnected)
		{
			countTrue = 0;
			visited.assign(n, 0);
			
			for (int j = 0; j < i + 1; j++)
				visited[deletedRooms[j]] = true;

			count = 0;
			for (int j = 0; j < n; j++)
			{
				if (!visited[j])
				{
					count++;
					if (count == 2) break;
					dfs(j);
				}
			}

			if (count == 1) out << "YES\n";
			else
			{
				out << "NO\n";
				possiblyConnected = false;
				countFalse = (n - i - 1) - countTrue;
			}
		}
	}

	out << "YES\n";

	return 0;
}*/