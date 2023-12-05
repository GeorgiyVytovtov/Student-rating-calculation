#include"Header.h"

void deleteEditLines(HWND hEditers[], const int lastItemIndex, const int itemIndex, int& startYPosition, int& indexDynamicEditScores, int& indexDynamicEditCoef)
{
	int startNumbDelet = lastItemIndex * 2 + 2;
	int amountDelet = 2 * (lastItemIndex - itemIndex);

	while (amountDelet)
	{
		DestroyWindow(hEditers[startNumbDelet--]);
		amountDelet--;
	}
	startYPosition -= 35 * (lastItemIndex - itemIndex);
	indexDynamicEditCoef -= 2 * (lastItemIndex - itemIndex);
	indexDynamicEditScores -= 2 * (lastItemIndex - itemIndex);
}
