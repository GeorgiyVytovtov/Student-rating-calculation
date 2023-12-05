#include"Header.h"
#include<algorithm>


int getData(HWND hEditers[], std::vector<int>& marks, std::vector<double>& credits,const int itemIndex)
{
	marks.clear();
	credits.clear();

	TCHAR bufScore[6], bufCoef[6];
	int countCell = itemIndex * 2 + 2;

	for (int i = 1; i <= countCell; i++)
	{
		if (i & 1)
		{
			GetWindowText(hEditers[i], bufCoef, 5);
			credits.push_back(_wtof(bufCoef));
		}
		else
		{
			GetWindowText(hEditers[i], bufScore, 5);
			marks.push_back(_wtoi(bufScore));
		}
	}

	if (std::find_if(marks.begin(), marks.end(), [](int a) {return a > 100; }) != marks.end() || std::find(marks.begin(), marks.end(), 0) != marks.end())
	{
		MessageBox(GetParent(hEditers[0]), _T("Please check if your entry is correct. Enter a number from 0 to 100"), _T("Error entering mark"), MB_ICONERROR);
		return 0;
	}
	else if (std::find_if(credits.begin(), credits.end(), [](int a) {return a > 10; }) != credits.end() || std::find_if(credits.begin(), credits.end(), [](double a) {return a <= 0; }) != credits.end())
	{
		MessageBox(GetParent(hEditers[0]), _T("Please check if your entry is correct. Enter a number from 0 to 10"), _T("Error entering subject credit"), MB_ICONERROR);
		return 0;
	}
	else if ((marks.size()-1)== itemIndex && (credits.size()-1) == itemIndex)
		return 1;
	else
	{
		MessageBox(GetParent(hEditers[0]), _T("Reading error"), _T("Reading error"), NULL);
		return 0;
	}
}