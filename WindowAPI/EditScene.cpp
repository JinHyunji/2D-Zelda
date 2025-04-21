#include "pch.h"
#include "EditScene.h"
#include "InputManager.h"
#include "Utils.h"
#include <fstream>

EditScene::EditScene()
{
}

EditScene::~EditScene()
{
}

void EditScene::Init()
{
}

void EditScene::Update()
{
	if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::LeftMouse))
	{
		POINT mousePos = GET_SINGLE(InputManager)->GetMousePos();

		if (_setOrigin)
		{
			_lastPos = mousePos;
			_setOrigin = false;
		}
		else
		{
			_lines.push_back(make_pair(_lastPos, mousePos));
			_lastPos = mousePos;
		}
	}

	if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::RightMouse))
		_setOrigin = true;

	// Save
	if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::S))
	{
		wofstream file;
		file.open(L"Unit.txt"); // 파일 이름 저장

		int32 minX = INT32_MAX;
		int32 maxX = INT32_MIN;
		int32 minY = INT32_MAX;
		int32 maxY = INT32_MIN;

		for (auto& line : _lines)
		{
			POINT from = line.first;
			POINT to = line.second;

			minX = min(min(minX, from.x), to.x);
			maxX = max(max(maxX, from.x), to.x);
			minY = min(min(minY, from.y), to.y);
			maxY = max(max(maxY, from.y), to.y);
		}

		int32 midX = (maxX + minX) / 2;
		int32 midY = (maxY + minY) / 2;

		// 라인 개수
		file << static_cast<int32>(_lines.size()) << endl;

		// 파일 입출력
		for (auto& line : _lines)
		{
			POINT from = line.first;
			from.x -= midX;
			from.y -= midY;

			POINT to = line.second;
			to.x -= midX;
			to.y -= midY;

			wstring str = std::format(L"({0},{1})->({2},{3})", from.x, from.y, to.x, to.y);
			file << str << endl;
		}
		
		file.close();
	}

	// Load
	if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::D))
	{
		wifstream file;
		file.open(L"Unit.txt");

		// 라인 개수
		int32 count;
		file >> count;

		_lines.clear();

		int32 midX = 400;
		int32 midY = 300;

		for (int32 i = 0; i < count; i++)
		{
			POINT p1;
			POINT p2;

			wstring str;
			file >> str;
			::swscanf_s(str.c_str(), L"(%d,%d)->(%d,%d)", &p1.x, &p1.y, &p2.x, &p2.y); // POINT에 저장

			p1.x += midX;
			p1.y += midY;
			p2.x += midX;
			p2.y += midY;

			_lines.push_back(make_pair(p1, p2));
			_setOrigin = true;
		}

		file.close();
	}
}

void EditScene::Render(HDC hdc)
{
	for (auto& line : _lines)
	{
		POINT p1 = line.first;
		POINT p2 = line.second;

		Pos pos1;
		pos1.x = (float)p1.x;
		pos1.y = (float)p1.y;

		Pos pos2;
		pos2.x = (float)p2.x;
		pos2.y = (float)p2.y;

		Utils::DrawLine(hdc, pos1, pos2);
	}
}
