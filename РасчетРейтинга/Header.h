#pragma once
#include<Windows.h>
#include<vector>
#include<tchar.h>
#include <commctrl.h>


void createEditLines(HWND& hWnd, HWND hEditers[], int& startPositionY, int& indexDynamicEditScores, int& indexDynamicEditCoef,const int lastItemIndex,const int itemIndex, HFONT hFontTitle);

void deleteEditLines(HWND hEditers[],const int lastItemIndex,const int itemIndex, int& startYPosition, int& indexDynamicEditScores, int& indexDynamicEditCoef);

void createEditLine(HWND& hWnd, HWND& hEditFirst, HWND& hEditSecond, int x, int y, HFONT hFontTitle);

int getData(HWND hEditers[], std::vector<int>& marks, std::vector<double>& credits, const int itemIndex);

double averageScore(const std::vector<int> marks);

double ratingScore(const std::vector<int> marks,const std::vector<double> credits,const int additionalPoint);

