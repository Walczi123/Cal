#include "Buttons.h"
#include "Functions.h"
#include "Resource.h"

#include <commctrl.h> 

LPSTR NazwaKlasy = "Main Window";
MSG Komunikat;
HWND BPlus, BMinus, BMult, BDiv, BEqual, BClear, BClearAll, B_0, B_1, B_2, B_3, B_4, B_5, B_6, B_7, B_8, B_9, B_pi, B_e;
HWND p_sin, p_cos, p_tan, B_null, B_p2, B_p1, B_p, B_fac, B_log, B_ln, B_riv, B_root, B_sqrt, B_lp, B_rp, B_dot, B_Ans, B_10p;
HWND MainText, ResultText;
HANDLE hOut;
const int cor = 8;
//HRGN hrZaokr = CreateRoundRectRgn(10,10 , 442 - cor, 378 - cor, -(2*cor), -(2 * cor));


LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// WYPEŁNIANIE STRUKTURY
	WNDCLASSEX wc;

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = 0;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_BTNFACE + 1); 
	wc.lpszMenuName = NULL;
	wc.lpszClassName = NazwaKlasy;
	wc.hIconSm = (HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(2503), IMAGE_ICON, 24, 24, 32);
	wc.hIcon = (HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(2503), IMAGE_ICON, 24, 24, 32);

		// REJESTROWANIE KLASY OKNA
	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, "Wysoka Komisja odmawia rejestracji tego okna!", "Niestety...",
			MB_ICONEXCLAMATION | MB_OK);
		return 1;
	}

	// TWORZENIE OKNA
	HWND hwnd;
	hwnd = CreateWindowEx(WS_EX_CLIENTEDGE, NazwaKlasy, "Calculator", WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX , CW_USEDEFAULT, CW_USEDEFAULT, 442, 378, NULL, NULL, hInstance, NULL);

	if (hwnd == NULL)
	{
		MessageBox(NULL, "Okno odmówiło przyjścia na świat!", "Ale kicha...", MB_ICONEXCLAMATION);
		return 1;
	}

	ShowWindow(hwnd, nCmdShow); // Pokaż okienko...
	//SetWindowRgn(hwnd, hrZaokr, TRUE);
	UpdateWindow(hwnd);

	//Text Box
	MainText = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | ES_AUTOVSCROLL | WS_VSCROLL, 7, 7, 408, 60, hwnd, (HMENU)ID_TMain, hInstance, NULL);
	ResultText = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE , 107, 74, 308, 25, hwnd, (HMENU)ID_TResult, hInstance, NULL);
	SendMessage(MainText, WM_SETFONT, (WPARAM)GetStockObject(DEFAULT_GUI_FONT), (LPARAM)true);
	HFONT MyFont = CreateFont(18, 0, 0, 0, 0, TRUE, 0, 0, 0, 0, 0, 0, 0, "Arial");
	SendMessage(MainText, WM_SETFONT, (WPARAM)MyFont, (LPARAM)true);

	//Buttons
	int Bwide = 51, Bhight = 45;
	int level1 = 106, level2 = level1 + Bhight, level3 = level2 + Bhight, level4 = level3 + Bhight, level5 = level4 + Bhight;
	int row1 = 7, row2 = row1 + Bwide, row3 = row2 + Bwide, row4 = row3 + Bwide, row5 = row4 + Bwide, row6 = row5 + Bwide, row7 = row6 + Bwide, row8 = row7 + Bwide;

	//level1
	p_sin = CreateWindowEx(WS_EX_PALETTEWINDOW, "BUTTON", "sin", WS_CHILD | WS_VISIBLE, row1, level1, Bwide, Bhight, hwnd, (HMENU)ID_B_sin, hInstance, NULL);
	p_cos = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "cos", WS_CHILD | WS_VISIBLE, row2, level1, Bwide, Bhight, hwnd, (HMENU)ID_B_cos, hInstance, NULL);
	p_tan = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "tan", WS_CHILD | WS_VISIBLE, row3, level1, Bwide, Bhight, hwnd, (HMENU)ID_B_tan, hInstance, NULL);
	B_pi = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "pi", WS_CHILD | WS_VISIBLE, row4, level1, Bwide, Bhight, hwnd, (HMENU)ID_B_pi, hInstance, NULL);
	B_e = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "e", WS_CHILD | WS_VISIBLE, row5, level1, Bwide, Bhight, hwnd, (HMENU)ID_B_e, hInstance, NULL);
	//B_null = CreateWindowEx(WS_EX_CLIENTEDGE, "STATIC", "", WS_CHILD | WS_VISIBLE, row6, level1, Bwide, Bhight, hwnd, (HMENU)ID_B_null, hInstance, NULL);
	BClear = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "CE", WS_CHILD | WS_VISIBLE, row7, level1, Bwide, Bhight, hwnd, (HMENU)ID_BClear, hInstance, NULL);
	BClearAll = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "C", WS_CHILD | WS_VISIBLE, row8, level1, Bwide, Bhight, hwnd, (HMENU)ID_BClearAll, hInstance, NULL);
	//level2
	B_p2 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "x^2", WS_CHILD | WS_VISIBLE, row1, level2, Bwide, Bhight, hwnd, (HMENU)ID_B_p2, hInstance, NULL);
	B_p1 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "x^(-1)", WS_CHILD | WS_VISIBLE, row2, level2, Bwide, Bhight, hwnd, (HMENU)ID_B_p1, hInstance, NULL);
	B_p = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "x^y", WS_CHILD | WS_VISIBLE, row3, level2, Bwide, Bhight, hwnd, (HMENU)ID_B_p, hInstance, NULL);
	B_7 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "7", WS_CHILD | WS_VISIBLE, row4, level2, Bwide, Bhight, hwnd, (HMENU)ID_B_7, hInstance, NULL);
	B_8 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "8", WS_CHILD | WS_VISIBLE, row5, level2, Bwide, Bhight, hwnd, (HMENU)ID_B_8, hInstance, NULL);
	B_9 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "9", WS_CHILD | WS_VISIBLE, row6, level2, Bwide, Bhight, hwnd, (HMENU)ID_B_9, hInstance, NULL);
	BPlus = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "+", WS_CHILD | WS_VISIBLE, row7, level2, Bwide, Bhight, hwnd, (HMENU)ID_BPlus, hInstance, NULL);
	BMinus = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "-", WS_CHILD | WS_VISIBLE, row8, level2, Bwide, Bhight, hwnd, (HMENU)ID_BMinus, hInstance, NULL);
	//level3
	B_fac = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "x!", WS_CHILD | WS_VISIBLE, row1, level3, Bwide, Bhight, hwnd, (HMENU)ID_B_fac, hInstance, NULL);
	B_log = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "log", WS_CHILD | WS_VISIBLE, row2, level3, Bwide, Bhight, hwnd, (HMENU)ID_B_log, hInstance, NULL);
	B_ln = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "ln", WS_CHILD | WS_VISIBLE, row3, level3, Bwide, Bhight, hwnd, (HMENU)ID_B_ln, hInstance, NULL);
	B_4 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "4", WS_CHILD | WS_VISIBLE, row4, level3, Bwide, Bhight, hwnd, (HMENU)ID_B_4, hInstance, NULL);
	B_5 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "5", WS_CHILD | WS_VISIBLE, row5, level3, Bwide, Bhight, hwnd, (HMENU)ID_B_5, hInstance, NULL);
	B_6 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "6", WS_CHILD | WS_VISIBLE, row6, level3, Bwide, Bhight, hwnd, (HMENU)ID_B_6, hInstance, NULL);
	BMult = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "*", WS_CHILD | WS_VISIBLE, row7, level3, Bwide, Bhight, hwnd, (HMENU)ID_BMult, hInstance, NULL);
	BDiv = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "/", WS_CHILD | WS_VISIBLE, row8, level3, Bwide, Bhight, hwnd, (HMENU)ID_BDiv, hInstance, NULL);
	//level4
	//B_riv = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "1/x", WS_CHILD | WS_VISIBLE, row1, level4, Bwide, Bhight, hwnd, (HMENU)ID_B_riv, hInstance, NULL);
	B_sqrt = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "sqrt", WS_CHILD | WS_VISIBLE, row2, level4, Bwide, Bhight, hwnd, (HMENU)ID_B_sqrt, hInstance, NULL);
	B_root = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "√", WS_CHILD | WS_VISIBLE, row3, level4, Bwide, Bhight, hwnd, (HMENU)ID_B_root, hInstance, NULL);
	B_1 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "1", WS_CHILD | WS_VISIBLE, row4, level4, Bwide, Bhight, hwnd, (HMENU)ID_B_1, hInstance, NULL);
	B_2 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "2", WS_CHILD | WS_VISIBLE, row5, level4, Bwide, Bhight, hwnd, (HMENU)ID_B_2, hInstance, NULL);
	B_3 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "3", WS_CHILD | WS_VISIBLE, row6, level4, Bwide, Bhight, hwnd, (HMENU)ID_B_3, hInstance, NULL);
	B_lp = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "(", WS_CHILD | WS_VISIBLE, row7, level4, Bwide, Bhight, hwnd, (HMENU)ID_B_lp, hInstance, NULL);
	B_rp = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", ")", WS_CHILD | WS_VISIBLE, row8, level4, Bwide, Bhight, hwnd, (HMENU)ID_B_rp, hInstance, NULL);
	//level5
	//p31 = CreateWindowEx(WS_EX_CLIENTEDGE, "STATIC", "1", WS_CHILD | WS_VISIBLE, row1, level5, Bwide, Bhight, hwnd, NULL, hInstance, NULL);
	//p32 = CreateWindowEx(WS_EX_CLIENTEDGE, "STATIC", "2", WS_CHILD | WS_VISIBLE, row2, level5, Bwide, Bhight, hwnd, NULL, hInstance, NULL);
	//p33 = CreateWindowEx(WS_EX_CLIENTEDGE, "STATIC", "3", WS_CHILD | WS_VISIBLE, row3, level5, Bwide, Bhight, hwnd, NULL, hInstance, NULL);
	B_0 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "0", WS_CHILD | WS_VISIBLE, row4, level5, Bwide, Bhight, hwnd, (HMENU)ID_B_0, hInstance, NULL);
	B_dot = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", ".", WS_CHILD | WS_VISIBLE, row5, level5, Bwide, Bhight, hwnd, (HMENU)ID_B_dot, hInstance, NULL);
	B_10p = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "10^x", WS_CHILD | WS_VISIBLE, row6, level5, Bwide, Bhight, hwnd, (HMENU)ID_B_10p, hInstance, NULL);
	B_Ans = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "Ans", WS_CHILD | WS_VISIBLE, row7, level5, Bwide, Bhight, hwnd, (HMENU)ID_B_Ans, hInstance, NULL);
	BEqual = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "=", WS_CHILD | WS_VISIBLE, row8, level5, Bwide, Bhight, hwnd, (HMENU)ID_BEqual, hInstance, NULL);
	
	// Pętla komunikatów
	while (GetMessage(&Komunikat, NULL, 0, 0))
	{
		TranslateMessage(&Komunikat);
		DispatchMessage(&Komunikat);
	}

	return Komunikat.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	std::string result,ans;
	switch (msg)
	{
	case WM_CLOSE:
		DestroyWindow(hwnd); break;
	case WM_DESTROY:
		PostQuitMessage(0); break;
	case WM_COMMAND:
		switch (wParam)
		{
		case ID_BPlus:
			AddWindowText(MainText, "+"); break;
		case ID_BMinus:
			AddWindowText(MainText, "-"); break;
		case ID_BMult:
			AddWindowText(MainText, "*"); break;
		case ID_BDiv:
			AddWindowText(MainText, "/"); break;
		case ID_BEqual:
			result = Result(ONP(MainText, hwnd), hwnd);
			SetWindowText(ResultText, result.c_str());
			break;
		case ID_BClear:
			LessWindowText(MainText); break;
		case ID_BClearAll:
			NullWindowText(MainText, ResultText); break;
		case ID_B_0:
			AddWindowText(MainText, "0"); break;
		case ID_B_1:
			AddWindowText(MainText, "1"); break;
		case ID_B_2:
			AddWindowText(MainText, "2"); break;
		case ID_B_3:
			AddWindowText(MainText, "3"); break;
		case ID_B_4:
			AddWindowText(MainText, "4"); break;
		case ID_B_5:
			AddWindowText(MainText, "5"); break;
		case ID_B_6:
			AddWindowText(MainText, "6"); break;
		case ID_B_7:
			AddWindowText(MainText, "7"); break;
		case ID_B_8:
			AddWindowText(MainText, "8"); break;
		case ID_B_9:
			AddWindowText(MainText, "9"); break;
		case ID_B_pi:
			AddWindowText(MainText, "pi"); break;
		case ID_B_e:
			AddWindowText(MainText, "e"); break;
		case ID_B_p2:
			AddWindowText(MainText, "^2"); break;
		case ID_B_p1:
			AddWindowText(MainText, "^(-1)"); break;
		case ID_B_p:
			AddWindowText(MainText, "^"); break;
		case ID_B_10p:
			AddWindowText(MainText, "10^"); break;
		case ID_B_dot:
			AddWindowText(MainText, "."); break;
		case ID_B_lp:
			AddWindowText(MainText, "("); break;
		case ID_B_rp:
			AddWindowText(MainText, ")"); break;
		case ID_B_Ans:
			ans = Ans(ResultText);
			AddWindowText(MainText, ans.c_str()); break;
		case ID_B_sin:
			AddWindowText(MainText, "sin("); break;
		case ID_B_cos:
			AddWindowText(MainText, "cos("); break;
		case ID_B_tan:
			AddWindowText(MainText, "tan("); break;
		case ID_B_log:
			AddWindowText(MainText, "log"); break;
		case ID_B_ln:
			AddWindowText(MainText, "ln("); break;
		case ID_B_sqrt:
			AddWindowText(MainText, "sqrt("); break;
		case ID_B_root:
			AddWindowText(MainText, "√"); break;
		case ID_B_fac:
			AddWindowText(MainText, "!"); break;

		}break;
	case WM_KEYDOWN:
		switch ((int)wParam)
		{
		case VK_RETURN:
			MessageBox(hwnd, "Wciśnięto Entera", "Yeah", MB_ICONINFORMATION);
			break;

		case VK_ESCAPE:
			DestroyWindow(hwnd);
			break;
		}break;
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
}