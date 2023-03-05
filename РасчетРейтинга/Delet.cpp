#include"Header.h"

void deleteEdit(HWND hEditers[], const int lastItemIndex, const int ItemIndex, int& startYPosition, int& indexDynamicEditScores, int& indexDynamicEditCoef)
{
	int startNumbDelet = lastItemIndex * 2 + 2;
	int amountDelet = 2 * (lastItemIndex - ItemIndex);

	while (amountDelet)
	{
		DestroyWindow(hEditers[startNumbDelet--]);
		amountDelet--;
	}
	startYPosition -= 35 * (lastItemIndex - ItemIndex);
	indexDynamicEditCoef -= 2 * (lastItemIndex - ItemIndex);
	indexDynamicEditScores -= 2 * (lastItemIndex - ItemIndex);
}
