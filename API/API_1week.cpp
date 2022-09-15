#include <windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
HWND hWndMain;
LPCTSTR lpszClass = TEXT("Class");

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance
	, LPSTR lpszCmdParam, int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst = hInstance;

	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = WndProc;
	WndClass.lpszClassName = lpszClass;
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&WndClass);

	hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);
	//Message loop
	while (GetMessage(&Message, NULL, 0, 0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return (int)Message.wParam;
}

//화면 다시 그리기  <-- 프로그래머책임
//os는?? 다시 그려야 할 시점을 알려준다..WM_PAINT massage로
//int px[1000], py[1000];
int iCount;
//전역변수로 설정한 이유 -> 지역변수로 설정 시 블록 종료 시 메모리에서 사라지기 때문에
//-> 블록이 끝나면 사라지는데 다시 시작하면 다시 쓰레기값이 들어감, 앞의 내용이 없어짐
//iCount를 초기화 안한 이유->전역변수는 최초에 초기화 되어있다. 

//우클릭은 빨강 좌클릭은 파랑값으로 만들기
typedef struct tagmyPOINT
{
	LONG x;
	LONG y;
	int iBrushColor; //0=red, 1=blue
}myPOINT;
myPOINT pt[1000];


LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	int x, y;
	HBRUSH hBrush;
	switch (iMessage) {
	case WM_CREATE:
		hWndMain = hWnd;
		return 0;
	
	/*case WM_LBUTTONDOWN:
	// =case 0x0201:
		hdc = GetDC(hWnd);  

		//빨간 브러쉬
		hBrush = CreateSolidBrush(RGB(255, 0, 0));
		SelectObject(hdc, hBrush);
		//빨간 브러쉬
		//로컬로 있기때문에 창을 내렸다 올리면 날아감 -> 아래에도 추가

		//핸들(변수)
		//hwnd 윈도우에 포함되어있는 도구상자(의 핸들)를 달라
		//DC=DeviceContext (현재 윈도우에 포함되어있는 그리기 도구상자)
		//모든 그리기 API호출 시 DC를넘겨주어야 한다.
		x = LOWORD(lParam);  //macro
		//x = (WORD)(lParam);  ()=캐스팅 32비트 정수를 16비트로 처리 / 앞의 16비트를 날림
		//macro 정의로 이동하면 확인가능, 컴파일 시 전처리기로 자동으로 처리
		// LOWORD = WORD = unsigned short
		//x = (unsigned short)(lParam); //16비트 정수
		y = HIWORD(lParam);
		//y = (unsigned short)((lParam)>>16);
		                     //c의 bitwise operator, operation (16비트 밀어냄) >> : shift 미는 것
		//y = ((lParam) >> 16); //32비트 데이터의 앞 16비트가 0으로 되어 캐스팅이 필요없음

		//px[iCount] = x;
		//py[iCount] = y;
		iCount++;

		Rectangle(hdc, x-30, y-30, x+30, y+30);  
		//Rectangle 같이 대문자로 시작하면 윈도우가 처리하는 함수
		return 0;  //return -> WMLBUTTONDOWN 처리 끝 -> WndProc() 종료*/
	
	case WM_LBUTTONDOWN:
		hdc = GetDC(hWnd);

		hBrush = CreateSolidBrush(RGB(255, 0, 0));
		SelectObject(hdc, hBrush);

		x = LOWORD(lParam);
		y = HIWORD(lParam);

		pt[iCount].x = x;
		pt[iCount].y = y;
		pt[iCount].iBrushColor = 0;

		iCount++;

		Rectangle(hdc, x - 30, y - 30, x + 30, y + 30);
		return 0;

	case WM_RBUTTONDOWN:
		hdc = GetDC(hWnd);

		hBrush = CreateSolidBrush(RGB(0, 0, 255));
		SelectObject(hdc, hBrush);

		x = LOWORD(lParam);
		y = HIWORD(lParam);

		pt[iCount].x = x;
		pt[iCount].y = y;
		pt[iCount].iBrushColor = 1;

		iCount++;

		Rectangle(hdc, x - 30, y - 30, x + 30, y + 30);
		return 0;
	
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		//저장 위치
		
		//여기에 추가하면 남아있음
		
		//여기
		
		/*for (int i = 0; i < iCount; i++)
		{
			Rectangle(hdc, px[i] - 30, py[i] - 30, px[i] + 30, py[i] + 30);
		}*/

		EndPaint(hWnd, &ps);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}
