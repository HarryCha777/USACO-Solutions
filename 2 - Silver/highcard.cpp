#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

int main()
{
	ifstream in("highcard.in");
	ofstream out("highcard.out");

	int N;
	in >> N;

	int elsie[50000];

	for (int i = 0; i < N; i++)
	{
		in >> elsie[i];
		elsie[i] = elsie[i];
	}

	sort(elsie, elsie + N);

	int indexE = 0;
	int indexB = 0;
	int bessie[50000];

	for (int i = 1; i <= N * 2; i++)
	{
		if (elsie[indexE] == i)
		{
			indexE++;
		}
		else
		{
			bessie[indexB++] = i;
		}
	}

	// bessie is already sorted through above loop.

	int win = 0;
	int startPos = 0;

	for (int i = 0; i < N; i++)
	{
		for (int j = startPos; j < N; j++)
		{
			if (bessie[j] > elsie[i])
			{
				bessie[j] = 0;
				startPos = j;
				win++;
				break;
			}
		}
	}

	out << win << endl;
	//cin.get();

	return 0;
}

