#include "Functions.h"

void AddWindowText(HWND h, char * text)
{
	int length = GetWindowTextLength(h);
	LPSTR buffer = (LPSTR)GlobalAlloc(GPTR, length + 1);
	GetWindowText(h, buffer, length + 1);
	int size = strlen(text);
	char * write = new char[length + size + 1];
	strcpy(write, buffer);
	strcat(write, text);
	SetWindowText(h, write);
	GlobalFree(buffer);
	delete[] write;
	return;
}

void LessWindowText(HWND h)
{
	int length = GetWindowTextLength(h);
	int i;
	if (length) {
		LPSTR buffer = (LPSTR)GlobalAlloc(GPTR, length + 1);
		GetWindowText(h, buffer, length);
		char * write = new char[length];
		for (i = 0; i < length - 1; i++) {
			write[i] = (char)buffer[i];
		}
		write[i] = '\0';
		SetWindowText(h, write);
	}
	return;
}

void NullWindowText(HWND h1, HWND h2)
{
	if(GetWindowTextLength(h1))SetWindowText(h1, "");
	if(GetWindowTextLength(h2))SetWindowText(h2, "");
	return;
}

char* Result(HWND hwnd)
{
	char *result=new char[100];
	int length = GetWindowTextLength(hwnd), i=0,j=0,last=0,n1,n2,r;
	LPSTR buffer = (LPSTR)GlobalAlloc(GPTR, length + 1);
	GetWindowText(hwnd, buffer, length + 1);
	//char * write = new char[length + 1];
	std::string write(buffer);
	std::string num1, num2;
	GlobalFree(buffer);
	for (i = 1; i <= length; i++) { 
		if (write[i]=='+') {
			n1= leftnum(write,i);
			n2 = rigthnum(write, i);
			_itoa(n1+n2, result, 10);
			break;
		};
		if (write[i] == '-') {
			n1 = leftnum(write, i);
			n2 = rigthnum(write, i);
			_itoa(n1 - n2, result, 10);
			break;
		};
		if (write[i] == '*') {
			n1 = leftnum(write, i);
			n2 = rigthnum(write, i);
			_itoa(n1 * n2, result, 10);
			break;
		};
		if (write[i] == '/') {
			n1 = leftnum(write, i);
			n2 = rigthnum(write, i);
			if (n2 == 0) {
				std::string a = { "Error, nie podziele przez 0" };
				result = (char*)(a.c_str());
			}
			_itoa(n1 / n2, result, 10);
			break;
		};
		/*if (!isdigit(write[i])){
			token[j++]=write.erase(last, i);
			last = i;
		}*/
	}

	return result;
}

int leftnum(std::string text, int z)
{
	int i = 0;
	std::string t(text),num;
	for (i = z-1; i > 0; i--) {
		if (!isdigit(text[i])) break;
	}
	num = t.erase(i, z - i);
	return atoi(num.c_str());
}

int rigthnum(std::string text , int z )
{
	int i = 0;
	std::string t(text), num;
	for (i = z + 1 ; i < text.length(); i++) {
		if (!isdigit(text[i])) break;
	}
	num = t.erase(z, i);
	return atoi(num.c_str());
}
