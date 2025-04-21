#include "pch.h"
#include "TimeManager.h"

void TimeManager::Init()
{
	LARGE_INTEGER frequency;
	LARGE_INTEGER prevCount;

	::QueryPerformanceFrequency(&frequency);
	::QueryPerformanceCounter(&prevCount); // CPU 클럭

	_frequency = static_cast<uint64>(frequency.QuadPart); // QuadPart 사용
	_prevCount = static_cast<uint64>(prevCount.QuadPart);

	/*::QueryPerformanceFrequency(reinterpret_cast<LARGE_INTEGER>(& _frequency));
	::QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER>(&_prevCount));*/
}

void TimeManager::Update()
{
	LARGE_INTEGER currentCount;
	::QueryPerformanceCounter(&currentCount);

	_deltaTime = (static_cast<float>(currentCount.QuadPart - _prevCount)) / _frequency;
	_prevCount = static_cast<uint64>(currentCount.QuadPart);

	_frameCount++;
	_frameTime += _deltaTime;

	if (_frameTime >= 1.f)
	{
		_fps = static_cast<uint32>(_frameCount / _frameTime);

		_frameTime = 0.f;
		_frameCount = 0;
	}
}
