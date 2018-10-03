#pragma once

#include <string>
#include <windows.h>   
#include <cmath>
#include <cctype>

void AddWindowText(HWND, char * text);
void LessWindowText(HWND);
void NullWindowText(HWND, HWND);
//char* Result(HWND);
std::string leftnum(std::string, int);
std::string rigthnum(std::string, int);
void ONP(HWND);