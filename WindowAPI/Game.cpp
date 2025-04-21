#include "pch.h"
#include "Game.h"
#include "TimeManager.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "ResourceManager.h"

Game::Game()
{
}

Game::~Game()
{
	GET_SINGLE(SceneManager)->Clear();
	GET_SINGLE(ResourceManager)->Clear();

	_CrtDumpMemoryLeaks(); // Memory Leak Check
}

void Game::Init(HWND hwnd)
{
	_hwnd = hwnd;
	_hdc = GetDC(hwnd);

	::GetClientRect(_hwnd, &_rect);

	_hdcBack = ::CreateCompatibleDC(_hdc); // _hdc와 호환되는 DC를 생성
	_bmpBack = ::CreateCompatibleBitmap(_hdc, _rect.right, _rect.bottom); // _hdc와 호환되는 Bitmap 생성
	HBITMAP prev = (HBITMAP)::SelectObject(_hdcBack, _bmpBack); // DC와 BMP를 연결 (이전에 사용한 BMP 반환)
	::DeleteObject(prev); // 이전에 사용한 BMP 삭제

	GET_SINGLE(TimeManager)->Init();
	GET_SINGLE(InputManager)->Init(hwnd);
	GET_SINGLE(SceneManager)->Init();
	GET_SINGLE(ResourceManager)->Init(hwnd, fs::path(L"C:\\Users\\jinhy\\Desktop\\C++\\게임 프로그래머 입문 올인원\\복습\\WindowAPI\\Resources"));

	GET_SINGLE(SceneManager)->ChangeScene(SceneType::DevScene);
}

void Game::Update()
{
	GET_SINGLE(TimeManager)->Update();
	GET_SINGLE(InputManager)->Update();
	GET_SINGLE(SceneManager)->Update();
}

void Game::Render()
{
	uint32 fps = GET_SINGLE(TimeManager)->GetFps();
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();

	GET_SINGLE(SceneManager)->Render(_hdcBack);

	{
		POINT mousePos = GET_SINGLE(InputManager)->GetMousePos();
		wstring str = std::format(L"Mouse({0}),({1})", mousePos.x, mousePos.y);
		::TextOut(_hdcBack, 20, 10, str.c_str(), static_cast<int32>(str.size()));
	}

	{
		wstring str = std::format(L"FPS({0}), DT({1} ms)", fps, static_cast<int32>(deltaTime));
		::TextOut(_hdcBack, 650, 10, str.c_str(), static_cast<int32>(str.size()));
	}


	// Double Buffering
	::BitBlt(_hdc, 0, 0, _rect.right, _rect.bottom, _hdcBack, 0, 0, SRCCOPY); // 비트 블릿 : 고속 복사
	::PatBlt(_hdcBack, 0, 0, _rect.right, _rect.bottom, WHITENESS); // 그려준 화면을 하얀색으로 리셋
}
