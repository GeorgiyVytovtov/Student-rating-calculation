#include"Header.h"

const int HEIGHT = 20;
const int WIDTH = 40;
const int DISTANCE_BETWEEN_EDIT = 65;

void creater(HWND& hWnd, HWND& hEditFirst, HWND& hEditSecond, int x, int y, HFONT hFontTitle)
{
	hEditFirst = CreateWindow(
		WC_EDIT,
		NULL,
		WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT,
		x, y, WIDTH, HEIGHT,
		hWnd, NULL, NULL, NULL);
	hEditSecond = CreateWindow(
		WC_EDIT,
		NULL,
		WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT| ES_NUMBER,
		x - DISTANCE_BETWEEN_EDIT, y, WIDTH, HEIGHT,
		hWnd, NULL, NULL, NULL);
	SendMessage(hEditFirst, EM_SETLIMITTEXT, 3, 0);
	SendMessage(hEditSecond, EM_SETLIMITTEXT, 3, 0);
	SendMessage(hEditFirst, WM_SETFONT, (WPARAM)hFontTitle, true);
	SendMessage(hEditSecond, WM_SETFONT, (WPARAM)hFontTitle, true);
}