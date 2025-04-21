#include "pch.h"
#include "UI.h"
#include "InputManager.h"

UI::UI()
{
}

UI::~UI()
{
}

void UI::BeginPlay()
{
}

void UI::Tick()
{
}

void UI::Render(HDC hdc)
{
}

RECT UI::GetRect()
{
	RECT rect =
	{
		_pos.x - _size.x / 2,
		_pos.y - _size.y / 2,
		_pos.x + _size.x / 2,
		_pos.y + _size.y / 2,
	};

	return rect;
}

bool UI::IsMouseInRect()
{
	RECT rect = GetRect();

	POINT mousePos = GET_SINGLE(InputManager)->GetMousePos();

	// 1) 메서드 이용해서 반환
	//return ::PtInRect(&rect, mousePos); 

	// 2) 직접 구해주기
	if (mousePos.x < rect.left) return false;
	if (rect.right < mousePos.x) return false;
	if (mousePos.y < rect.top) return false;
	if (rect.bottom < mousePos.y) return false;
	return true;

}
