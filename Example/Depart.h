#pragma once
#include "sfwdraw.h"
#include "MenuState.h"
#include "WaveManager.h"
#include <iostream>
class depart : public BaseState
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
		timer = 4.f;
	}

	virtual void draw()
	{
		/*char buffer[64];
		sprintf_s(buffer, "You Died");*/
		sfw::drawString(d, "You Died", 50, 500, 15, 15, 0, 0, GREEN);
		/*sfw::drawString(d, "XXXX-XXXX-XXXX-XXXX", 100, 475, 20, 20, 0, 0, BLACK);
		sfw::drawString(d, "[ENTER]", 400, 200, 20, 20, 0, 0, GREEN);*/
	}

	virtual void step()
	{
		timer -= sfw::getDeltaTime();
	}

	virtual size_t next() const
	{
		if (timer < 0)
		{
			return (size_t)Enter_Option;
		}

		return (size_t)Depart;
	}

};