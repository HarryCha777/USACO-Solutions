#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

int main()
{
	ifstream in("bphoto.in");
	ofstream out("bphoto.out");

	int n, arr[100010]; in >> n;
	for (int i = 0; i < n; i++) in >> arr[i];

	int count = 0;
	for (int i = 0; i < n; i++)
	{
		int Li = 0; for (int j = 0; j < i; j++) if (arr[i] < arr[j]) Li++;
		int Ri = 0; for (int j = i + 1; j < n; j++) if (arr[i] < arr[j]) Ri++;
		if (max(Li, Ri) > min(Li, Ri) * 2) count++;
	}
	out << count << endl;

	return 0;
}