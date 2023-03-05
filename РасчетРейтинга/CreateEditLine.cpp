#include"Header.h"

void createEditLine(HWND& hWnd, HWND hEditers[], int& startPositionY, int& indexDynamicEditScores, int& indexDynamicEditCoef, const int lastItemIndex, const int ItemIndex, HFONT hFontTitle)
{
	for (int i = lastItemIndex; i < ItemIndex; i++)
	{
		creater(hWnd, hEditers[indexDynamicEditCoef], hEditers[indexDynamicEditScores], 175, startPositionY, hFontTitle);
		startPositionY += 35;
		indexDynamicEditCoef += 2;
		indexDynamicEditScores += 2;
	}
}