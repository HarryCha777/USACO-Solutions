/*
ID: harrych2
PROG: concom
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <algorithm>
#include <cstring>
#include <bitset>
using namespace std;

int limit = 100, n, p[110][110], companies[110];
bitset <110> visited;

void dfs(int x)
{
	visited[x] = 1;
	for (int i = 1; i <= limit; i++)
		companies[i] += p[x][i];
	for (int i = 1; i <= limit; i++)
		if (!visited[i] && 50 <= companies[i] && i != x)
			dfs(i);
}

int main()
{
	ifstream in("concom.in");
	ofstream out("concom.out");

	in >> n;
	for (int i = 0; i < n; i++)
	{
		int a, b; in >> a >> b;
		in >> p[a][b];
	}

	for (int i = 1; i <= limit; i++)
	{
		memset(companies, 0, sizeof companies);
		visited.reset();

		dfs(i);

		for (int j = 1; j <= limit; j++) // auto-sorted
			if (50 <= companies[j] && i != j)
				out << i << " " << j << endl;
	}

	return 0;
}

// code below is too complicated and slow (it stops at the last test case)
/*

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
using namespace std;

typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<int> vi;

int n, compNum; // number of existing companies
vii inputAB(0), ans(0);
vi inputP(0);
vector<vi> contList(110, vi()); // control list

int calc(int a, int b, int c)
{
	int sumP = 0;
	for (int i = 0; i < n; i++)
	{
		if (inputAB[i].first == b && inputAB[i].second == c)
			sumP += inputP[i];
	}
	return sumP;
}

int main()
{
	ifstream in("concom.in");
	ofstream out("concom.out");

	in >> n; int decreasedN = 0;
	for (int i = 0; i < n; i++)
	{
		int a, b, p; in >> a >> b >> p;
		if (a == b) { decreasedN++; }
		else		{ inputAB.push_back(ii(a, b)); inputP.push_back(p); }
		compNum = max(compNum, a); compNum = max(compNum, b);
	}
	n -= decreasedN;

	for (int i = 0; i < n; i++) if (inputP[i] > 50) ans.push_back(ii(inputAB[i].first, inputAB[i].second));
	for (int i = 0; i < ans.size(); i++) contList[ans[i].first].push_back(ans[i].second);
	
	// print comtList
	//for (int i = 1; i <= compNum; i++)
	//{ cout << i << ":   "; for (int j = 0; j < contList[i].size(); j++) cout << contList[i][j] << " "; cout << endl; } cin.get();
	
	for (int z = 0; z < 10; z++) // how much should this whole loop be repeated few times because ans and contList are changing?
	for (int a = 1; a <= compNum; a++) // notice 1 to compNum + 1 (NOT n + 1...it's companyNum + 1)
	{
		for (int c = 1; c <= compNum; c++) // notice 1 to compNum + 1
		{
			// "company a" will try to control "company c "with using companies it controls ("company b")
			if (a == c) continue;
			if (find(contList[a].begin(), contList[a].end(), c) != contList[a].end()) continue; // if (c is already controlled by a)

			int totalP = 0;
			for (int i = 0; i < contList[a].size(); i++)
			{
				int b = contList[a][i];
				if (b == c) continue;
				totalP += calc(a, b, c);
				if (totalP > 50) break;
			}
			if (totalP > 50)
			{
				ans.push_back(ii(a, c));
				contList[a].push_back(c);
			}
		}
	}

	sort(ans.begin(), ans.end());
	int firstPrev = -1, secondPrev = -1;
	for (int i = 0; i < ans.size(); i++)
	{
		if (!(ans[i].first == firstPrev && ans[i].second == secondPrev) && !(ans[i].first == ans[i].second))
			out << ans[i].first << " " << ans[i].second << endl;
		firstPrev = ans[i].first;
		secondPrev = ans[i].second;
	}

	return 0;
}*/