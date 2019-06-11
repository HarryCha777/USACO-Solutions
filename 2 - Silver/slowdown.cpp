#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

int main()
{
	ifstream in("slowdown.in");
	ofstream out("slowdown.out");

	int n, type[10010], value[10010]; in >> n;
	for (int i = 0; i < n; i++)
	{
		char ch; int num; in >> ch >> num;
		type[i] = ch; value[i] = num;
	}

	double time = 0, dist = 0, speed = 1;
	int dem = 1;
	while (dist < 1000)
	{
		//cout << dist << endl;
		for (int i = 0; i < n; i++)
		{
			if (type[i] == 'T' && time >= value[i])
			{
				speed = 1.0 / (++dem);
				value[i] = 10000;
			}
			else if (type[i] == 'D' && dist >= value[i])
			{
				speed = 1.0 / (++dem);
				value[i] = 10000;
			}
		}

		dist += speed;
		time++;
	}
	
	if (time - (int)time >= 0.5)
		cout << (int)time + 1 << endl;
	else
		cout << (int)time << endl;
	while (1);

	return 0;
}


























/*

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
using namespace std;

int main()
{
	ifstream in("slowdown.in");
	ofstream out("slowdown.out");

	int N;
	in >> N;
	int dists[10000], times[10000];
	int indexD = 0, indexT = 0;

	for (int i = 0; i < N; i++)
	{
		char ch;
		in >> ch;

		if (ch == 'D') in >> dists[indexD++];
		else in >> times[indexT++];
	}

	sort(dists, dists+indexD);
	sort(times, times+indexT);

	//for (int i = 0; i < indexD; i++) cout << dists[i] << " "; cout << endl;
	//for (int i = 0; i < indexT; i++) cout << times[i] << " "; cout << endl;

	double time = 0;
	double dist = 0;
	double travel = 1;
	int denom = 2;

	bool checkDEnd = false, checkTEnd = false;
	int checkD = 0, checkT = 0;

	while (dist < 1000)
	{
		while (!checkDEnd) // just in case any consecutive slow-downs
		{
			if (checkD == indexD)
			{
				//cout << 3;

				checkDEnd = true;
				break;
			}

			if (dists[checkD] <= dist) // also should calculate next move (between)
			{
				//cout << 1;

				travel = 1.0 / (denom++);
				checkD++;
			}
			else
			{
				break;
			}
		}

		while (!checkTEnd) // just in case any consecutive slow-downs
		{
			if (checkT == indexT)
			{
				//cout << 4;

				checkTEnd = true;
				break;
			}

			if (times[checkT] <= time) // also should calculate next move (between)
			{
				//cout << 2;

				travel = 1.0 / (denom++);
				checkT++;
			}
			else
			{
				break;
			}
		}

		dist += travel;
		time++;

		//if (dist > 950)
			//cout << dist << " " << time << endl;
	}
	
	if (time - (int)time >= 0.5)
		out << (int)time + 1 << endl;
	else
		out << (int)time << endl;
	//cin.get();

	return 0;
}*/