#include<string>
#include<array>
#include<Windows.h>
#include <commdlg.h>
#include"Header.h"
#include"resource.h"
#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#define CALCULATE 1
#define IDC_COMBOBOX_TEXT 1000

const int NUMBER_SUBJECTS = 8;
const int QUANTITY_EDITS = NUMBER_SUBJECTS * 2 + 1;
const TCHAR* str_about_marks = _T("Enter your marks\n(100 points):");
const TCHAR* str_about_credits = _T("Enter the amount of credits\nfor the corresponding subject:");
const TCHAR* str_about_select = _T("Select the number of\nsubjects per semester:");

std::array<std::wstring, 5> text = { _T("Number additional points (from 0 to 6)"),_T("0.00"),_T("Average score"),
									_T("0.00"),_T("Rating score") };

HFONT hFontTitle = CreateFont(16, 0, 0, 0, FW_EXTRALIGHT, 0, 0, 0, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, FF_MODERN, _T("Times New Roman"));

static HWND hEditers[QUANTITY_EDITS];

std::vector<int> marks;
std::vector<double> credits;
int additionalPoint;int itemIndex, lastItemIndex;
int positionDynamicEditY = 145;// Start position dynamic edit by y.
int indexDynamicEditCredit = 3;// Start index of dynamically changing credits editors.
int indexDynamicEditMark = 4;// Start index of dynamically changing marks editors.

LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;	RECT rt;
	switch (msg)
	{
	case WM_CREATE: {
		HWND hWndComboBox = CreateWindow(
			WC_COMBOBOX,
			NULL,
			WS_VISIBLE | WS_CHILD | CBS_DROPDOWNLIST,
			250, 20, 40, 200,
			hWnd, reinterpret_cast<HMENU>(IDC_COMBOBOX_TEXT), NULL, NULL);

		for(int i = 0; i < NUMBER_SUBJECTS; i++)
			SendMessage(GetDlgItem(hWnd, IDC_COMBOBOX_TEXT), CB_ADDSTRING, 0, (LPARAM)std::to_wstring(i+1).c_str());

		HWND hCalculate = CreateWindow(
			WC_BUTTON,
			_T("Calculate"),
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			500, 370, 100, 30,
			hWnd, reinterpret_cast<HMENU>(CALCULATE), NULL, NULL);

		createEditLine(hWnd, hEditers[1], hEditers[2], 175, 110, hFontTitle);
		hEditers[0] = CreateWindow(
			WC_EDIT,
			_T("1"),
			WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT| ES_NUMBER,
			380, 235, 40, 20,
			hWnd, NULL, NULL, NULL);

		SendMessage(hCalculate, WM_SETFONT, (WPARAM)hFontTitle, true);
		SendMessage(hEditers[0], WM_SETFONT, (WPARAM)hFontTitle, true);
		SendMessage(hWndComboBox, WM_SETFONT, (WPARAM)hFontTitle, true);
		SendMessage(hEditers[0], EM_SETLIMITTEXT, 1, 0);
		SendMessage(hWndComboBox, CB_SETCURSEL, 0, 0);
		break;
	}
	case WM_COMMAND: {
		switch (LOWORD(wParam))
		{
			case IDC_COMBOBOX_TEXT:
			{
				switch (HIWORD(wParam))
				{
					case CBN_SELCHANGE:
					{
						itemIndex = SendMessage((HWND)lParam, (UINT)CB_GETCURSEL, (WPARAM)0, (LPARAM)0);
						if (lastItemIndex < itemIndex)
						{
							createEditLines(hWnd, hEditers, positionDynamicEditY, indexDynamicEditMark, indexDynamicEditCredit, lastItemIndex, itemIndex, hFontTitle);
						}
						else
						{
							deleteEditLines(hEditers, lastItemIndex, itemIndex, positionDynamicEditY, indexDynamicEditMark, indexDynamicEditCredit);
						}
						lastItemIndex = itemIndex;
					}
					break;
					default:
						break;
				}
			}
			break;

			case CALCULATE: {
				TCHAR buffAdditionalPoint[6];

				GetWindowText(hEditers[0], buffAdditionalPoint, 5);
				additionalPoint = _wtoi(buffAdditionalPoint);
				if (additionalPoint < 0 || additionalPoint>6)
				{
					MessageBox(hWnd, _T("Enter a value between 0 and 6"), _T("Incorrect entered data"), MB_ICONERROR);
					break;
				}

				if (getData(hEditers, marks, credits, itemIndex))
				{
					text[1] = std::to_wstring(averageScore(marks));
					text[3] = std::to_wstring(ratingScore(marks, credits, additionalPoint));
				}
				else
					break;
				InvalidateRect(hWnd, NULL, 1);
			}
			break;

			case CLEAR_ALL:
				for (int i = 0; i < QUANTITY_EDITS; i++)
					SetWindowText(hEditers[i], _T(""));
				break;
			case CLEAR_BALS:
				for (int i = 2; i < QUANTITY_EDITS; i += 2)
					SetWindowText(hEditers[i], _T(""));
				break;
			case CLEAR_COEF:
				for (int i = 1; i < QUANTITY_EDITS; i += 2)
					SetWindowText(hEditers[i], _T(""));
				break;
			case ID_ABOUTPROGRAM:
				MessageBox(GetParent(hEditers[1]), _T("This program is designed to calculate the student's average and ranking score for the semester."), _T("About program"), MB_ICONINFORMATION);
				break;
			case IDO_EXIT:
				DestroyWindow(hWnd);
				break;
			default:
				break;
		}
		break;
	}
	case WM_PAINT:
	{
		int j = 0;
		hdc = BeginPaint(hWnd, &ps);
		SelectObject(hdc, hFontTitle);
		SetBkColor(hdc, RGB(220, 220, 220));
		for (int y = 210; y > 85; y -= 25)// Output cycle of informational text and text of calculation results.
		{
			TextOut(hdc, 380, y, text[j].c_str(), text[j].length());
			j++;
		}
		SetBkMode(hdc, TRANSPARENT);

		//Constant text output
		SetRect(&rt,60, 70, 160, 110);
		DrawText(hdc, str_about_marks, _tcslen(str_about_marks), &rt, DT_LEFT);
		SetRect(&rt, 175, 70, 355, 110);
		DrawText(hdc, str_about_credits, _tcslen(str_about_credits), &rt, DT_LEFT);
		SetRect(&rt, 110, 15, 300, 110);
		DrawText(hdc, str_about_select, _tcslen(str_about_select), &rt, DT_LEFT);
		EndPaint(hWnd, &ps);
	}
	break;

	case WM_DESTROY: {
		PostQuitMessage(0);
		break;
	}
	default:
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}

}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	HWND hWnd;
	MSG msg;
	WNDCLASSEX wc;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCEW(IDI_ICON1));
	wc.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCEW(IDI_ICON1));
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.hInstance = hInstance;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.lpfnWndProc = WndProc;
	wc.lpszMenuName = MAKEINTRESOURCEW(IDR_MENU1);
	wc.lpszClassName = _T("WinMainClass");

	RegisterClassEx(&wc);
	hWnd = CreateWindow(
		wc.lpszClassName,
		_T("Student rating calculation"),
		WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX,
		(GetSystemMetrics(SM_CXSCREEN) - 640) / 2,
		(GetSystemMetrics(SM_CYSCREEN) - 480) / 2,
		640, 480,
		NULL, NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}