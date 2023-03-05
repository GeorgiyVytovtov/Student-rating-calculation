#pragma once
#include<Windows.h>
#include<vector>
#include<tchar.h>
#include <commctrl.h>


void createEditLine(HWND& hWnd, HWND hEditers[], int& startPositionY, int& indexDynamicEditScores, int& indexDynamicEditCoef,const int lastItemIndex,const int ItemIndex, HFONT hFontTitle);

void deleteEdit(HWND hEditers[],const int lastItemIndex,const int ItemIndex, int& startYPosition, int& indexDynamicEditScores, int& indexDynamicEditCoef);

void creater(HWND& hWnd, HWND& hEditFirst, HWND& hEditSecond, int x, int y, HFONT hFontTitle);

void menuClear(HWND hEditers[], const int SIZE_EDIT, int clearValue);

int getData(HWND hEditers[], std::vector<double>& scores, std::vector<double>& coef, const int ItemIndex);

double averageScore(const std::vector<double> scores);

double ratingScore(const std::vector<double> scores,const std::vector<double> coef,const double dopScores);

