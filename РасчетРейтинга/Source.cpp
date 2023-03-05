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



const int SIZE_EDIT = 17;

HFONT hFontTitle = CreateFont(16, 0, 0, 0, FW_EXTRALIGHT, 0, 0, 0, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, FF_MODERN, _T("Times New Roman"));

std::array<std::wstring, 7> text = { _T("Кол.доп баллов (от 0 до 6)"),_T("0.00"),_T("Средний балл"),
									_T("0.00"),_T("Рейтинговий бал"),_T("Введете оценку\n(100 бальную):"),
									_T("Введете объем кредитов\nсоответствующего предмета:") };



LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static HWND hEditers[SIZE_EDIT];
	static HWND hWndComboBox;

	HDC hdc;
	PAINTSTRUCT ps;	RECT rt;	static std::vector<double> scores;
	static std::vector<double> coefficients;
	static double dopScores;	static int ItemIndex, lastItemIndex;
	static int positionDynamicEditY = 145;// Start position dynamic edit by y.
	static int indexDynamicEditCoef = 3;// Start index of dynamically changing coefficient editors.
	static int indexDynamicEditScores = 4;// Start index of dynamically changing scores editors.
	switch (msg)
	{
	case WM_CREATE: {
		hWndComboBox = CreateWindow(
			WC_COMBOBOX,
			NULL,
			WS_VISIBLE | WS_CHILD | CBS_DROPDOWNLIST,
			10, 10, 100, 800,
			hWnd,
			(HMENU)IDC_COMBOBOX_TEXT,
			NULL,
			NULL);

		if (!hWndComboBox)
			MessageBox(NULL, _T("ComboBox Failed."), _T("Error"), MB_OK | MB_ICONERROR);

		SendMessage(GetDlgItem(hWnd, IDC_COMBOBOX_TEXT), CB_ADDSTRING, 0, (LPARAM)_T("1"));
		SendMessage(GetDlgItem(hWnd, IDC_COMBOBOX_TEXT), CB_ADDSTRING, 0, (LPARAM)_T("2"));
		SendMessage(GetDlgItem(hWnd, IDC_COMBOBOX_TEXT), CB_ADDSTRING, 0, (LPARAM)_T("3"));
		SendMessage(GetDlgItem(hWnd, IDC_COMBOBOX_TEXT), CB_ADDSTRING, 0, (LPARAM)_T("4"));
		SendMessage(GetDlgItem(hWnd, IDC_COMBOBOX_TEXT), CB_ADDSTRING, 0, (LPARAM)_T("5"));
		SendMessage(GetDlgItem(hWnd, IDC_COMBOBOX_TEXT), CB_ADDSTRING, 0, (LPARAM)_T("6"));
		SendMessage(GetDlgItem(hWnd, IDC_COMBOBOX_TEXT), CB_ADDSTRING, 0, (LPARAM)_T("7"));
		SendMessage(GetDlgItem(hWnd, IDC_COMBOBOX_TEXT), CB_ADDSTRING, 0, (LPARAM)_T("8"));
		SendMessage(GetDlgItem(hWnd, IDC_COMBOBOX_TEXT), CB_SETCURSEL, 0, 0);

		HWND hBtn = CreateWindow(
			WC_BUTTON,
			_T("Рассчитать"),
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			500, 370, 100, 30,
			hWnd, reinterpret_cast<HMENU>(CALCULATE), NULL, NULL);

		creater(hWnd, hEditers[1], hEditers[2], 175, 110, hFontTitle);
		hEditers[0] = CreateWindow(
			WC_EDIT,
			_T("1"),
			WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT| ES_NUMBER,
			380, 235, 40, 20,
			hWnd, NULL, NULL, NULL);

		SendMessage(hBtn, WM_SETFONT, (WPARAM)hFontTitle, true);
		SendMessage(hEditers[0], WM_SETFONT, (WPARAM)hFontTitle, true);
		SendMessage(hEditers[0], EM_SETLIMITTEXT, 1, 0);
		SendMessage(hWndComboBox, WM_SETFONT, (WPARAM)hFontTitle, true);
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
						ItemIndex = SendMessage((HWND)lParam, (UINT)CB_GETCURSEL, (WPARAM)0, (LPARAM)0);
						if (lastItemIndex < ItemIndex)
						{
							createEditLine(hWnd, hEditers, positionDynamicEditY, indexDynamicEditScores, indexDynamicEditCoef, lastItemIndex, ItemIndex, hFontTitle);
						}
						else
						{
							deleteEdit(hEditers, lastItemIndex, ItemIndex, positionDynamicEditY, indexDynamicEditScores, indexDynamicEditCoef);
						}
						lastItemIndex = ItemIndex;
					}
					break;
					default:
						break;
				}
			}
			break;

			case CALCULATE: {
				TCHAR buffDopScores[6];

				GetWindowText(hEditers[0], buffDopScores, 5);
				dopScores = _wtof(buffDopScores);
				if (dopScores < 0 || dopScores>6)
				{
					MessageBox(hWnd, _T("Введите значение в пределах от 0 до 6"), _T("Неверно введены данные"), MB_ICONERROR);
					break;
				}

				if (getData(hEditers, scores, coefficients, ItemIndex))
				{
					text[1] = std::to_wstring(averageScore(scores));
					text[3] = std::to_wstring(ratingScore(scores, coefficients, dopScores));
				}
				else
					break;
				InvalidateRect(hWnd, NULL, 1);
			}
			break;

			case CLEAR_ALL:
				menuClear(hEditers, SIZE_EDIT, CLEAR_ALL);
				break;
			case CLEAR_BALS:
				menuClear(hEditers, SIZE_EDIT, CLEAR_BALS);
				break;
			case CLEAR_COEF:
				menuClear(hEditers, SIZE_EDIT, CLEAR_COEF);
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

		// Сonstant text output.
		SetRect(&rt,60, 70, 160, 110);
		DrawText(hdc, text[j].c_str(), text[j].length(), &rt, DT_LEFT);
		SetRect(&rt, 175, 70, 355, 110);
		j++;
		DrawText(hdc, text[j].c_str(), text[j].length(), &rt, DT_LEFT);
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
		_T("Расчет рейтинга"),
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