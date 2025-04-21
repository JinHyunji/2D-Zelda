#pragma once
#include "Creature.h"

class Player;

class Monster : public Creature
{
	using Super = Creature;

public:
	Monster();
	virtual ~Monster() override;

	virtual void BeginPlay() override;
	virtual void Tick() override;
	virtual void Render(HDC hdc) override;

protected:
	virtual void TickIdle() override;
	virtual void TickMove() override;
	virtual void TickSkill() override;
	virtual void UpdateAnimation() override;

protected:
	Flipbook* _flipbookMove[4] = {};
	float _waitSeconds = 0.f;

	Player* _target = nullptr; // TEMP -> ID를 부여하거나 스마트 포인터로 변경해야함
};

