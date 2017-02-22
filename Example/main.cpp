
#include "sfwdraw.h"
#include "GameState.h"
#include "Option.h"
#include "Depart.h"

/*
	The main function should be used for application state management.
	Currently, only one state is implemented here, you'll need to add additional
	and get them to behave properly.
*/
void main()
{
	sfw::initContext();
	
	unsigned spr_font = sfw::loadTextureMap("../res/fontmap.png", 16, 16);
	GameState gs;
	option option;
	depart depart;


	gs.init(); // called once
	
	option.init(spr_font);
	depart.init(spr_font);

	MenuState state = Enter_Option;

	//gs.play(); // Should be called each time the state is transitioned into

	while (sfw::stepContext())
	{
		switch (state)
		{
		case Enter_Option:
			option.play();
		case Option:
			option.step();
			option.draw();
			state = (MenuState)option.next();
			break;
		case Enter_Depart:
			depart.play();
		case Depart:
			depart.step();
			depart.draw();
			state = (MenuState)depart.next();
			break;

		case Enter_AGame:
			//gs.isGameOver();
			gs.play();
		case AGame:
			gs.step();
			gs.draw();
			state = (MenuState)gs.next();
		}
		//gs.step(); // called each update
		//gs.draw(); // called each update

		//gs.next(); Determine the ID of the next state to transition to.
	}

	gs.stop(); // should be called each time the state is transitioned out of

	//gs.term(); // called once


	sfw::termContext();

}