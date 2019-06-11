/*
ID: harrych2
PROG: agrinet
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
using namespace std;

typedef pair<int, int> ii;
typedef vector<int> vi;

class UnionFind
{
private:
	vi p, rank, setSize;
	int numSets;
public:
	UnionFind(int N)
	{
		setSize.assign(N, 1); numSets = N; rank.assign(N, 0);
		p.assign(N, 0); for (int i = 0; i < N; i++) p[i] = i;
	}

	int findSet(int i) { return (p[i] == i) ? i : (p[i] = findSet(p[i])); }
	bool isSameSet(int i, int j) { return findSet(i) == findSet(j); }
	void unionSet(int i, int j)
	{
		if (!isSameSet(i, j))
		{
			numSets--;
			int x = findSet(i), y = findSet(j);

			if (rank[x] > rank[y]) { p[y] = x; setSize[x] += setSize[y]; }
			else
			{
				p[x] = y; setSize[y] += setSize[x];
				if (rank[x] == rank[y]) rank[y]++;
			}
		}
	}
	int numDisjointSets() { return numSets; }
	int sizeOfSet(int i) { return setSize[findSet(i)]; }
};

int main()
{
	ifstream in("agrinet.in");
	ofstream out("agrinet.out");

	int V; in >> V;
	vector< pair<int, ii> > edgeList(0);
	for (int i = 0; i < V; i++)
	{
		for (int j = 0; j < V; j++)
		{
			int w; in >> w; if (i == j) continue;
			edgeList.push_back(make_pair(w, ii(i, j)));
		}
	}
	sort(edgeList.begin(), edgeList.end()); // don't forget to sort!!!
	int E = edgeList.size();

	int minCost = 0;
	UnionFind UF(V);
	for (int i = 0; i < E; i++)
	{
		pair<int, ii> front = edgeList[i];
		if (!UF.isSameSet(front.second.first, front.second.second)) // if no cycle
		{
			minCost += front.first;
			UF.unionSet(front.second.first, front.second.second);
		}
	}

	out << minCost << endl;

	return 0;
}