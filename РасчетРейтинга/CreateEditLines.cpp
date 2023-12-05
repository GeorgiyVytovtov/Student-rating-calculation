#include"Header.h"

void createEditLines(HWND& hWnd, HWND hEditers[], int& startPositionY, int& indexDynamicEditScores, int& indexDynamicEditCoef, const int lastItemIndex, const int itemIndex, HFONT hFontTitle)
{
	for (int i = lastItemIndex; i < itemIndex; i++)
	{
		createEditLine(hWnd, hEditers[indexDynamicEditCoef], hEditers[indexDynamicEditScores], 175, startPositionY, hFontTitle);
		startPositionY += 35;
		indexDynamicEditCoef += 2;
		indexDynamicEditScores += 2;
	}
}