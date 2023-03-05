#include"Header.h"
#include"resource.h"

void menuClear(HWND hEditers[], const int SIZE_EDIT, int clearValue)
{
	switch (clearValue)
	{
	case CLEAR_ALL:
		for (int i = 0; i < SIZE_EDIT; i++)
			SetWindowText(hEditers[i], _T(""));
		break;
	case CLEAR_BALS:
		for (int i = 2; i < SIZE_EDIT; i += 2)
			SetWindowText(hEditers[i], _T(""));
		break;
	case CLEAR_COEF:
		for (int i = 1; i < SIZE_EDIT; i += 2)
			SetWindowText(hEditers[i], _T(""));
		break;
	default:
		break;
	}
}