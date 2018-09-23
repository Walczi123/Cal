#pragma once

#include <string>
#include <windows.h>   
#include <cmath>
#include <cctype>

void AddWindowText(HWND, char * text);
void LessWindowText(HWND);
void NullWindowText(HWND, HWND);
char* Result(HWND);
int leftnum(std::string, int);
int rigthnum(std::string, int);