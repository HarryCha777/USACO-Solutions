#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
using namespace std;

typedef vector<int> vi;

vi nums;
vector<vi> tree;
int oriValue;

int count(int index)
{
	int ret = 0;
	for (int i = 0; i < tree[index].size(); i++)
	{
		if (oriValue < nums[tree[index][i]]) ret++;
		ret += count(tree[index][i]);
	}
	return ret;
}

int main()
{
	ifstream in("promote.in");
	ofstream out("promote.out");

	int n; in >> n;
	nums.assign(n, 0);
	for (int i = 0; i < n; i++) in >> nums[i];

	tree.assign(n, vi());
	for (int i = 1; i < n; i++)
	{
		int index; in >> index; index--;
		tree[index].push_back(i);
	}

	for (int i = 0; i < n; i++)
	{
		oriValue = nums[i];
		out << count(i) << endl;
	}

	return 0;
}













































































































/*

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <set>
using namespace std;

typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<int> vi;

vector<vii> tree;
//set<int> alreadyVisited; // use map?

int oriValue;
int count(int u)
{
	int ret = 0;
	//if (alreadyVisited.find(u) == alreadyVisited.end())
		for (int j = 0; j < tree[u].size(); j++)
		{
			if (oriValue < tree[u][j].second) ret++;
			ret += count(tree[u][j].first);
		}
	return ret;
}

int main() // 2017 Jan. PLATINUM 1
{
	ifstream in("promote.in");
	ofstream out("promote.out");

	int n; in >> n;
	vi input(n);
	for (int i = 0; i < n; i++) in >> input[i];
	tree.assign(n, vii());
	for (int i = 1; i < n; i++)
	{
		int p; in >> p; p--;
		tree[p].push_back(ii(i, input[i]));
	}

	//for (int i = 0; i < n; i++)
	//{
	//	cout << i + 1 << ":   ";
	//	for (int j = 0; j < tree[i].size(); j++)
	//		printf("(%d, %d)", tree[i][j].first + 1, tree[i][j].second);
	//	printf("\n");
	//} cin.get();

	for (int i = 0; i < n; i++)
		oriValue = input[i], out << count(i) << endl;

	//vi ans(n, 0);
	//for (int i = n - 1; i >= 0; i--)
	//{
	//	oriValue = input[i];
	//	alreadyVisited.clear();
	//	for (int j = i + 1; j < n; j++)
	//		if (input[i] < input[j]) ans[i] += ans[j] + 1, alreadyVisited.insert(j);
	//	ans[i] += count(i);
	//}
	//for (int i = 0; i < n; i++) out << ans[i] << endl;

	return 0;
}*/

/*

#include <iostream>
#include <fstream>
#include <algorithm>
#include <cstring>
#include <vector>
using namespace std;

typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<int> vi;

vector<vii> tree;
int memo[100010]; // use set or map?

int oriValue;
int count(int u)
{
	if (memo[u] != -1) return memo[u];

	int ret = 0;
	for (int j = 0; j < tree[u].size(); j++)
	{
		if (oriValue < tree[u][j].second) ret++;
		ret += count(tree[u][j].first);
	}
	return ret;
}

int main()
{
	ifstream in("promote.in");
	ofstream out("promote.out");

	int n; in >> n;
	vi input(n);
	for (int i = 0; i < n; i++) in >> input[i];
	tree.assign(n, vii());
	for (int i = 1; i < n; i++)
	{
		int p; in >> p; p--;
		tree[p].push_back(ii(i, input[i]));
	}

	vi ans(n, 0);
	memset(memo, -1, sizeof memo);
	for (int i = n - 1; i >= 0; i--)
	{
		oriValue = input[i];
		ans[i] = count(i);
		memo[i] = ans[i];
	}
	for (int i = 0; i < n; i++) out << ans[i] << endl;

	return 0;
}*/