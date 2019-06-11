#include <iostream>
#include <algorithm>
#include <fstream>
using namespace std;

int main()
{
	ifstream in("badmilk.in");
	ofstream out("badmilk.out");

	int N, M, D, S;
	in >> N >> M >> D >> S; // friends, milk types, D-lines in input, sicks
	int friendMilkTime[1000][3] = {};

	for (int i = 0; i < D; i++)
	{
		in >> friendMilkTime[i][0];
		in >> friendMilkTime[i][1];
		in >> friendMilkTime[i][2];
	}

	int patientsTime[60][2] = {};

	for (int i = 0; i < S; i++)
	{
		in >> patientsTime[i][0];
		in >> patientsTime[i][1];
	}

	int possibleBadMilks[60] = {}; // milk 1 will be 1 in array, not 0.

								   // consider sicked time! in sicks!
	for (int i = 0; i < S; i++)
	{
		for (int j = 0; j < D; j++)
		{
			if (friendMilkTime[j][0] == patientsTime[i][0]) // if it is the friend
			{
				if (friendMilkTime[j][2] < patientsTime[i][1]) // if it is behind that sickened time
				{
					possibleBadMilks[friendMilkTime[j][1]] = 1;
					cout << friendMilkTime[j][1];
				}
			}
		}
	}

	// if sick but did not drink it
	for (int i = 0; i < S; i++)
	{
		for (int j = 0; j < M; j++)
		{
			if (possibleBadMilks[j + 1] == 0) continue;

			bool entered = false;

			for (int k = 0; k < D; k++)
			{
				if (friendMilkTime[k][0] == patientsTime[i][0]
					&& friendMilkTime[k][1] == j + 1)
				{
					entered = true;
					break;
				}
			}

			if (!entered)
			{
				possibleBadMilks[j + 1] = 0;
			}
		}
	}

	int count = 0;
	int countedFriends[60] = {}; // milk 1 will be 1 in array, not 0.

	for (int i = 0; i < D; i++)
	{
		for (int j = 0; j < M; j++)
		{
			if (possibleBadMilks[j + 1] == 1) // it is one of possibleBadMilks
			{
				if (friendMilkTime[i][1] == j + 1 && countedFriends[friendMilkTime[i][0]] == 0)
					// he/she drank that milk && not already counted friend
				{
					countedFriends[friendMilkTime[i][0]] = 1;
					count++;
				}
			}
		}
	}

	out << count << endl;

	//cin.get();
	return 0;
}
