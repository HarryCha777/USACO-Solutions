#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

int main()
{
	ifstream in("bcount.in");
	ofstream out("bcount.out");

	int n, q; in >> n >> q;
	int prefix1[1000010] = {}, prefix2[1000010] = {}, prefix3[1000010] = {};
	int firstInput; in >> firstInput;
	if (firstInput == 1) prefix1[1]++;			// remember that it starts from [1]!
	else if (firstInput == 2) prefix2[1]++;
	else prefix3[1]++;
	for (int i = 2; i <= n; i++)
	{
		prefix1[i] = prefix1[i - 1];
		prefix2[i] = prefix2[i - 1];
		prefix3[i] = prefix3[i - 1];

		int input; in >> input;
		if (input == 1) prefix1[i]++;
		else if (input == 2) prefix2[i]++;
		else prefix3[i]++;
	}
	//for (int i = 1; i <= n; i++) printf("%d %d %d\n", prefix1[i], prefix2[i], prefix3[i]); cin.get();

	for (int i = 0; i < q; i++)
	{
		int start, end; in >> start >> end; start--; // don't forget to start--
		int total1s = prefix1[end] - prefix1[start];
		int total2s = prefix2[end] - prefix2[start];
		int total3s = prefix3[end] - prefix3[start];
		out << total1s << " " << total2s << " " << total3s << endl;
	}

	return 0;
}