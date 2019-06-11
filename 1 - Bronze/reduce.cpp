#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

int main()
{
	ifstream in("reduce.in");
	ofstream out("reduce.out");

	int n; in >> n;
	int pos[50010][2], left = 2000000000, right = 0, down = 2000000000, up = 0,
		leftI, rightI, downI, upI;

	for (int i = 0; i < n; i++)
	{
		in >> pos[i][0] >> pos[i][1];
		if (pos[i][0] < left) left = pos[i][0], leftI = i;
		if (pos[i][0] > right) right = pos[i][0], rightI = i;
		if (pos[i][1] < down) down = pos[i][1], downI = i;
		if (pos[i][1] > up) up = pos[i][1], upI = i;
	}

	int minArea = 2000000000;

	int left2 = 2000000000, right2 = 0, down2 = 2000000000, up2 = 0;
	for (int i = 0; i < n; i++) if (i != leftI)
		left2 = min(left2, pos[i][0]), right2 = max(right2, pos[i][0]),
		down2 = min(down2, pos[i][1]), up2 = max(up2, pos[i][1]);
	minArea = min(minArea, (right2 - left2)*(up2 - down2));

	left2 = 2000000000, right2 = 0, down2 = 2000000000, up2 = 0;
	for (int i = 0; i < n; i++) if (i != rightI)
		left2 = min(left2, pos[i][0]), right2 = max(right2, pos[i][0]),
		down2 = min(down2, pos[i][1]), up2 = max(up2, pos[i][1]);
	minArea = min(minArea, (right2 - left2)*(up2 - down2));

	left2 = 2000000000, right2 = 0, down2 = 2000000000, up2 = 0;
	for (int i = 0; i < n; i++) if (i != downI)
		left2 = min(left2, pos[i][0]), right2 = max(right2, pos[i][0]),
		down2 = min(down2, pos[i][1]), up2 = max(up2, pos[i][1]);
	minArea = min(minArea, (right2 - left2)*(up2 - down2));

	left2 = 2000000000, right2 = 0, down2 = 2000000000, up2 = 0;
	for (int i = 0; i < n; i++) if (i != upI)
		left2 = min(left2, pos[i][0]), right2 = max(right2, pos[i][0]),
		down2 = min(down2, pos[i][1]), up2 = max(up2, pos[i][1]);
	minArea = min(minArea, (right2 - left2)*(up2 - down2));
	out << minArea << endl;

	// this is wrong since there can be a cow that is at left-est AND ALSO at the up-est side.
	/*int minArea = 2000000000;
	int secondLeft = 2000000000;
	for (int i = 0; i < n; i++) if (pos[i][0] != left) secondLeft = min(secondLeft, pos[i][0]);
	minArea = min(minArea, (right - secondLeft)*(up - down));
	int secondRight = 2000000000;
	for (int i = 0; i < n; i++) if (pos[i][0] != right) secondRight = max(secondRight, pos[i][0]);
	minArea = min(minArea, (secondRight - left)*(up - down));
	int secondDown = 2000000000;
	for (int i = 0; i < n; i++) if (pos[i][1] != down) secondDown = min(secondLeft, pos[i][1]);
	minArea = min(minArea, (right - left)*(up - secondDown));
	int secondUp = 2000000000;
	for (int i = 0; i < n; i++) if (pos[i][1] != up) secondUp = max(secondRight, pos[i][1]);
	minArea = min(minArea, (right - left)*(secondUp - down));
	out << minArea << endl;*/

	return 0;
}








// this is also correct (similar speed as code above.)
/*

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
using namespace std;

int main()
{
	ifstream in("reduce.in");
	ofstream out("reduce.out");

	int n, x[50010] = {}, y[50010] = {}; in >> n;
	for (int i = 0; i < n; i++) in >> x[i] >> y[i];
	// notice that removing a cow that doesn't have minX, maxX, minY, or maxY is meaningless since we're removing only one cow.
	// cows that have minX, maxX, minY, or maxY (or 2 of them) are in array "marked"

	int maxX = 0, maxY = 0, minX = 2000000000, minY = 2000000000, marked[50010] = {}, index = 0;
	for (int i = 0; i < n; i++) maxX = max(maxX, x[i]), maxY = max(maxY, y[i]), minX = min(minX, x[i]), minY = min(minY, y[i]);
	for (int i = 0; i < n; i++) if (x[i] == maxX || y[i] == maxY || x[i] == minX || y[i] == minY) marked[index++] = i;
	
	int minArea = 2000000000;
	for (int j = 0; j < index; j++)
	{
		maxX = 0, maxY = 0, minX = 2000000000, minY = 2000000000;
		for (int i = 0; i < n; i++) if (i != marked[j])
			maxX = max(maxX, x[i]), maxY = max(maxY, y[i]), minX = min(minX, x[i]), minY = min(minY, y[i]);
		minArea = min(minArea, (maxX - minX)*(maxY - minY));
	}
	out << minArea << endl;

	return 0;
}*/