#include <iostream>
#include <fstream>
#include <algorithm>
#include <cstring>
using namespace std;

int b, v[30];
bool memo[10010][10010];

int countMin(int rem, int c)
{
	if (rem < 0 || memo[rem][c]) return 2000000000;
	if (!rem) return 0;
	memo[rem][c] = 1;

	int ret = 2000000000;
	for (int i = 0; i < b; i++)
		ret = min(ret, countMin(rem - v[i], c + 1) + 1);
	//memo[rem][c] = 0; // do NOT do this. makes memo too slow!
	return ret;
}

int main()
{
	ifstream in("mooomoo.in");
	ofstream out("mooomoo.out");

	int n, fields[110], newFields[110];
	in >> n >> b;
	for (int i = 0; i < b; i++) in >> v[i];
	for (int i = 0; i < n; i++) in >> fields[i], newFields[i] = fields[i];
	for (int i = 1; i < n; i++) if (fields[i - 1] > 1) newFields[i] -= fields[i - 1] - 1;

	int count = 0;
	for (int i = 0; i < n; i++)
	{
		for (int a = 0; a <= newFields[i]; a++) for (int b = 0; b < 10010; b++) memo[a][b] = 0;
		count += countMin(newFields[i], 0);
	}
	out << count << endl;

	return 0;
}