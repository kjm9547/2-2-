#include <windows.h>
#include "resource.h"

LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass=TEXT("Mouse");

int APIENTRY WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance
		  ,LPSTR lpszCmdParam,int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst=hInstance;
	
	WndClass.cbClsExtra=0;
	WndClass.cbWndExtra=0;
	WndClass.hbrBackground=(HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.hCursor=LoadCursor(NULL,IDC_ARROW);
	WndClass.hIcon=LoadIcon(NULL,IDI_APPLICATION);
	WndClass.hInstance=hInstance;
	WndClass.lpfnWndProc=WndProc;
	WndClass.lpszClassName=lpszClass;
	WndClass.lpszMenuName=MAKEINTRESOURCE(IDR_MENU1);
	WndClass.style=CS_HREDRAW | CS_VREDRAW;// | CS_DBLCLKS;
	RegisterClass(&WndClass);

	hWnd=CreateWindow(lpszClass,lpszClass,WS_OVERLAPPEDWINDOW,
		  CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,
		  NULL,(HMENU)NULL,hInstance,NULL);
	ShowWindow(hWnd,nCmdShow);
	
	while (GetMessage(&Message,NULL,0,0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return (int)Message.wParam;
}

typedef struct tagmyline
{
	POINT p[3000];
	int iCount; //한개 선내에서의 점개수
	COLORREF iPenColor;
} line;

line lines[1000];
int iLines; //윈도우 전체에서 선개수 

COLORREF iCurrentPenColor = RGB(255,0,0);   //

//int iTempCount; // 임시로 한개 선내에서의 점개수를 카운트...

LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
{
	HDC hdc;
	static int x;
	static int y;
	//static BOOL bNowDraw=FALSE;

	PAINTSTRUCT ps;
	HPEN hPen;

	switch (iMessage) {
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case ID_RED:
			iCurrentPenColor = RGB(255, 0, 0);
			break;
		case ID_GREEN:
			iCurrentPenColor = RGB(0, 255, 0);
			break;
		case ID_BLUE:
			iCurrentPenColor = RGB(0, 0, 255);
			break;
		}
		return 0;

	case WM_KEYDOWN:
		switch (wParam) {
		case VK_BACK:
			if (iLines > 0){
				iLines--;
				InvalidateRect(hWnd, NULL, TRUE);
			}
			break;
		}
		return 0;

	case WM_LBUTTONDOWN:
		x=LOWORD(lParam);
		y=HIWORD(lParam);
	//	bNowDraw=TRUE;
		lines[iLines].iPenColor = iCurrentPenColor;
		lines[iLines].iCount = 0;
		lines[iLines].p[lines[iLines].iCount].x = x;
		lines[iLines].p[lines[iLines].iCount].y = y;
		lines[iLines].iCount++;
		return 0;

	case WM_MOUSEMOVE:  //p.92
		if (wParam & MK_LBUTTON) { //bitwise operator
			//왼쪽버튼을 누른상태로 움직이면...
			hdc=GetDC(hWnd);
			hPen = CreatePen(PS_SOLID, 3, iCurrentPenColor);
			SelectObject(hdc, hPen);
			MoveToEx(hdc,x,y,NULL);  
			//DC에 들어가 있는 펜을 가져와서 x,y 지점으로..
			x=LOWORD(lParam);
			y=HIWORD(lParam);
			LineTo(hdc,x,y); //x,y 지점까지 선긋기...
			ReleaseDC(hWnd,hdc); //반납
			lines[iLines].p[lines[iLines].iCount].x = x;
			lines[iLines].p[lines[iLines].iCount].y = y;
			lines[iLines].iCount++;
		}
		return 0;
	case WM_LBUTTONUP:
		// 한개 선객체의 완성
	//	bNowDraw=FALSE;
		//lines[iLines].iCount=iTempCount;
		//iTempCount = 0;
		iLines++;
		return 0;
	case WM_LBUTTONDBLCLK:
		InvalidateRect(hWnd, NULL, TRUE);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		for (int i = 0; i < iLines; i++)
		{
			hPen = CreatePen(PS_SOLID, 3, lines[i].iPenColor);
			hPen = (HPEN)SelectObject(hdc, hPen);

			MoveToEx(hdc, lines[i].p[0].x,
				lines[i].p[0].y, NULL);
			for (int j = 1; j < lines[i].iCount; j++)
			{
				LineTo(hdc, lines[i].p[j].x,
					lines[i].p[j].y);
			}
			DeleteObject(SelectObject(hdc, hPen)); //삭제
		}
		EndPaint(hWnd, &ps);
		return 0;
	}
	return(DefWindowProc(hWnd,iMessage,wParam,lParam));
}
