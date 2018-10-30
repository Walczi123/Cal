#pragma once

#include <string>
#include <windows.h>   
#include <cmath>
#include <deque>
#include <algorithm>

void AddWindowText(HWND, std::string text);
void LessWindowText(HWND);
void NullWindowText(HWND, HWND);
unsigned int priority(std::string);
std::string read_num(std::string);
std::deque<std::string> ONP(HWND,HWND);
std::string Result(std::deque<std::string>,HWND);
std::deque<std::string> ONP(std::string, HWND);
std::string Ans(HWND);
double log(double, double);
double factorial(double);

