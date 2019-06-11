/*
ID: harrych2
PROG: cowtour
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <algorithm>
#include <iomanip>
#include <string>
#include <cmath>
using namespace std;

typedef long long ll;
#define INF 1000000000

ll x[151], y[151];

double findDist(ll i, ll j)
{
	double deltaX = x[i] - x[j], deltaY = y[i] - y[j];
	return sqrt(deltaX*deltaX + deltaY*deltaY);
}

int main()
{
	ifstream in("cowtour.in");
	ofstream out("cowtour.out");

	ll V; in >> V;
	for (ll i = 0; i < V; i++) in >> x[i] >> y[i];

	double adjMatrix[160][160] = {};
	for (ll i = 0; i < V; i++)
	{
		string str; in >> str;
		for (ll j = 0; j < V; j++)
		{
			if (str[j] == '1') adjMatrix[i][j] = findDist(i, j);
			else adjMatrix[i][j] = INF;
		}
		adjMatrix[i][i] = 0;
	}

	for (ll k = 0; k < V; k++)
		for (ll i = 0; i < V; i++)
			for (ll j = 0; j < V; j++)
				adjMatrix[i][j] = min(adjMatrix[i][j], adjMatrix[i][k] + adjMatrix[k][j]);

	//for (int i = 0; i < V; i++) // printing adjMatrix
	//{for (int j = 0; j < V; j++) adjMatrix[i][j]==INF ? cout<<"INF\t" : cout<<adjMatrix[i][j]<<"\t"; cout<<endl;} cout<<endl;

	double maxDist[151] = {};
	for (ll i = 0; i < V; i++)
		for (ll j = 0; j < V; j++)
			if (adjMatrix[i][j] != INF)
				maxDist[i] = max(maxDist[i], adjMatrix[i][j]);

	//for (int i = 0; i < V; i++) cout << maxDist[i] << " "; cout << endl; cout << endl; // printing maxDist

	double minDiam = INF;
	for (ll i = 0; i < V; i++)
		for (ll j = 0; j < V; j++)
			if (adjMatrix[i][j] == INF)
				minDiam = min(minDiam, maxDist[i] + maxDist[j] + findDist(i, j));

	for (ll i = 0; i < V; i++) minDiam = max(minDiam, maxDist[i]); // this must be done after previous loops

	out << setprecision(6) << fixed << minDiam << endl;

	return 0;
}

/*

#include <iostream>
#include <fstream>
#include <algorithm>
#include <iomanip>
#include <cstring>
#include <string>
#include <vector>
#include <climits>
#include <cmath>
using namespace std;

typedef long long ll;
#define INF 1000000000

ll V;
double currAdjMatrix[160][160];

void floydWarshall() // must calculate this once otside any loop to pass the time limit
{
	for (ll k = 0; k < V; k++)
		for (ll i = 0; i < V; i++)
			for (ll j = 0; j < V; j++)
				currAdjMatrix[i][j] = min(currAdjMatrix[i][j], currAdjMatrix[i][k] + currAdjMatrix[k][j]); // save in a method?
}

ll main()
{
	ifstream in("cowtour.in");
	ofstream out("cowtour.out");

	in >> V;
	vector<ll> x(0), y(0);
	for (ll i = 0; i < V; i++)
	{
		ll posX, posY; in >> posX >> posY;
		x.push_back(posX); y.push_back(posY);
	}

	double adjMatrix[160][160];
	for (ll i = 0; i < V; i++)
	{
		string str; in >> str;
		for (ll j = 0; j < V; j++)
		{
			if (str[j] == '1')
			{
				ll deltaX = abs(x[i] - x[j]), deltaY = abs(y[i] - y[j]);
				if (deltaX && deltaY)	adjMatrix[i][j] = sqrt(deltaX*deltaX + deltaY*deltaY);
				else if (deltaX)		adjMatrix[i][j] = deltaX;
				else if (deltaY)		adjMatrix[i][j] = deltaY;
				// there cannot be "none of the above"
			}
			else
			{
				adjMatrix[i][j] = INF;
			}
		}
	}
	
	// print the adj. matrix
	//for (ll a = 0; a < V; a++)
	//{
	//	for (ll b = 0; b < V; b++)
	//		cout << adjMatrix[a][b] << "\t";
	//		//adjMatrix[a][b] == INF ? cout << 0 << " " : cout << 1 << " ";
	//	cout << endl;
	//}cout << endl << endl; cin.get();

	double minDiam = LLONG_MAX;
	for (ll a = 0; a < V; a++)
		for (ll b = a; b < V; b++)
		{
			if (adjMatrix[a][b] != INF || a == b) continue;

			ll deltaX = abs(x[a] - x[b]), deltaY = abs(y[a] - y[b]);
			if (deltaX && deltaY)	adjMatrix[a][b] = adjMatrix[b][a] = sqrt(deltaX*deltaX + deltaY*deltaY); // bi-directional
			else if (deltaX)		adjMatrix[a][b] = adjMatrix[b][a] = deltaX;
			else if (deltaY)		adjMatrix[a][b] = adjMatrix[b][a] = deltaY;
			
			memcpy(currAdjMatrix, adjMatrix, sizeof adjMatrix); floydWarshall(); // currAdjMatrix'll be changing
			double currDiam = 0;
			for (ll i = 0; i < V; i++)
				for (ll j = 0; j < V; j++)
					if (i != j)
						currDiam = max(currDiam, currAdjMatrix[i][j]);

			adjMatrix[a][b] = adjMatrix[b][a] = INF;
			minDiam = min(minDiam, currDiam);
		}

	out << setprecision(6) << fixed << minDiam << endl; // use digit precision!
	// remember: when you add a path, you must do it to [i][j] AND [j][i] as well because is it bi-directional!
	// change everything to long long double or something like that

	return 0;
}*/