#pragma once
class Utils
{
public:
	static void DrawText(HDC hdc, Pos pos, const wstring& str);
	static void DrawRect(HDC hdc, Pos pos, int32 width, int32 height);
	static void DrawCircle(HDC hdc, Pos pos, int32 radius);
	static void DrawLine(HDC hdc, Pos from, Pos to);
};