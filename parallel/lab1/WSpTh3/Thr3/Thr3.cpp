// Thr3.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "resource.h"
//#include "windowsx.h"
#define MAX_LOADSTRING 100
//Look into Windowsx.h for System definitions without the prefix R
#define RHANDLE_MSG(hwnd, message, fn)    \
	case (message): return RHANDLE_##message((hwnd), (wParam), (lParam), (fn))

#define RHANDLE_WM_COMMAND(hwnd, wParam, lParam, fn) \
	((fn)((hwnd), (int)(LOWORD(wParam)), (HWND)(lParam), (UINT)HIWORD(wParam)), -1L)

#define RHANDLE_WM_INITDIALOG(hwnd, wParam, lParam, fn) \
	(LRESULT)(DWORD)(UINT)(BOOL)(fn)((hwnd), (HWND)(wParam), lParam)

#define RFORWARD_WM_COMMAND(hwnd, id, hwndCtl, codeNotify, fn) \
	(LONG)(fn)((hwnd), WM_COMMAND, MAKEWPARAM((UINT)(id),(UINT)(codeNotify)), (LPARAM)(HWND)(hwndCtl))


//Globals to control threads
TCHAR szMutexName[] = "$MutexFor3Threads$";
HANDLE hMutex;
HANDLE hThreadE[3];
CRITICAL_SECTION csPaintArea;

BOOL fTerminateE;
BOOL fTerminateR;
BOOL fTerminateT;

bool bSuspendE,
bSuspendT,
bSuspendR;

unsigned thridE;		//thread identifier

DWORD nWM_PAINT = 0;      //WM_PAINT count

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// The title bar text



// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);

//_stdcall for CALLBACK (see Windef.h)
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);

LRESULT CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	ChangeThreadPriority_Box(HWND, UINT, WPARAM, LPARAM);

BOOL ChThPr_OnInitDialog(HWND hDlg, HWND hwndFocus, LPARAM lParam);
LONG ChThPr_OnCommand(HWND hDlg, int id, HWND hwndCtl, UINT codeNotify);



LONG WndProc_OnCreate(HWND hWnd, LPCREATESTRUCT lpCreateStruct);
LONG WndProc_OnDestroy(HWND hWnd);
void WndProc_OnPaint(HWND hWnd);
LONG WndProc_OnCommand(HWND hWnd, int id, HWND hwndCtl, UINT codeNotify);
void WndProc_OnClose(HWND hWnd);

unsigned int __stdcall  PaintEllipse(void *hWnd);
unsigned int __stdcall  PaintRectangle(void *hWnd);
unsigned int __stdcall  PaintText(void *hWnd);

void SuspendEllipse(HMENU hMenu, bool *bSuspend);
void SuspendRectangle(HMENU hMenu, bool *bSuspend);
void SuspendText(HMENU hMenu, bool *bSuspend);

void TerminateEllipse(HWND hWnd, HMENU hMenu, BOOL *fTerminate);
void TerminateRectangle(HWND hWnd, HMENU hMenu, BOOL *fTerminate);
void TerminateText(HWND hWnd, HMENU hMenu, BOOL *fTerminate);

//_stdcall for APIENTRY (see Windef.h), used for new and last versions
int APIENTRY WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR     lpCmdLine,
	int       nCmdShow)

{//Create an object Mutex (named)
	//As it is named it is possible to verify if there is only one application instance too!
	if (!(hMutex = CreateMutex(NULL, FALSE, szMutexName))) {//FALSE sets it In SIGNALED STATE!
		//NO OWNERSHIP	
		MessageBox(NULL, "CreateMutex Error", "Four Threads",
			MB_OK | MB_ICONEXCLAMATION);
		return 01;
	}
	if (GetLastError() == ERROR_ALREADY_EXISTS) {
		MessageBox(NULL, "Mutex already started", "Four Threads",
			MB_OK | MB_ICONEXCLAMATION);
		return 01;

	}

	InitializeCriticalSection(&csPaintArea);

	TCHAR msgHINST[250];
	wsprintf(msgHINST, TEXT("HINSTANCE is %ld"), hInstance);
	MessageBox(NULL, msgHINST, "Four Threads",
		MB_OK);

	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_THR3, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, (LPCTSTR)IDC_THR3);

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
//    This function and its usage is only necessary if you want this code
//    to be compatible with Win32 systems prior to the 'RegisterClassEx'
//    function that was added to Windows 95. It is important to call this function
//    so that the application will get 'well formed' small icons associated
//    with it.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = (WNDPROC)WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, (LPCTSTR)IDI_THR3);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = (LPCSTR)IDC_THR3;
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, (LPCTSTR)IDI_SMALL);

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HANDLE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;

	hInst = hInstance; // Store instance handle in our global variable

	hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

//
//  FUNCTION: WndProc(HWND, unsigned, WORD, LONG)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	//	int wmId, wmEvent;
	switch (message)
	{
		HANDLE_MSG(hWnd, WM_COMMAND, WndProc_OnCommand);//!
		HANDLE_MSG(hWnd, WM_PAINT, WndProc_OnPaint);//!
		HANDLE_MSG(hWnd, WM_CREATE, WndProc_OnCreate);//!
		HANDLE_MSG(hWnd, WM_DESTROY, WndProc_OnDestroy);//!
		HANDLE_MSG(hWnd, WM_CLOSE, WndProc_OnClose);//!
	default:return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;//BY CHANCE TO BE USED
}
LONG WndProc_OnCommand(HWND hWnd, int id, HWND hwndCtl, UINT codeNotify)
{
	// Parse the menu selections:
	switch (id)
	{
	case IDM_SUSE:
		SuspendEllipse(GetMenu(hWnd), &bSuspendE);
		return 0L;

	case IDM_SUSR:
		SuspendRectangle(GetMenu(hWnd), &bSuspendR);
		return 0L;

	case ID_COMMAND_SUSPENDTEXT:
		SuspendText(GetMenu(hWnd), &bSuspendT);
		return 0L;

	case IDM_TERME:
		TerminateEllipse(hWnd, GetMenu(hWnd), &fTerminateE);
		return 0L;

	case IDM_TERMR:
		TerminateRectangle(hWnd, GetMenu(hWnd), &fTerminateR);
		return 0L;

	case IDM_TERMT:
		TerminateText(hWnd, GetMenu(hWnd), &fTerminateT);
		return 0L;

	case IDM_CH_THR_PR_ELL:
		DialogBox(hInst, (LPCTSTR)IDD_DIALOG_PRIORITY, hWnd,
			(DLGPROC)ChangeThreadPriority_Box);
		return 0L;

	case IDM_ABOUT:
		DialogBox(hInst, (LPCTSTR)IDD_ABOUTBOX, hWnd, (DLGPROC)About);
		return 0L;//   break;
	case IDM_EXIT:
		DestroyWindow(hWnd); //PostQuitMessage(0);					                        
		return 0L;//  break;
	default:break;
		// return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return RFORWARD_WM_COMMAND(hWnd, id, hwndCtl, codeNotify, DefWindowProc);
}

void WndProc_OnPaint(HWND hWnd)
{
	PAINTSTRUCT ps;
	HDC hdc;
	TCHAR szHello[MAX_LOADSTRING];
	TCHAR sznWM_PAINT[50];
	DWORD dwRetCode;
	LoadString(hInst, IDS_HELLO, szHello, MAX_LOADSTRING);

	EnterCriticalSection(&csPaintArea);
	hdc = BeginPaint(hWnd, &ps);
	// TODO: Add any drawing code here...
	RECT rt;
	GetClientRect(hWnd, &rt);

	DrawText(hdc, szHello, strlen(szHello), &rt, DT_CENTER);

	wsprintf(sznWM_PAINT, TEXT("nWM_PAINT=%d"), nWM_PAINT);
	rt.top = rt.top + 50;
	DrawText(hdc, sznWM_PAINT, strlen(sznWM_PAINT), &rt, DT_CENTER);

	EndPaint(hWnd, &ps);
	nWM_PAINT++;
	LeaveCriticalSection(&csPaintArea);
}
// This program requires the multithreaded library. For example,
// compile with the following command line:
//     CL /MT /D "_X86_" BEGTHRD.C

LONG WndProc_OnCreate(HWND hWnd, LPCREATESTRUCT lpCreateStruct)
{
	fTerminateE = FALSE;
	fTerminateR = FALSE;
	fTerminateT = FALSE;

	bSuspendE = false;
	bSuspendR = false;
	bSuspendT = false;

	unsigned ususpend = 0;
	hThreadE[0] = (HANDLE)_beginthreadex(NULL,//must be FOR W95 ,SA
		0,//stack size committed
		PaintEllipse,
		(void *)hWnd, //*arglist
		ususpend,//0
		&thridE
	);
	if (!hThreadE[0]) {
		MessageBox(NULL, "Thread start Error",
			"PaintEllipse Thread",
			MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	}

	hThreadE[1] = (HANDLE)_beginthreadex(NULL,//must be FOR W95
		0,//stack size
		PaintRectangle,
		(void *)hWnd,
		ususpend,//0
		&thridE
	);
	if (!hThreadE[1]) {
		MessageBox(NULL, "Thread start Error",
			"PaintRectangle Thread",
			MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	}

	hThreadE[2] = (HANDLE)_beginthreadex(NULL,//must be FOR W95
		0,//stack size
		PaintText,
		(void *)hWnd,
		ususpend,//0
		&thridE
	);
	if (!hThreadE[2]) {
		MessageBox(NULL, "Thread start Error",
			"PaintText Thread",
			MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	}


	return TRUE;//BOOL
}
LONG WndProc_OnDestroy(HWND hWnd)
{

	if (bSuspendE)
		ResumeThread(hThreadE[0]);
	if (bSuspendR)
		ResumeThread(hThreadE[1]);
	if (bSuspendT)
		ResumeThread(hThreadE[2]);

	std::vector<HANDLE> threads;

	if (!fTerminateE) {
		threads.push_back(hThreadE[0]);
	}
	if (!fTerminateR) {
		threads.push_back(hThreadE[1]);
	}
	if (!fTerminateT) {
		threads.push_back(hThreadE[2]);
	}

	fTerminateE = TRUE;
	fTerminateR = TRUE;
	fTerminateT = TRUE;

	TCHAR szRetRes[100];
	DWORD dwRet;

	switch (dwRet = WaitForMultipleObjects(threads.size(), threads.data(), TRUE, INFINITE))
	{
	case WAIT_ABANDONED_0:
		wsprintf(szRetRes, TEXT("WAIT_ABANDONED_0=%d dwRet=%d"), WAIT_ABANDONED_0, dwRet);
		MessageBox(NULL, szRetRes, "WaitForMultipleObjects", MB_OK | MB_ICONEXCLAMATION);
		break;
	case WAIT_FAILED:
		break;
	case WAIT_OBJECT_0:
		wsprintf(szRetRes, TEXT("WAIT_OBJECT_0=%d dwRet=%d"), WAIT_OBJECT_0, dwRet);
		MessageBox(NULL, szRetRes, "WaitForMultipleObjects", MB_OK | MB_ICONEXCLAMATION);
		break;
	}

	for each (HANDLE hThread in threads)
	{
		if (!CloseHandle(hThread))
		{
			MessageBox(NULL, "CloseHandle  failed",
				"Thread", MB_OK | MB_ICONEXCLAMATION);
		}
	}

	CloseHandle(hMutex);

	DeleteCriticalSection(&csPaintArea);

	PostQuitMessage(0);
	return (0);
}

void  WndProc_OnClose(HWND hWnd)
{
	/*
	LONG InterlockedExchangeAdd (
	PLONG Addend,  // pointer to the addend
	LONG Increment // increment value
	);
	*/
	DWORD dwn = InterlockedExchangeAdd((PLONG)&nWM_PAINT, 0);

	TCHAR sznWM[50];
	sprintf(sznWM, "nWM_PAINT=%11d\n", dwn);// no nWM_PAINT


	int r = MessageBox(hWnd, sznWM, "Primary Thread WM_PAINT count",
		MB_OKCANCEL | MB_ICONEXCLAMATION);

	DeleteCriticalSection(&cs);
	DestroyWindow(hWnd); // or 
}

// Message handler for about box.
LRESULT CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
		return TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}
		break;
	}
	return FALSE;					//SetDlgMsgResult-???ABSENT
}


unsigned int __stdcall  PaintText(void *hWnd) {
	HDC hDC;
	RECT rect;
	LONG xLeft, xRight, yTop, yBottom;
	short nRed, nGreen, nBlue;
	HBRUSH hBrush, hOldBrush;

	srand((unsigned int)hWnd + 100);
	while (!fTerminateT) {	// Is not it to be continued?
		// To be continued!
		EnterCriticalSection(&csPaintArea);
		hDC = GetDC((HWND)hWnd);
		nRed = rand() % 255; nGreen = rand() % 255; nBlue = rand() % 255;

		GetWindowRect((HWND)hWnd, &rect);
		xLeft = rand() % (rect.left + 1);
		xRight = rand() % (rect.right + 1);
		yTop = rand() % (rect.top + 1);
		yBottom = rand() % (rect.bottom + 1);

		hBrush = CreateSolidBrush(RGB(nRed, nGreen, nBlue));
		hOldBrush = (HBRUSH)SelectObject(hDC, hBrush);
		TextOut(hDC, xLeft, yTop, "Hello", 5);
		SelectObject(hDC, hOldBrush);
		DeleteObject(hBrush);
		ReleaseDC((HWND)hWnd, hDC);
		LeaveCriticalSection(&csPaintArea);
		Sleep(100);
		InvalidateRect((HWND)hWnd, NULL, TRUE);
		Sleep(100);
	}//End of while
	return 0;
}


unsigned int __stdcall  PaintEllipse(void *hWnd) {
	HDC hDC;
	RECT rect;
	LONG xLeft, xRight, yTop, yBottom;
	short nRed, nGreen, nBlue;
	HBRUSH hBrush, hOldBrush;

	srand((unsigned int)hWnd + 100);
	while (!fTerminateE) {	// Is not it to be continued?
		// To be continued!

		EnterCriticalSection(&csPaintArea);
		hDC = GetDC((HWND)hWnd);
		nRed = rand() % 255; nGreen = rand() % 255; nBlue = rand() % 255;

		GetWindowRect((HWND)hWnd, &rect);
		xLeft = rand() % (rect.left + 1);
		xRight = rand() % (rect.right + 1);
		yTop = rand() % (rect.top + 1);
		yBottom = rand() % (rect.bottom + 1);

		hBrush = CreateSolidBrush(RGB(nRed, nGreen, nBlue));
		hOldBrush = (HBRUSH)SelectObject(hDC, hBrush);
		Ellipse(hDC, min(xLeft, xRight), min(yTop, yBottom),
			max(xLeft, xRight), max(yTop, yBottom));
		SelectObject(hDC, hOldBrush);
		DeleteObject(hBrush);
		ReleaseDC((HWND)hWnd, hDC);
		LeaveCriticalSection(&csPaintArea);
		Sleep(100);
		InvalidateRect((HWND)hWnd, NULL, TRUE);
		Sleep(100);
	}//End of while
	return 0;
}//End of PaintEllipse

unsigned int __stdcall  PaintRectangle(void *hWnd) {

	HDC hDC;
	RECT rect;
	LONG xLeft, xRight, yTop, yBottom;
	short nRed, nGreen, nBlue;
	HBRUSH hBrush, hOldBrush;

	srand((unsigned int)hWnd);
	while (!fTerminateR) {
		// Is not it to be continued?

		// To be continued!
		EnterCriticalSection(&csPaintArea);
		hDC = GetDC((HWND)hWnd);
		nRed = rand() % 255; nGreen = rand() % 255; nBlue = rand() % 255;

		GetWindowRect((HWND)hWnd, &rect);
		xLeft = rand() % (rect.left + 1);
		xRight = rand() % (rect.right + 1);
		yTop = rand() % (rect.top + 1);
		yBottom = rand() % (rect.bottom + 1);

		hBrush = CreateSolidBrush(RGB(nRed, nGreen, nBlue));
		hOldBrush = (HBRUSH)SelectObject(hDC, hBrush);
		Rectangle(hDC, min(xLeft, xRight), min(yTop, yBottom),
			max(xLeft, xRight), max(yTop, yBottom));
		SelectObject(hDC, hOldBrush);
		DeleteObject(hBrush);
		ReleaseDC((HWND)hWnd, hDC);

		LeaveCriticalSection(&csPaintArea);

		Sleep(100);
		InvalidateRect((HWND)hWnd, NULL, TRUE);
		Sleep(100);
	}//End of while
	return 0;
}//End of PaintRectangle

//Wrong solution whithout using hMutex???

void SuspendEllipse(HMENU hMenu, bool *bSuspend)
{
	TCHAR message[260];

	EnterCriticalSection(&csPaintArea);
	if (!*bSuspend) {
		if (0xFFFFFFFF == SuspendThread(hThreadE[0]))//or -1 (==0xFFFFFFFF)
		{
			wsprintf(message, TEXT("SuspendThread Error %ld"), GetLastError());
			MessageBox(NULL, message, "PaintEllipse Thread", MB_OK | MB_ICONEXCLAMATION);
			LeaveCriticalSection(&csPaintArea);
			return;
		}

		*bSuspend = true;
		//Check
		//Sets the check-mark attribute to the checked state.
		CheckMenuItem(hMenu, IDM_SUSE, MF_CHECKED);
	}
	else
	{
		if (0xFFFFFFFF == ResumeThread(hThreadE[0]))
		{
			wsprintf(message, TEXT("ResumeThread Error %ld"), GetLastError());
			MessageBox(NULL, message, "PaintEllipse Thread", MB_OK | MB_ICONEXCLAMATION);
			LeaveCriticalSection(&csPaintArea);
			return;
		}

		*bSuspend = false;
		//Uncheck 
		//Sets the check-mark attribute to the unchecked state.
		CheckMenuItem(hMenu, IDM_SUSE, MF_UNCHECKED);
	}
	LeaveCriticalSection(&csPaintArea);
	return;
}

//Right solution 

void SuspendRectangle(HMENU hMenu, bool *bSuspend)
{
	TCHAR message[260];

	EnterCriticalSection(&csPaintArea);
	if (!*bSuspend) {
		if (0xFFFFFFFF == SuspendThread(hThreadE[1]))
		{
			wsprintf(message, TEXT("SuspendThread Error %ld"), GetLastError());
			MessageBox(NULL, message, "PaintRectangle Thread", MB_OK | MB_ICONEXCLAMATION);
			LeaveCriticalSection(&csPaintArea);
			return;
		}

		*bSuspend = true;
		//Check
		//Sets the check-mark attribute to the checked state.
		CheckMenuItem(hMenu, IDM_SUSR, MF_CHECKED);
	}
	else
	{
		if (0xFFFFFFFF == ResumeThread(hThreadE[1]))
		{
			wsprintf(message, TEXT("ResumeThread Error %ld"), GetLastError());
			MessageBox(NULL, message, "PaintRectangle Thread", MB_OK | MB_ICONEXCLAMATION);
			LeaveCriticalSection(&csPaintArea);
			return;
		}

		*bSuspend = false;
		//Uncheck 
		//Sets the check-mark attribute to the unchecked state.
		CheckMenuItem(hMenu, IDM_SUSR, MF_UNCHECKED);
	}
	LeaveCriticalSection(&csPaintArea);
}//SuspendRectangle

void SuspendText(HMENU hMenu, bool *bSuspend)
{
	TCHAR message[260];
	EnterCriticalSection(&csPaintArea);
	if (!*bSuspend) {
		if (0xFFFFFFFF == SuspendThread(hThreadE[2]))
		{
			wsprintf(message, TEXT("SuspendThread Error %ld"), GetLastError());
			MessageBox(NULL, message, "PaintText Thread", MB_OK | MB_ICONEXCLAMATION);
			LeaveCriticalSection(&csPaintArea);
			return;
		}

		*bSuspend = true;
		//Check
		//Sets the check-mark attribute to the checked state.
		CheckMenuItem(hMenu, ID_COMMAND_SUSPENDTEXT, MF_CHECKED);
	}
	else
	{
		if (0xFFFFFFFF == ResumeThread(hThreadE[2]))
		{
			wsprintf(message, TEXT("ResumeThread Error %ld"), GetLastError());
			MessageBox(NULL, message, "PaintText Thread", MB_OK | MB_ICONEXCLAMATION);
			LeaveCriticalSection(&csPaintArea);
			return;
		}

		*bSuspend = false;
		//Uncheck 
		//Sets the check-mark attribute to the unchecked state.
		CheckMenuItem(hMenu, ID_COMMAND_SUSPENDTEXT, MF_UNCHECKED);
	}
	LeaveCriticalSection(&csPaintArea);
}//SuspendRectangle


void TerminateEllipse(HWND hWnd, HMENU hMenu, BOOL *fTerminate)
{
	if (!*fTerminate)
	{
		//Check
		//Sets the check-mark attribute to the unchecked state.
		CheckMenuItem(hMenu, IDM_TERME, MF_CHECKED);
		*fTerminate = true;
		if (bSuspendE)
			ResumeThread(hThreadE[0]);

		WaitForSingleObject(hThreadE[0], INFINITE);//Block the primary thread if PaintEllipse
		// is in the suspended state
		if (!CloseHandle(hThreadE[0]))
		{
			MessageBox(NULL, "CloseHandle  failed",
				"PaintEllipse Thread",
				MB_OK | MB_ICONEXCLAMATION);
		};


	}
	else
	{
		//Uncheck
		//Sets the check-mark attribute to the checked state.
		CheckMenuItem(hMenu, IDM_TERME, MF_UNCHECKED);

		*fTerminate = false;

		unsigned ususpend = (bSuspendE) ? CREATE_SUSPENDED : 0;
		hThreadE[0] = (HANDLE)_beginthreadex(NULL,//must be FOR W95
			0,//stack size
			PaintEllipse,
			(void *)hWnd,
			ususpend,//0
			&thridE
		);
		if (!hThreadE[0])
			MessageBox(NULL, "Thread start Error",
				"PaintEllipse Thread",
				MB_OK | MB_ICONEXCLAMATION);

	}
	return;
}

void TerminateText(HWND hWnd, HMENU hMenu, BOOL *fTerminate)
{
	if (!*fTerminate)
	{
		//Check
		//Sets the check-mark attribute to the unchecked state.
		CheckMenuItem(hMenu, IDM_TERMT, MF_CHECKED);
		*fTerminate = true;
		if (bSuspendT)
			ResumeThread(hThreadE[2]);

		WaitForSingleObject(hThreadE[2], INFINITE);

		if (!CloseHandle(hThreadE[2]))
		{
			MessageBox(NULL, "CloseHandle  failed",
				"PaintText Thread",
				MB_OK | MB_ICONEXCLAMATION);
		};


	}
	else
	{
		//Uncheck
		//Sets the check-mark attribute to the checked state.
		CheckMenuItem(hMenu, IDM_TERMT, MF_UNCHECKED);

		*fTerminate = false;

		unsigned ususpend = (bSuspendT) ? CREATE_SUSPENDED : 0;
		hThreadE[2] = (HANDLE)_beginthreadex(NULL,//must be FOR W95
			0,//stack size
			PaintText,
			(void *)hWnd,
			ususpend,//0
			&thridE
		);
		if (!hThreadE[2])MessageBox(NULL, "Thread start Error",
			"PaintText Thread",
			MB_OK | MB_ICONEXCLAMATION);

	}
	return;
}

void TerminateRectangle(HWND hWnd, HMENU hMenu, BOOL *fTerminate)
{
	if (!*fTerminate)
	{
		//Check
		//Sets the check-mark attribute to the unchecked state.
		CheckMenuItem(hMenu, IDM_TERMR, MF_CHECKED);
		*fTerminate = true;
		if (bSuspendR)
			ResumeThread(hThreadE[1]);

		WaitForSingleObject(hThreadE[1], INFINITE);

		if (!CloseHandle(hThreadE[1]))
		{
			MessageBox(NULL, "CloseHandle  failed",
				"PaintText Thread",
				MB_OK | MB_ICONEXCLAMATION);
		};


	}
	else
	{
		//Uncheck
		//Sets the check-mark attribute to the checked state.
		CheckMenuItem(hMenu, IDM_TERMR, MF_UNCHECKED);

		*fTerminate = false;

		unsigned ususpend = (bSuspendR) ? CREATE_SUSPENDED : 0;
		hThreadE[1] = (HANDLE)_beginthreadex(NULL,//must be FOR W95
			0,//stack size
			PaintRectangle,
			(void *)hWnd,
			ususpend,//0
			&thridE
		);
		if (!hThreadE[1])MessageBox(NULL, "Thread start Error",
			"PaintText Thread",
			MB_OK | MB_ICONEXCLAMATION);

	}
	return;
}

//Dialog Box Function
//_stdcall for CALLBACK (see Windef.h)
LRESULT CALLBACK ChangeThreadPriority_Box(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		RHANDLE_MSG(hDlg, WM_INITDIALOG, ChThPr_OnInitDialog);
		RHANDLE_MSG(hDlg, WM_COMMAND, ChThPr_OnCommand);
		//return true; for all handled messages
	default:
		return FALSE;//not handled messages	
	}
}//ChangeThreadPriority_Box


LONG ChThPr_OnCommand(HWND hDlg, int id, HWND hwndCtl, UINT codeNotify)
{
	// Parse the Change Thread Priority Box commands:
	switch (id)
	{
	case IDOK:
	{
		int nPriorityEll = THREAD_PRIORITY_NORMAL;
		int nIDCheckButton = IDC_RADIO_NORMAL, i;
		for (i = 0; i < 7; i++)
			if (BST_CHECKED == IsDlgButtonChecked(hDlg, IDC_RADIO_TMCRITICAL + i))
			{
				nIDCheckButton = IDC_RADIO_TMCRITICAL + i;
				break;
			}
		switch (nIDCheckButton)
		{
		case IDC_RADIO_TMCRITICAL:
			nPriorityEll = THREAD_PRIORITY_TIME_CRITICAL;
			break;
		case IDC_RADIO_HGHST:
			nPriorityEll = THREAD_PRIORITY_HIGHEST;
			break;
		case IDC_RADIO_ABOVE:
			nPriorityEll = THREAD_PRIORITY_ABOVE_NORMAL;
			break;
		case IDC_RADIO_NORMAL:
			nPriorityEll = THREAD_PRIORITY_NORMAL;
			break;
		case IDC_RADIO_BELOW:
			nPriorityEll = THREAD_PRIORITY_BELOW_NORMAL;
			break;
		case IDC_RADIO_LOWEST:
			nPriorityEll = THREAD_PRIORITY_LOWEST;
			break;
		case IDC_RADIO_IDLE:
			nPriorityEll = THREAD_PRIORITY_NORMAL;
			break;
		default:
			break;
		}
		SetThreadPriority(hThreadE[0], nPriorityEll);
	}

	case IDCANCEL:
		EndDialog(hDlg, id);
		return TRUE;//handled
	default:
		return TRUE;

	}//return TRUE for all handled commands,else ones are not here
}

BOOL ChThPr_OnInitDialog(HWND hDlg, HWND hwndFocus, LPARAM lParam)
{
	//Set Current Priority Class and Thread Priority

	int nPriorityEll = GetThreadPriority(hThreadE[0]);
	int nIDCheckButton;

	switch (nPriorityEll)
	{
	case THREAD_PRIORITY_TIME_CRITICAL:
		nIDCheckButton = IDC_RADIO_TMCRITICAL;
		break;
	case THREAD_PRIORITY_HIGHEST:
		nIDCheckButton = IDC_RADIO_HGHST;
		break;
	case THREAD_PRIORITY_ABOVE_NORMAL:
		nIDCheckButton = IDC_RADIO_ABOVE;
		break;
	case THREAD_PRIORITY_NORMAL:
		nIDCheckButton = IDC_RADIO_NORMAL;
		break;
	case THREAD_PRIORITY_BELOW_NORMAL:
		nIDCheckButton = IDC_RADIO_BELOW;
		break;
	case THREAD_PRIORITY_LOWEST:
		nIDCheckButton = IDC_RADIO_LOWEST;
		break;
	case THREAD_PRIORITY_IDLE:
		nIDCheckButton = IDC_RADIO_IDLE;
		break;
	default:
		break;
	}
	CheckRadioButton(hDlg,          // handle to dialog box
		IDC_RADIO_TMCRITICAL, // identifier of first radio button in group
		IDC_RADIO_IDLE,  // identifier of last radio button in group
		nIDCheckButton  // identifier of radio button to select
	);

	/////////////CheckDlgButton(hwnd,IDC_RADIO_DIRECT,bDirection);
	DWORD fdwPrClass = GetPriorityClass(GetCurrentProcess());
	TCHAR szPrClass[100];
	switch (fdwPrClass)
	{
	case IDLE_PRIORITY_CLASS:
		wsprintf(szPrClass, TEXT("%s"), TEXT("IDLE_PRIORITY_CLASS"));
		break;
		//	case BELOW_NORMAL_PRIORITY_CLASS:
		//		wsprintf(szPrClass,TEXT("%s"),TEXT("BELOW_NORMAL_PRIORITY_CLASS"));
		//		break;
	case NORMAL_PRIORITY_CLASS:
		wsprintf(szPrClass, TEXT("%s"), TEXT("NORMAL_PRIORITY_CLASS"));
		break;
		//	case ABOVE_NORMAL_PRIORITY_CLASS:
		//		wsprintf(szPrClass,TEXT("%s"),TEXT("ABOVE_NORMAL_PRIORITY_CLASS"));
		//		break;
	case HIGH_PRIORITY_CLASS:
		wsprintf(szPrClass, TEXT("%s"), TEXT("HIGH_PRIORITY_CLASS"));
		break;
	case REALTIME_PRIORITY_CLASS:
		wsprintf(szPrClass, TEXT("%s"), TEXT("REALTIME_PRIORITY_CLASS"));
		break;
	default:
		break;
	}

	SendDlgItemMessage(hDlg, IDC_STATIC_PR_CL, WM_SETTEXT, 0, (LPARAM)szPrClass);//EM_REPLACESEL

	return TRUE;//handled
}


