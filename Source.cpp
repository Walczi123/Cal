#include "Buttons.h"
#include "Functions.h"

LPSTR NazwaKlasy = "Main Window";
MSG Komunikat;
HWND BPlus, BMinus,BMult, BDiv, BEqual, p1, p2, p3, p4, p5,p6,p7,p8,p9,p10,p11,p12,p13,p14,p15,p16,p17,p18,p19,p20,p21,p22,p23,p24,p25,p26, p27, p28, p29, p30, p31, p32, p33, p34, p35, p36, p37, p38;
HWND BClear, BClearAll,B_0, B_1, B_2, B_3, B_4, B_5, B_6, B_7, B_8, B_9,B_pi,B_e;
HWND MainText, ResultText;
HANDLE hOut;

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
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = NazwaKlasy;
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);\

	// REJESTROWANIE KLASY OKNA
	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, "Wysoka Komisja odmawia rejestracji tego okna!", "Niestety...",
			MB_ICONEXCLAMATION | MB_OK);
		return 1;
	}

	// TWORZENIE OKNA
	HWND hwnd;

	hwnd = CreateWindowEx(WS_EX_CLIENTEDGE, NazwaKlasy, "Calculator", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 442, 378, NULL, NULL, hInstance, NULL);

	if (hwnd == NULL)
	{
		MessageBox(NULL, "Okno odmówiło przyjścia na świat!", "Ale kicha...", MB_ICONEXCLAMATION);
		return 1;
	}

	ShowWindow(hwnd, nCmdShow); // Pokaż okienko...
	UpdateWindow(hwnd);

	//Text Box
	MainText = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | ES_AUTOVSCROLL | WS_VSCROLL, 7, 7, 408, 60, hwnd, (HMENU)ID_TMain, hInstance, NULL);
	ResultText = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE , 107, 74, 308, 25, hwnd, (HMENU)ID_TResult, hInstance, NULL);
	SendMessage(MainText, WM_SETFONT, (WPARAM)GetStockObject(DEFAULT_GUI_FONT), (LPARAM)true);

	SetWindowText(MainText, "Wpisz tu coś");
	DWORD dlugosc = GetWindowTextLength(MainText);
	LPSTR Bufor = (LPSTR)GlobalAlloc(GPTR, dlugosc + 1);
	GetWindowText(MainText, Bufor, dlugosc + 1);


	//Buttons
	int Bwide = 51, Bhight = 45;
	int level1 = 106, level2 = level1 + Bhight, level3 = level2 + Bhight, level4 = level3 + Bhight, level5 = level4 + Bhight;
	int row1 = 7, row2 = row1 + Bwide, row3 = row2 + Bwide, row4 = row3 + Bwide, row5 = row4 + Bwide, row6 = row5 + Bwide, row7 = row6 + Bwide, row8 = row7 + Bwide;

	//level1
	p7 = CreateWindowEx(WS_EX_CLIENTEDGE, "STATIC", "1", WS_CHILD | WS_VISIBLE, row1, level1, Bwide, Bhight, hwnd, NULL, hInstance, NULL);
	p8 = CreateWindowEx(WS_EX_CLIENTEDGE, "STATIC", "2", WS_CHILD | WS_VISIBLE, row2, level1, Bwide, Bhight, hwnd, NULL, hInstance, NULL);
	p9 = CreateWindowEx(WS_EX_CLIENTEDGE, "STATIC", "3", WS_CHILD | WS_VISIBLE, row3, level1, Bwide, Bhight, hwnd, NULL, hInstance, NULL);
	B_pi = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "pi", WS_CHILD | WS_VISIBLE, row4, level1, Bwide, Bhight, hwnd, (HMENU)ID_B_pi, hInstance, NULL);
	B_e = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "e", WS_CHILD | WS_VISIBLE, row5, level1, Bwide, Bhight, hwnd, (HMENU)ID_B_e, hInstance, NULL);
	p12 = CreateWindowEx(WS_EX_CLIENTEDGE, "STATIC", "6", WS_CHILD | WS_VISIBLE, row6, level1, Bwide, Bhight, hwnd, NULL, hInstance, NULL);
	BClear = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "CE", WS_CHILD | WS_VISIBLE, row7, level1, Bwide, Bhight, hwnd, (HMENU)ID_BClear, hInstance, NULL);
	BClearAll = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "C", WS_CHILD | WS_VISIBLE, row8, level1, Bwide, Bhight, hwnd, (HMENU)ID_BClearAll, hInstance, NULL);
	//level2
	p1 = CreateWindowEx(WS_EX_CLIENTEDGE, "STATIC", "1", WS_CHILD | WS_VISIBLE, row1, level2, Bwide, Bhight, hwnd, NULL, hInstance, NULL);
	p2 = CreateWindowEx(WS_EX_CLIENTEDGE, "STATIC", "2", WS_CHILD | WS_VISIBLE, row2, level2, Bwide, Bhight, hwnd, NULL, hInstance, NULL);
	p3 = CreateWindowEx(WS_EX_CLIENTEDGE, "STATIC", "3", WS_CHILD | WS_VISIBLE, row3, level2, Bwide, Bhight, hwnd, NULL, hInstance, NULL);
	B_7 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "7", WS_CHILD | WS_VISIBLE, row4, level2, Bwide, Bhight, hwnd, (HMENU)ID_B_7, hInstance, NULL);
	B_8 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "8", WS_CHILD | WS_VISIBLE, row5, level2, Bwide, Bhight, hwnd, (HMENU)ID_B_8, hInstance, NULL);
	B_9 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "9", WS_CHILD | WS_VISIBLE, row6, level2, Bwide, Bhight, hwnd, (HMENU)ID_B_9, hInstance, NULL);
	BPlus = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "+", WS_CHILD | WS_VISIBLE, row7, level2, Bwide, Bhight, hwnd, (HMENU)ID_BPlus, hInstance, NULL);
	BMinus = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "-", WS_CHILD | WS_VISIBLE, row8, level2, Bwide, Bhight, hwnd, (HMENU)ID_BMinus, hInstance, NULL);
	//level3
	p15 = CreateWindowEx(WS_EX_CLIENTEDGE, "STATIC", "1", WS_CHILD | WS_VISIBLE, row1, level3, Bwide, Bhight, hwnd, NULL, hInstance, NULL);
	p16 = CreateWindowEx(WS_EX_CLIENTEDGE, "STATIC", "2", WS_CHILD | WS_VISIBLE, row2, level3, Bwide, Bhight, hwnd, NULL, hInstance, NULL);
	p17 = CreateWindowEx(WS_EX_CLIENTEDGE, "STATIC", "3", WS_CHILD | WS_VISIBLE, row3, level3, Bwide, Bhight, hwnd, NULL, hInstance, NULL);
	B_4 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "4", WS_CHILD | WS_VISIBLE, row4, level3, Bwide, Bhight, hwnd, (HMENU)ID_B_4, hInstance, NULL);
	B_5 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "5", WS_CHILD | WS_VISIBLE, row5, level3, Bwide, Bhight, hwnd, (HMENU)ID_B_5, hInstance, NULL);
	B_6 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "6", WS_CHILD | WS_VISIBLE, row6, level3, Bwide, Bhight, hwnd, (HMENU)ID_B_6, hInstance, NULL);
	BMult = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "*", WS_CHILD | WS_VISIBLE, row7, level3, Bwide, Bhight, hwnd, (HMENU)ID_BMult, hInstance, NULL);
	BDiv = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "/", WS_CHILD | WS_VISIBLE, row8, level3, Bwide, Bhight, hwnd, (HMENU)ID_BDiv, hInstance, NULL);
	//level4
	p23 = CreateWindowEx(WS_EX_CLIENTEDGE, "STATIC", "1", WS_CHILD | WS_VISIBLE, row1, level4, Bwide, Bhight, hwnd, NULL, hInstance, NULL);
	p24 = CreateWindowEx(WS_EX_CLIENTEDGE, "STATIC", "2", WS_CHILD | WS_VISIBLE, row2, level4, Bwide, Bhight, hwnd, NULL, hInstance, NULL);
	p25 = CreateWindowEx(WS_EX_CLIENTEDGE, "STATIC", "3", WS_CHILD | WS_VISIBLE, row3, level4, Bwide, Bhight, hwnd, NULL, hInstance, NULL);
	B_1 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "1", WS_CHILD | WS_VISIBLE, row4, level4, Bwide, Bhight, hwnd, (HMENU)ID_B_1, hInstance, NULL);
	B_2 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "2", WS_CHILD | WS_VISIBLE, row5, level4, Bwide, Bhight, hwnd, (HMENU)ID_B_2, hInstance, NULL);
	B_3 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "3", WS_CHILD | WS_VISIBLE, row6, level4, Bwide, Bhight, hwnd, (HMENU)ID_B_3, hInstance, NULL);
	p29 = CreateWindowEx(WS_EX_CLIENTEDGE, "STATIC", "7", WS_CHILD | WS_VISIBLE, row7, level4, Bwide, Bhight, hwnd, (HMENU)ID_BPlus, hInstance, NULL);
	p30 = CreateWindowEx(WS_EX_CLIENTEDGE, "STATIC", "8", WS_CHILD | WS_VISIBLE, row8, level4, Bwide, Bhight, hwnd, (HMENU)ID_BMinus, hInstance, NULL);
	//level5
	p31 = CreateWindowEx(WS_EX_CLIENTEDGE, "STATIC", "1", WS_CHILD | WS_VISIBLE, row1, level5, Bwide, Bhight, hwnd, NULL, hInstance, NULL);
	p32 = CreateWindowEx(WS_EX_CLIENTEDGE, "STATIC", "2", WS_CHILD | WS_VISIBLE, row2, level5, Bwide, Bhight, hwnd, NULL, hInstance, NULL);
	p33 = CreateWindowEx(WS_EX_CLIENTEDGE, "STATIC", "3", WS_CHILD | WS_VISIBLE, row3, level5, Bwide, Bhight, hwnd, NULL, hInstance, NULL);
	B_0 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "0", WS_CHILD | WS_VISIBLE, row4, level5, Bwide, Bhight, hwnd, (HMENU)ID_B_0, hInstance, NULL);
	p35 = CreateWindowEx(WS_EX_CLIENTEDGE, "STATIC", "5", WS_CHILD | WS_VISIBLE, row5, level5, Bwide, Bhight, hwnd, NULL, hInstance, NULL);
	p36 = CreateWindowEx(WS_EX_CLIENTEDGE, "STATIC", "6", WS_CHILD | WS_VISIBLE, row6, level5, Bwide, Bhight, hwnd, NULL, hInstance, NULL);
	p37 = CreateWindowEx(WS_EX_CLIENTEDGE, "STATIC", "7", WS_CHILD | WS_VISIBLE, row7, level5, Bwide, Bhight, hwnd, (HMENU)ID_BPlus, hInstance, NULL);
	BEqual = CreateWindowEx(0, "BUTTON", "=", WS_CHILD | WS_VISIBLE, row8, level5, Bwide, Bhight, hwnd, (HMENU)ID_BEqual, hInstance, NULL);
	
	// Pętla komunikatów
	while (GetMessage(&Komunikat, NULL, 0, 0))
	{
		TranslateMessage(&Komunikat);
		DispatchMessage(&Komunikat);
	}

	GlobalFree(Bufor);
	return Komunikat.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	char *result;
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
			AddWindowText(MainText, "+");break;
		case ID_BMinus:
			AddWindowText(MainText, "-");break;
		case ID_BMult:
			AddWindowText(MainText, "*"); break;
		case ID_BDiv:
			AddWindowText(MainText, "/"); break;
		case ID_BEqual:
			ONP(MainText);
			//result = Result(MainText);
			SetWindowText(ResultText, result); break;
		case ID_BClear:
			LessWindowText(MainText); break;
		case ID_BClearAll:
			NullWindowText(MainText, ResultText);break;
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
		}
		break;

	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
}