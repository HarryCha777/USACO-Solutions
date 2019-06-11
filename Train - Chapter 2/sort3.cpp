/*
ID: harrych2
PROG: sort3
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

void swap(int arr[], int indexA, int indexB)
{
	int temp = arr[indexA];
	arr[indexA] = arr[indexB];
	arr[indexB] = temp;
}

bool checkArrays(int arr1[], int arr2[], int n)
{
	for (int i = 0; i < n; i++)
		if (arr1[i] != arr2[i])
			return false;
	return true;
}

int main()
{
	ifstream in("sort3.in");
	ofstream out("sort3.out");
	
	int n, arr1[1010], arr2[1010]; in >> n;
	for (int i = 0; i < n; i++)
	{
		in >> arr1[i];
		arr2[i] = arr1[i];
	}
	sort(arr2, arr2 + n);

	int minSwaps = 0;

	while (true)
	{
		// checking for double matches in the beginning
		while (true)
		{
			int index1 = -1, index2 = -1;

			for (int i = 0; i < n; i++)
			{
				for (int j = 0; j < n; j++)
				{
					if (i != j && arr1[i] != arr1[j] && arr2[i] != arr2[j]
						&& arr1[i] == arr2[j] && arr1[j] == arr2[i])
					{
						index1 = i;
						index2 = j;
						break;
					}
				}

				if (index1 != -1) break;
			}

			//printf("%d %d\n", index1, index2);

			if (index1 == -1) break;
			else
			{
				minSwaps++;
				swap(arr1, index1, index2);
			}
		}

		if (checkArrays(arr1, arr2, n)) break;

		// when no more double matches remains
		while (true)
		{
			int index1 = -1, index2 = -1;

			// checking if they have double matches
			for (int i = 0; i < n; i++)
			{
				for (int j = 0; j < n; j++)
				{
					if (i != j && arr1[i] != arr1[j] && arr2[i] != arr2[j])
					{
						if (arr1[i] == arr2[j] && arr1[j] == arr2[i]) // if double match is found, it's the end
						{
							swap(arr1, i, j);
							minSwaps++;
							index1 = -10;
							//printf("%d %d\n", i, j);

							break;
						}
						else if ((arr1[i] == arr2[j] && arr1[j] != arr2[i])
							|| (arr1[i] != arr2[j] && arr1[j] == arr2[i]))
						{
							index1 = i;
							index2 = j;
							break;
						}
					}
				}

				if (index1 != -1 || index1 == -10) break;
			}

			//printf("%d %d\n", index1, index2);

			if (index1 == -10) break;
			else
			{
				swap(arr1, index1, index2);
				minSwaps++;
			}
		}

		if (checkArrays(arr1, arr2, n)) break;
	}

	//printf("%d\n", minSwaps);
	out << minSwaps << endl;

	//for (int i = 0; i < n; i++) printf("%d ", arr1[i]); printf("\n");
	//for (int i = 0; i < n; i++) printf("%d ", arr2[i]); printf("\n");
	//while (1);

	return 0;
}