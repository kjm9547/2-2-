#include <windows.h>

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
	WndClass.lpszMenuName=NULL;
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

/*POINT{
	int x;
	int y;
}*/
typedef struct _line{//구조체 이름
	POINT p[500]; //p[j].x /p[j].y 포인트 구조체에 변수 x y 보유
	int iCount;//한 개의 선내에서의 점개수

}line;//구조체 별칭

line lines[1000];
int iLines;//윈도우 전체의 선 개수
int iTempCount; //선내의 점 갯수 파악

LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
{
	HDC hdc;
	static int x;
	static int y;
	HPEN hPen;
	PAINTSTRUCT ps;
	//static BOOL bNowDraw=FALSE;

	switch (iMessage) {
	case WM_LBUTTONDOWN:
		x = LOWORD(lParam);
		y = HIWORD(lParam);
		//	bNowDraw=TRUE;
		lines[iLines].p[0].x = x;
		lines[iLines].p[0].y = y;

		return 0;
	case WM_MOUSEMOVE://대문자로 구성 = 메크로

		if (wParam & MK_LBUTTON) {//왼쪽 버튼을 누른상태로
			hdc = GetDC(hWnd);
			hPen = CreatePen(PS_SOLID, 3, RGB(255, 0, 0));
			hPen = (HPEN)SelectObject(hdc, hPen);

			MoveToEx(hdc, x, y, NULL);//pen을 x,y 위치로 
			x = LOWORD(lParam);//x의 값
			y = HIWORD(lParam);//y의 값
			LineTo(hdc, x, y);//x,y지점까지 선을 그려라
			ReleaseDC(hWnd, hdc);//반납
			/*lines[iLines].p[lines[iLines].iCount].x = x;
			lines[iLines].p[lines[iLines].iCount].y = y;
			lines[iLines].iCount++;

			*/
			lines[iLines].p[iTempCount].x = x;
			lines[iLines].p[iTempCount].y = y;

			iTempCount++;
		}
		
		return 0;
	case WM_LBUTTONUP:
	//	bNowDraw=FALSE;
		lines[iLines].iCount = iTempCount;
		iTempCount = 0;
		iLines++;
		return 0;
	/*case WM_PAINT:
		hdc = GetDC(hWnd);
		for (int i = 0; i < iLines; i++){
			MoveToEx(hdc, lines[i].p[0].x, lines[i].p[0].y, NULL);
			for (int j = 0; j < lines[i].iCount; j++){
				LineTo(hdc, lines[i].p[j].x, lines[i].p[j].y);
			}
		}
		ReleaseDC(hWnd, hdc);
		return 0;*/

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		
		for (int i = 0; i < iLines; i++){
			//내가 만든 그리기 객체(펜) 사용 후 삭제..생성자 소멸자개념?
			//단 선택해제 후 삭제,
			hPen = CreatePen(PS_SOLID, 3, RGB(255, 0, 0));
			hPen = (HPEN)SelectObject(hdc, hPen);

			
			MoveToEx(hdc, lines[i].p[0].x,
				lines[i].p[0].y, NULL);//pen을 x,y 위치로 

			for (int j = 0; j < lines[i].iCount-1; j++){
				LineTo(hdc, lines[i].p[j + 1].x, lines[i].p[j+1].y);
			}
			
			DeleteObject(SelectObject(hdc, hPen));
		}
		EndPaint(hWnd, &ps);
		
		
		return 0;
	case WM_LBUTTONDBLCLK:
		InvalidateRect(hWnd, NULL, TRUE);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd,iMessage,wParam,lParam));
}
