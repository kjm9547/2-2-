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

//ȭ�� �ٽ� �׸���  <-- ���α׷���å��
//os��?? �ٽ� �׷��� �� ������ �˷��ش�..WM_PAINT massage��
//int px[1000], py[1000];
int iCount;
//���������� ������ ���� -> ���������� ���� �� ��� ���� �� �޸𸮿��� ������� ������
//-> ����� ������ ������µ� �ٽ� �����ϸ� �ٽ� �����Ⱚ�� ��, ���� ������ ������
//iCount�� �ʱ�ȭ ���� ����->���������� ���ʿ� �ʱ�ȭ �Ǿ��ִ�. 

//��Ŭ���� ���� ��Ŭ���� �Ķ������� �����
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

		//���� �귯��
		hBrush = CreateSolidBrush(RGB(255, 0, 0));
		SelectObject(hdc, hBrush);
		//���� �귯��
		//���÷� �ֱ⶧���� â�� ���ȴ� �ø��� ���ư� -> �Ʒ����� �߰�

		//�ڵ�(����)
		//hwnd �����쿡 ���ԵǾ��ִ� ��������(�� �ڵ�)�� �޶�
		//DC=DeviceContext (���� �����쿡 ���ԵǾ��ִ� �׸��� ��������)
		//��� �׸��� APIȣ�� �� DC���Ѱ��־�� �Ѵ�.
		x = LOWORD(lParam);  //macro
		//x = (WORD)(lParam);  ()=ĳ���� 32��Ʈ ������ 16��Ʈ�� ó�� / ���� 16��Ʈ�� ����
		//macro ���Ƿ� �̵��ϸ� Ȯ�ΰ���, ������ �� ��ó����� �ڵ����� ó��
		// LOWORD = WORD = unsigned short
		//x = (unsigned short)(lParam); //16��Ʈ ����
		y = HIWORD(lParam);
		//y = (unsigned short)((lParam)>>16);
		                     //c�� bitwise operator, operation (16��Ʈ �о) >> : shift �̴� ��
		//y = ((lParam) >> 16); //32��Ʈ �������� �� 16��Ʈ�� 0���� �Ǿ� ĳ������ �ʿ����

		//px[iCount] = x;
		//py[iCount] = y;
		iCount++;

		Rectangle(hdc, x-30, y-30, x+30, y+30);  
		//Rectangle ���� �빮�ڷ� �����ϸ� �����찡 ó���ϴ� �Լ�
		return 0;  //return -> WMLBUTTONDOWN ó�� �� -> WndProc() ����*/
	
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
		//���� ��ġ
		
		//���⿡ �߰��ϸ� ��������
		
		//����
		
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
