#pragma once
#include "sfwdraw.h"
#include "MenuState.h"
class option : public BaseState
{
public:
	int d;
	float timer;
	int select;

	virtual void init(int A_font)
	{
		d = A_font;
	}

	virtual void play()
	{
		timer = 3.f;
	}

	virtual void draw()
	{
		sfw::drawString(d, "Please Enter Credit Card Information To Continue", 50, 500, 15, 20, 0, 0, GREEN);
		sfw::drawString(d, "Press M & N To Cycle Between Turrets", 70, 475, 20, 20, 0, 0, BLACK);
		sfw::drawString(d, "Press B To Build Turrets (50 gold)", 70, 425, 20, 20, 0, 0, BLACK);
		sfw::drawString(d, "Press V To Upgrade Turrets (25 gold)", 70, 375, 20, 20, 0, 0, BLACK);
		sfw::drawString(d, "Press Space To Start The Wave", 70, 325, 20, 20, 0, 0, BLACK);
		sfw::drawString(d, "[ENTER]", 400, 200, 20, 20, 0, 0, GREEN);
	}

	virtual void step()
	{
	}

	virtual size_t next() const
	{
		if (sfw::getKey(KEY_ENTER))
		{
			return (size_t)Enter_AGame;
		}
		
		return (size_t)Option;
	}

};