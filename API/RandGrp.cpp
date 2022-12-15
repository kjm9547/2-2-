#include <windows.h>
#include<tchar.h>


LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);
HINSTANCE g_hInst;
HWND hWndMain;
LPCTSTR lpszClass=TEXT("RaceMutex");
LPCTSTR tc = TEXT("고양이");

int APIENTRY WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance
	  ,LPSTR lpszCmdParam,int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst=hInstance;

	WndClass.cbClsExtra=0;
	WndClass.cbWndExtra=0;
	WndClass.hbrBackground=(HBRUSH)(COLOR_WINDOW+1);
	WndClass.hCursor=LoadCursor(NULL,IDC_ARROW);
	WndClass.hIcon=LoadIcon(NULL,IDI_APPLICATION);
	WndClass.hInstance=hInstance;
	WndClass.lpfnWndProc=WndProc;
	WndClass.lpszClassName=lpszClass;
	WndClass.lpszMenuName=NULL;
	WndClass.style=CS_HREDRAW | CS_VREDRAW;
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

int X;
int r = 0;

HANDLE hMutex;
DWORD WINAPI ThreadFunc1(LPVOID Param)
{
	TCHAR c[100];
	HDC hdc;
	hdc=GetDC(hWndMain);
	for (int i=0;i<100;i++) {
		WaitForSingleObject(hMutex, INFINITE);
		X=100;
		Sleep(10);
		TextOut(hdc,X,100, _itoa(i, c, 10),5);
		r++;
		ReleaseMutex(hMutex);
	}
	
	ReleaseDC(hWndMain, hdc);
	return 0;
}
/*
************************************************************************************************************************************
		c = TCHAR형 배열
		wsprintf(c, TEXT("%d 야옹"), i);//버퍼에 넣고
		c에 "%d 야옹"을 할당 이 때 %d는 i를 출력 함 i는 int형 변수
		TextOut(hdc, 400, 200, c, lstrlen(c));//포지션 지정해서 출력
		hdc = window 
		400 = x포지션 값	200 = y 포지션 값	c배열에 있는값을 불러옴 lstrlen(c)길이는 c만큼
		
		
		CreateMutext(NULL, FALSE, NULL);

		CreateThread(NULL, 0, 스레드가 실행 시킬 함수 , 실행되는 함수에 넘겨지는 매개변수 (스레드에서 사용될 값 넘겨준다 생각?), 0, &ThreadID)

		뮤텍스??
		여러 개의 스레드가 공유 데이터(전역 변수)에 접근 할 때 순서대로 지정해주기 위해서 사용
		WaitForSingleObject(hMutex,INFINITE) hMutex에 뮤텍스 소유권을 INFINITE만큼 시간 할당
		이후 사용을 하고  RelaseMutex()로 뮤텍스 소유권을 해제 >> 해제 시 대기 중인 다음 스레드 실행

		오류 해결 
		
		_CRT_SECURE_NO_WARNINGS
		프로젝트 속성 -> c/c++ -> 전처리기 -> 편집 ->  전처리기 정의에 _CRT_SECURE_NO_WARNINGS 복사해서 추가
	
		
		
************************************************************************************************************************************
*/



DWORD WINAPI ThreadFunc2(LPVOID Param)
{
	
	HDC hdc;
	TCHAR c[1000];
	//TCHAR
	hdc=GetDC(hWndMain);
	for (int i=0;i<162;i++) {
		WaitForSingleObject(hMutex, INFINITE);
		X=200;
		Sleep(10);
		wsprintf(c, TEXT("%d 야옹"), i);//버퍼에 넣고
		TextOut(hdc, 400, 200, c, lstrlen(c));//포지션 지정해서 출력
		//TextOut(hdc,400,200,_itoa(i,c,10), 5);
		//TextOut(hdc, 400, 200, "야옹", 3);
		//_itoa(value,buffer,10진수)
		//CreateMutext() 보안(NULL)//초기 뮤텍스를 점유할 것인가(true 생성한거 점유, 다른 데서 쓸라면 릴리즈Mutex()함수,false==생성만)//뮤텍스의 이름 지정
		//CreateThread( )스레드 커널 오브젝트 보안 특성 기본 NULL// 스레드 스택 크기 디폴트 0//실행되는 함수//실행되는 함수에 넘겨지는 매개변수// 스레드를 제어하는 플래그// 스레드의 ID값
		ReleaseMutex(hMutex);//뮤텍스 소유권 해제
		r++;
	}
	
	ReleaseDC(hWndMain, hdc);
	return 0;
}
#define ID_PAUSE 104
LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
{ 
	DWORD ThreadID;
	HANDLE hThread;

	switch (iMessage) {
	case WM_CREATE:
		hMutex=CreateMutex(NULL, FALSE, NULL);
		hWndMain=hWnd;
		CreateWindow("button", "중지", BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE,
			200, 100, 80, 25, hWnd, (HMENU)ID_PAUSE, g_hInst, NULL);
		return 0;
	case WM_LBUTTONDOWN:
		hThread=CreateThread(NULL, 0, ThreadFunc1, NULL, 0, &ThreadID);
		CloseHandle(hThread);
		hThread=CreateThread(NULL, 0, ThreadFunc2, NULL, 0, &ThreadID);
		CloseHandle(hThread);
		return 0;
	case WM_DESTROY:
		CloseHandle(hMutex);
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd,iMessage,wParam,lParam));
}
