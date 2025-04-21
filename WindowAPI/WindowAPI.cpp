// WindowAPI.cpp : 애플리케이션에 대한 진입점을 정의합니다.

#include "pch.h"
#include "framework.h"
#include "WindowAPI.h"
#include "Game.h"

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;
HWND hWnd;

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);

// 메인 함수
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	// 1) 윈도우 창 정보 등록
	MyRegisterClass(hInstance);

	// 2) 윈도우 창 생성
	if (!InitInstance(hInstance, nCmdShow))
		return FALSE;

	Game game;
	game.Init(hWnd);

	MSG msg = {};
	uint64 preTick = 0;

	// 3) 메인 루프
	while (msg.message != WM_QUIT)
	{
		if (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) // message가 있는지 확인하는 코드
		{
			::TranslateMessage(&msg);
			::DispatchMessage(&msg);
		}
		else
		{
			uint64 now = ::GetTickCount64();

			//if (now - preTick >= 10)
			{
				// 게임
				game.Update();
				game.Render();

				preTick = now;
			}
		}
	}

	return (int)msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc; // 콜백 함수
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDOWAPI));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	//wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WINDOWAPI); // 메뉴 (파일, 도움말) 
	wcex.lpszMenuName = nullptr;
	wcex.lpszClassName = L"WindowAPI";
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

	RECT windowRect = { 0, 0, 800, 600 };
	AdjustWindowRect(&windowRect, WS_OVERLAPPEDWINDOW, false); // 내부 창 크기를 지정해준 크기로 조정(메뉴바 제외)

	hWnd = CreateWindowW(L"WindowAPI", L"Hello!", WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, windowRect.right - windowRect.left, windowRect.bottom - windowRect.top, nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)
	{
		return FALSE;
	}

	::ShowWindow(hWnd, nCmdShow);
	::UpdateWindow(hWnd);

	return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) // 콜백 함수 (메세지 처리)
{
	switch (message)
	{
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// 메뉴 선택을 구문 분석합니다:
		switch (wmId)
		{
			/*case IDM_ABOUT:
				DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
				break;*/
		case IDM_EXIT:
			::DestroyWindow(hWnd);
			break;
		default:
			return ::DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;
	case WM_PAINT: // 그리는 것과 관련있는 핵심 이벤트 -> 화면이 움직이거나 수정할 때만 갱신됨 -> 게임을 만들기 위해서는 매 프레임마다 갱신되어야 함.
	{
		PAINTSTRUCT ps;
		HDC hdc = ::BeginPaint(hWnd, &ps); // HDC : 정수가 들어있는 define 코드 (식별 번호) -> 여기에다가 그리면 됨(도화지)

		::EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
		::PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
