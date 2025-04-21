#include "pch.h"
#include "Utils.h"

void Utils::DrawText(HDC hdc, Pos pos, const wstring& str)
{
	::TextOut(hdc, static_cast<int32>(pos.x), static_cast<int32>(pos.y), str.c_str(), static_cast<int32>(str.size()));
}

void Utils::DrawRect(HDC hdc, Pos pos, int32 width, int32 height)
{
	::Rectangle(hdc, static_cast<int32>(pos.x - width / 2), static_cast<int32>(pos.y - height / 2), static_cast<int32>(pos.x + width / 2), static_cast<int32>(pos.y + height / 2));
}

void Utils::DrawCircle(HDC hdc, Pos pos, int32 radius)
{
	::Ellipse(hdc, static_cast<int32>(pos.x - radius), static_cast<int32>(pos.y - radius), static_cast<int32>(pos.x + radius), static_cast<int32>(pos.y + radius));
}

void Utils::DrawLine(HDC hdc, Pos from, Pos to)
{
	::MoveToEx(hdc, static_cast<int32>(from.x), static_cast<int32>(from.y), nullptr);
	::LineTo(hdc, static_cast<int32>(to.x), static_cast<int32>(to.y));
}

