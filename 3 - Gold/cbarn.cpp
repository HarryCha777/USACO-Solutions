#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
using namespace std;

int main()
{
	ifstream in("cbarn.in");
	ofstream out("cbarn.out");

	int n, c = 0; in >> n; vector<int> input(n);
	for (int i = 0; i < n; i++) // this is not just like max sum of 1D array
	{
		in >> input[i];
		c += input[i] - 1;
		if (c < 0) c = 0;
	}
	for (int i = 0; ; i++)
	{
		if (c == 0)
		{
			rotate(input.begin(), input.begin() + i, input.begin() + n);
			break;
		}
		c += input[i] - 1;
		if (c < 0) c = 0;
	}
	//for (int i = 0; i < input.size(); i++) cout << input[i] << " "; cout << endl; cin.get();

	long long ans = 0;
	for (int i = n - 1; i >= 0; i--)
	{
		while (input[i])
		{
			int j = i + 1;
			while (true)
			{
				if (j == n || input[j]) break;
				j++;
			}
			j--;
			if (input[j]) break; // this is to prevent test cases like this: with n = 5, 1 2 0 2 0. See what happens.
			input[j] = 1;
			input[i]--;
			ans += (j - i) * (j - i);

			//cout << ans << "   "; for (int a = 0; a < input.size(); a++) cout << input[a] << " "; cout << endl;
			bool done = true; for (int k = 0; k <= i; k++) if (input[k] != 1) { done = false; break; }
			if (done) { out << ans << endl; return 0; }
		}
	}
	out << ans << endl;
	return 0;
}

/*

#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

int main() // incomplete
{
	ifstream in("cbarn.in");
	ofstream out("cbarn.out");

	int N;
	in >> N;
	int cows[200000];
	
	for (int i = 0; i < N; i++)
	{
		in >> cows[i];
		cows[i + N] = cows[i];
	}

	int emptySpace = 0;
	int maxEmpty = 0;
	int index = -1;
	int indexNum = 1000000000;

	// nested for loops will result in TLE.
	// need improvement (single loop(or loops) solutions)

	// do this in input-reading; finding one that has most space with least nums.
	for (int i = 0; i < N; i++)
	{
		if (cows[i] == 0) continue;

		emptySpace = 0;

		for (int j = 1; ; j++)
		{
			if (cows[i + j] == 0)
			{
				emptySpace++;
			}
			else
			{
				if (emptySpace >= maxEmpty
					&& cows[i] < indexNum)
				{
					maxEmpty = emptySpace;
					indexNum = cows[i];
					index = i;
				}

				break;
			}
		}
	}

	printf("Index: %d, IndexNum: %d\n", index, indexNum);

	for (int i = 0; i < N; i++) printf("%d ", cows[i]); printf("\n");
	for (int i = N; i < N * 2; i++) printf("%d ", cows[i]); printf("\n"); printf("\n");

	long energy = 0;

	for (int i = index + N; i > index; i--)
	{
		if (cows[i] == 0) continue;

		emptySpace = 0;

		for (int j = 1; ; j++)
		{
			if (cows[i + j] == 0)
			{
				emptySpace++;
			}
			else
			{
				break;
			}
		}

		if (emptySpace == 0) continue;

		printf("ES: %d, i: %d.\n", emptySpace, i);

		for (int j = emptySpace; ; j--)
		{
			if (cows[i] > 0)
			{
				i++;
				cows[i + j] ++; // other side also!
				if (i + j >= N-1) { cows[i + j - N]++; }
				else { cows[i + j + N]++; }
				i--;

				cows[i] --; // other side also!
				if (i >= N-1) { cows[i - N]--; }
				else { cows[i + N]--; }

				energy += j*j;
			}
			else
			{
				break;
			}
		}

		for (int i = 0; i < N; i++) printf("%d ", cows[i]); printf("\n");
		for (int i = N; i < N * 2; i++) printf("%d ", cows[i]); printf("\n"); printf("\n");
	}
	
	cout << energy << endl;
	cin.get();

	return 0;
}*/