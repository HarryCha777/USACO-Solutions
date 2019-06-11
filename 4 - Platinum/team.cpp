#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
using namespace std;

typedef vector<int> vi;

int n, m, k, john[1010], paul[1010];
//bool johnUsed[1010], paulUsed[1010];
vi johnK, paulK;

bool check()
{
	sort(johnK.begin(), johnK.end());
	sort(paulK.begin(), paulK.end());
	//for (int i = 0; i < k; i++) cout << johnK[i] << " "; cout << endl;
	//for (int i = 0; i < k; i++) cout << paulK[i] << " "; cout << endl; cout << endl;

	for (int i = 0; i < k; i++)
		if (johnK[i] <= paulK[i])
			return false;
	return true;
}

/*int waysPaul(int prev, int count)
{
	if (count == k) return check();

	int res = 0;
	for (int i = prev; i < n; i++) if (!paulUsed[i])
	{
		paulUsed[i] = 1; paulK.push_back(paul[i]);
		res += waysPaul(i + 1, count + 1);
		paulUsed[i] = 0; paulK.erase(paulK.begin() + paulK.size() - 1);
	}
	res %= 1000000009;
	return res;
}*/

int waysPaul(int index, int count)
{
	if (count == k) return check();
	if (index == m) return 0;

	paulK.push_back(paul[index]);
	int takeRes = waysPaul(index + 1, count + 1); // take
	paulK.erase(paulK.begin() + paulK.size() - 1);

	int ignoreRes = waysPaul(index + 1, count); // ignore

	return (takeRes + ignoreRes) % 1000000009;
}

/*int waysJohn(int prev, int count)
{
	if (count == k) return waysPaul(0, 0);

	int res = 0;
	for (int i = prev; i < n; i++) if (!johnUsed[i])
	{
		johnUsed[i] = 1; johnK.push_back(john[i]);
		res += waysJohn(i + 1, count + 1);
		johnUsed[i] = 0; johnK.erase(johnK.begin() + johnK.size() - 1);
	}
	res %= 1000000009;
	return res;
}*/

int waysJohn(int index, int count)
{
	if (count == k) return waysPaul(0, 0);
	if (index == n) return 0;

	johnK.push_back(john[index]);
	int takeRes = waysJohn(index + 1, count + 1); // take
	johnK.erase(johnK.begin() + johnK.size() - 1);

	int ignoreRes = waysJohn(index + 1, count); // ignore

	return (takeRes + ignoreRes) % 1000000009;
}

int main()
{
	ifstream in("team.in");
	ofstream out("team.out");

	in >> n >> m >> k;
	for (int i = 0; i < n; i++) in >> john[i];
	for (int i = 0; i < m; i++) in >> paul[i];

	out << waysJohn(0, 0) << endl;
	// ARE THE BOOLS NEEDED?

	return 0;
}

/*

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
using namespace std;

typedef vector<int> vi;

int n, m, k, john[1010], paul[1010];
vi johnK, paulK;

bool check()
{
	sort(johnK.begin(), johnK.end());
	sort(paulK.begin(), paulK.end());
	//for (int i = 0; i < k; i++) cout << johnK[i] << " "; cout << endl;
	//for (int i = 0; i < k; i++) cout << paulK[i] << " "; cout << endl; cout << endl;

	for (int i = 0; i < k; i++)
		if (johnK[i] <= paulK[i])
			return false;
	return true;
}

int waysPaul(int index, int count)
{
	//if (paulMemo[index][count] != -1) return paulMemo[index][count];
	if (count == k) return check();
	if (index == m) return 0;

	paulK.push_back(paul[index]);
	int takeRes = waysPaul(index + 1, count + 1); // take
	paulK.erase(paulK.begin() + paulK.size() - 1);

	int ignoreRes = waysPaul(index + 1, count); // ignore

	return (takeRes + ignoreRes) % 1000000009;
}

int waysJohn(int index, int count)
{
	//if (johnMemo[index][count] != -1) return johnMemo[index][count];
	if (count == k) return waysPaul(0, 0);
	if (index == n) return 0;

	johnK.push_back(john[index]);
	int takeRes = waysJohn(index + 1, count + 1); // take
	johnK.erase(johnK.begin() + johnK.size() - 1);

	int ignoreRes = waysJohn(index + 1, count); // ignore

	return (takeRes + ignoreRes) % 1000000009;
}

int main()
{
	ifstream in("team.in");
	ofstream out("team.out");

	in >> n >> m >> k;
	for (int i = 0; i < n; i++) in >> john[i];
	for (int i = 0; i < m; i++) in >> paul[i];

	out << waysJohn(0, 0) << endl;
	//while (1);

	return 0;
}*/