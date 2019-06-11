/*
ID: harrych2
PROG: holstein
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
using namespace std;

typedef vector<int> vi;

int v, g, minCount = 2100000000, ansTotal;
vi req, currValues, ansValues, ansIndices, currIndices;
vector<vi> scoop;

bool overReq()
{
	for (int i = 0; i < v; i++)
		if (req[i] > currValues[i])
			return false;
	//int currTotal = 0; for (int i = 0; i < v; i++) currTotal += currValues[i]; cout << currTotal << ":   ";
	//for (int i = 0; i < currIndices.size(); i++) cout << currIndices[i] << " "; cout << endl; cin.get();
	return true;
}

void solve(int index, int currCount)
{
	if (overReq())
	{
		if (currCount < minCount) // is this even what the problem wants? count min or total value min?
		{
			//cout << "="; int currTotal = 0; for (int i = 0; i < v; i++) currTotal += currValues[i]; cout << currTotal << ":   ";
			//for (int i = 0; i < currIndices.size(); i++) cout << currIndices[i] << " "; cout << endl; cin.get();
			minCount = currCount;
			ansIndices = currIndices, ansValues = currValues; // this works!   :)
			ansTotal = 0; for (int i = 0; i < v; i++) ansTotal += ansValues[i];
		}
		else if (currCount == minCount) // is this even what the problem wants?
		{
			//cout << "ENTERED ==! CIN\n"; cin.get();
			int currTotal = 0; for (int i = 0; i < currValues.size(); i++) currTotal += currValues[i];
			if (currTotal < ansTotal)
			{
				ansIndices = currIndices, ansValues = currValues;
				ansTotal = 0; for (int i = 0; i < v; i++) ansTotal += ansValues[i];
			}
		}
		return;
	}

	if (index == g) return;

	// take
	for (int i = 0; i < v; i++) currValues[i] += scoop[index][i]; // print this and test it!
	currIndices.push_back(index);
	solve(index + 1, currCount + 1);
	for (int i = 0; i < v; i++) currValues[i] -= scoop[index][i];
	currIndices.erase(currIndices.begin() + (currIndices.size() - 1));

	// ignore
	solve(index + 1, currCount);
}

int main()
{
	ifstream in("holstein.in");
	ofstream out("holstein.out");

	in >> v;
	for (int i = 0; i < v; i++)
	{
		int value; in >> value;
		req.push_back(value);
	}
	in >> g;
	scoop.assign(g, vi());
	for (int i = 0; i < g; i++)
		for (int j = 0; j < v; j++)
		{
			int value; in >> value;
			scoop[i].push_back(value);
		}

	currValues.assign(v, 0);
	solve(0, 0);
	sort(ansIndices.begin(), ansIndices.end());
	out << ansIndices.size(); // this is same as minCount
	for (int i = 0; i < ansIndices.size(); i++)
		out << " " << ansIndices[i] + 1;
	out << endl;

	return 0;
}