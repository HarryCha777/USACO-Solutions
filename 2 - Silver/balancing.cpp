#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
using namespace std;

typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<int> vi;

int main()
{
	ifstream in("balancing.in");
	ofstream out("balancing.out");

	int n; in >> n;
	vii pos(n, ii());
	for (int i = 0; i < n; i++) in >> pos[i].first >> pos[i].second;
	vi x(n, 0), y(n, 0);
	for (int i = 0; i < n; i++) x[i] = pos[i].first, y[i] = pos[i].second;
	sort(x.begin(), x.end());
	sort(y.begin(), y.end());

	int ans = 2000000000, prevXLine = -1, prevYLine = -1;
	for (int i = 0; i < n - 1; i++) // I do not count leftmost line or rightmost line.
	{
		int lineX = x[i] + 1;
		if (lineX == prevXLine) continue;
		prevXLine = lineX;

		for (int j = 0; j < n - 1; j++) // I do not count top line or bottom line.
		{
			int lineY = y[j] + 1;
			if (lineY == prevYLine) continue;
			prevYLine = lineY;

			int NW, NE, SW, SE; NW = NE = SW = SE = 0;
			for (int k = 0; k < n; k++)
			{
				if (lineX > pos[k].first && lineY < pos[k].second) NW++;
				if (lineX < pos[k].first && lineY < pos[k].second) NE++;
				if (lineX > pos[k].first && lineY > pos[k].second) SW++;
				if (lineX < pos[k].first && lineY > pos[k].second) SE++;
			}

			//int currAns = max(NW, max(NE, max(SW, SE))); // this takes EXTREMELY long!
			// NEVER use these max stuff all at a time!

			// below code is MUCH faster!!!
			int currMax1 = max(NW, NE);
			int currMax2 = max(SW, SE);
			int totalMax = max(currMax1, currMax2);
			ans = min(ans, totalMax);
		}
	}
	out << ans << endl;

	return 0;
}









































































































































/*

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
using namespace std;

typedef pair<int, int> ii;
typedef vector<ii> vii;

int main() // this method does not work...finding xLine first(or maybe code is wrong) (code below is too slow though)
{
	ifstream in("balancing.in");
	ofstream out("balancing.out");

	int n; in >> n;
	vii pos(0);
	for (int i = 0; i < n; i++)
	{
		int x, y; in >> x >> y;
		pos.push_back(ii(x, y));
	}
	sort(pos.begin(), pos.end());

	int xLine, minXDiff = 1000000000; // finding xLine
	for (int i = 0; i < n; i++)
	{
		int currXLine = pos[i].first + 1; // + 1 for clear boundary...no cows are on it
		int left = 0, right = 0;
		for (int j = 0; j < n; j++)
		{
			if (pos[j].first < currXLine)	left++;
			else							right++;
		}
		if (abs(left - right) < minXDiff)
		{
			minXDiff = abs(left - right);
			xLine = pos[i].first + 1;
		}
	}

	int ans = 1000000000;
	for (int i = 0; i < n; i++)
	{
		int yLine = pos[i].second + 1;
		int q1 = 0, q2 = 0, q3 = 0, q4 = 0; // 4 quadrants count
		for (int j = 0; j < n; j++)
		{
			int x = pos[j].first, y = pos[j].second; // remember: j not i
			if (x > xLine && y > yLine) q1++;
			if (x < xLine && y > yLine) q2++;
			if (x < xLine && y < yLine) q3++;
			if (x > xLine && y < yLine) q4++;
		}
		//printf("%d %d %d %d\n", q1, q2, q3, q4);
		int max1 = max(q1, q2), max2 = max(q3, q4), theMax = max(max1, max2);
		ans = min(ans, theMax);
	}

	out << ans << endl;

	return 0;
}*/
























































/*

#include <iostream>
#include <fstream>
#include <algorithm>
#include <cstring>
#include <string>
using namespace std;

int main()
{
	ifstream in("balancing.in");
	ofstream out("balancing.out");

	int n, posXY[1010][2], X[1010], Y[1010];
	in >> n;

	for (int i = 0; i < n; i++)
	{
		in >> posXY[i][0] >> posXY[i][1];
		X[i] = posXY[i][0];
		Y[i] = posXY[i][1];
	}

	sort(X, X + n);
	sort(Y, Y + n);

	// the below code doese not work.
	// find best horizontal line first
	//int minDiff = 2100000000;
	//int prevX = X[0], bestXLine;
	//for (int i = 0; i < n; i++)
	//{
	//	int xLine = X[i] + 1; // + 1 for even line (all inputs are odd)

	//	if (i && X[i] == prevX) continue;
	//	prevX = X[i];

	//	int curr1 = 0, curr2 = 0;
	//	for (int j = 0; j < n; j++)
	//	{
	//		if (posXY[j][0] > xLine) curr1++;
	//		else curr2++;
	//	}

	//	if (abs(curr1 - curr2) < minDiff)
	//	{
	//		minDiff = abs(curr1 - curr2);
	//		bestXLine = xLine;
	//	}
	//}

	//// then vertical line
	//int ans = 2100000000;
	//int prevY = Y[0];
	//for (int i = 0; i < n; i++)
	//{
	//	if (i && Y[i] == prevY) continue;
	//	prevY = Y[i];

	//	int yLine = Y[i] + 1;

	//	int curr1 = 0, curr2 = 0, curr3 = 0, curr4 = 0;
	//	for (int j = 0; j < n; j++)
	//	{
	//		if (posXY[j][0] > bestXLine)
	//		{
	//			if (posXY[j][1] > yLine) curr1++;
	//			else curr2++;
	//		}
	//		else
	//		{
	//			if (posXY[j][1] > yLine) curr3++;
	//			else curr4++;
	//		}
	//	}

	//	// below is just finding the max and saving it
	//	int currMax1, currMax2, totalMax = 0;
	//	if (curr1 > curr2) currMax1 = curr1;
	//	else currMax1 = curr2;
	//	if (curr3 > curr4) currMax2 = curr3;
	//	else currMax2 = curr4;
	//	if (currMax1 > currMax2) totalMax = currMax1;
	//	else totalMax = currMax2;
	//	if (totalMax < ans) ans = totalMax;
	//}

	// below is 3-loop approach works but is too slow (O(n^3))
	int ans = 2100000000;
	int prevX = X[0], prevY = Y[0];
	for (int i = 0; i < n; i++)
	{
		if (i && X[i] == prevX) continue;
		prevX = X[i];

		for (int j = 0; j < n; j++)
		{
			if (j && Y[j] == prevY) continue;
			prevY = Y[j];

			int xLine = X[i] + 1; // + 1 for even line (all inputs are odd)
			int yLine = Y[j] + 1;

			int curr1 = 0, curr2 = 0, curr3 = 0, curr4 = 0;
			for (int k = 0; k < n; k++)
			{
				if (posXY[k][0] > xLine)
				{
					if (posXY[k][1] > yLine) curr1++;
					else curr2++;
				}
				else
				{
					if (posXY[k][1] > yLine) curr3++;
					else curr4++;
				}
			}

			// below is just finding the max and saving it
			int currMax1, currMax2, totalMax = 0;
			if (curr1 > curr2) currMax1 = curr1;
			else currMax1 = curr2;
			if (curr3 > curr4) currMax2 = curr3;
			else currMax2 = curr4;
			if (currMax1 > currMax2) totalMax = currMax1;
			else totalMax = currMax2;
			if (totalMax < ans) ans = totalMax;
		}
	}

	out << ans << "\n";
	//cin.get();
	// arr index and LL

	return 0;
}*/