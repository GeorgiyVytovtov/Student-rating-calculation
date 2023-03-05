#include"Header.h"
#include<algorithm>


int getData(HWND hEditers[], std::vector<double>& scores, std::vector<double>& coef,const int ItemIndex)
{
	scores.clear();
	coef.clear();

	TCHAR bufScore[6], bufCoef[6];
	int countCell = ItemIndex * 2 + 2;

	for (int i = 1; i <= countCell; i++)
	{
		if (i & 1)
		{
			GetWindowText(hEditers[i], bufCoef, 5);
			coef.push_back(_wtof(bufCoef));
		}
		else
		{
			GetWindowText(hEditers[i], bufScore, 5);
			scores.push_back(_wtof(bufScore));
		}
	}

	if (std::find_if(scores.begin(), scores.end(), [](int a) {return a > 100; }) != scores.end() || std::find(scores.begin(), scores.end(), 0) != scores.end())
	{
		MessageBox(GetParent(hEditers[0]), _T("Проверьте правильность ввода. Введите число от 0 до 100"), _T("Ошибка ввода оценки"), MB_ICONERROR);
		return 0;
	}
	else if (std::find_if(coef.begin(), coef.end(), [](int a) {return a > 10; }) != coef.end() || std::find_if(coef.begin(), coef.end(), [](double a) {return a <= 0; }) != coef.end())//-1    std::find(coef.begin(), coef.end(), 0) != coef.end()
	{
		MessageBox(GetParent(hEditers[0]), _T("Проверьте правильность ввода. Введите число от 0 до 10"), _T("Ошибка ввода коэффициента предмета"), MB_ICONERROR);
		return 0;
	}
	else if ((scores.size()-1)== ItemIndex && (coef.size()-1) == ItemIndex)
		return 1;
	else
	{
		MessageBox(GetParent(hEditers[0]), _T("Ошибка считывания"), _T("Ошибка считывания"), NULL);
		return 0;
	}
}