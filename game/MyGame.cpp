#include "stdafx.h"
#include "MyGame.h"
#include <sstream>

CMyGame::CMyGame(void) : 
	bg(400, 300, "bg.bmp", CColor::White(), 0),
	player(400,20, "katana.bmp", CColor::White(), GetTime()),	 
	cherry(40,600,"cherry.bmp",CColor::Black(),GetTime()),	
	pear(60,600,"pear.bmp",CColor::Black(),GetTime()),			
	apple(60,600,"Apple.bmp",CColor::Black(),GetTime()),          
	startScreen(400, 300, "startScreen.bmp", CColor::Black(), 0)
				
{
	// TODO: add initialisation here

	// set score to zero
	score=0;
	level = 0;

	gamewon = false;
}

CMyGame::~CMyGame(void)
{
	// TODO: add destruction code here
}

/////////////////////////////////////////////////////
// Per-Frame Callback Funtions (must be implemented!)

void CMyGame::OnUpdate()
{
	if (IsMenuMode() || IsGameOverMode()) return;
	
	Uint32 t = GetTime();

	// ----- updating sprites -----------

	player.Update(t);
	cherry.Update(t);
	pear.Update(t);
	apple.Update(t);

	
	
	if (cherry.HitTest(&player))
	{
		slash.Play("slash.wav");
		splat.Play("splat.wav");
		score++;
		cherry.SetPosition(float(rand() % 800), 0);
		cherry.SetVelocity(cherry.GetXVelocity(), 520);
		
	}
	if (cherry.GetY() < 0)
	{
		score--;
		cherry.SetPosition(float(rand() % 800), 0);
		cherry.SetVelocity(cherry.GetXVelocity(), 520);
		
	}
	if (pear.HitTest(&player))
	{
		slash.Play("slash.wav");
		splat.Play("splat.wav");
		score++;
		pear.SetPosition(float(rand() % 800), 0);
		pear.SetVelocity(pear.GetXVelocity(), 500);
		
	}
	if (pear.GetY() < 0)
	{
		score--;
		pear.SetPosition(float(rand() % 800), 0);
		pear.SetVelocity(pear.GetXVelocity(), 500);
		
	}
	if (apple.HitTest(&player))
	{
		slash.Play("slash.wav");
		splat.Play("splat.wav");
		GameOver();
	}
	if (apple.GetY() < 0)
	{
		apple.SetPosition(float(rand() % 800), 0);
		apple.SetVelocity(apple.GetXVelocity(), 500);
		
	}

	cherry.SetVelocity(cherry.GetXVelocity(), cherry.GetYVelocity() - 3.8);
	pear.SetVelocity(pear.GetXVelocity(), pear.GetYVelocity() - 3.8);
	apple.SetVelocity(apple.GetXVelocity(), apple.GetYVelocity() - 3.8);


	if (score < 0)
	{
		GameOver();
	}
	// --------- game rules ---------------

	if (level == 1 && score == 30)
	{
		gamewon = true; GameOver();
	}

	if (level == 2 && score == 40)
	{
		gamewon = true; GameOver();
	}

	
	


}

void CMyGame::OnDraw(CGraphics* g)
{
	if (IsMenuMode())
	{
		startScreen.Draw(g);
		return;
	}

	
	bg.Draw(g);
	    player.Draw(g);
		cherry.Draw(g);
		pear.Draw(g);
		apple.Draw(g);
		// draw all fruit here
		

		// print score at position xy(50,570)
		*g << font(28) << color(CColor::Red()) << xy(10,570) << score;

		// print game over at at the centre of the screen
		if (IsGameOverMode())
		{

			if (gamewon)
			{
				*g << font(30) << color(CColor::Blue()) << vcenter << center << " GAME WON - PRESS F2 TO RETURN TO THE MENU ";
			}
			else
			{
				*g << font(30) << color(CColor::Red()) << vcenter << center << " GAME OVER - PRESS F2 TO RETURN TO THE MENU ";
			}
		}

}

/////////////////////////////////////////////////////
// Game Life Cycle

// one time initialisation
void CMyGame::OnInitialize()
{
	
}

// called at the start of a new game - display menu here
void CMyGame::OnDisplayMenu()
{
	player.SetOmega(100);

	// set score to 0
	level = 1;
	score = 0;

	gamewon = false;


	music.Play("music.wav", -1); // play continuously with (-1)


	
}

void CMyGame::SetUpLevel1()
{
	HideMouse();

	cherry.SetPosition(0, 0);
	pear.SetPosition(0, 0);
	apple.SetPosition(0, 0);

	cherry.SetSpeed(520);
	pear.SetSpeed(600);
	apple.SetSpeed(500);

	
	apple.SetPosition(float(rand() % 110), 0);
	pear.SetPosition(float(rand() % 100), 0);
	cherry.SetPosition(float(rand() % 90), 0);

	

}

void CMyGame::SetUpLevel2()
{
	HideMouse();

	cherry.SetPosition(0, 0);
	pear.SetPosition(0, 0);
	apple.SetPosition(0, 0);

	cherry.SetSpeed(620);
	pear.SetSpeed(700);
	apple.SetSpeed(600);


	apple.SetPosition(float(rand() % 110), 0);
	pear.SetPosition(float(rand() % 100), 0);
	cherry.SetPosition(float(rand() % 90), 0);

}

// called when Game Mode entered
void CMyGame::OnStartGame()
{
	if (level == 1) SetUpLevel1();
	if (level == 2) SetUpLevel2();

}

// called when Game is Over
void CMyGame::OnGameOver()
{
	ShowMouse();
}

// one time termination code
void CMyGame::OnTerminate()
{
}

/////////////////////////////////////////////////////
// Keyboard Event Handlers

void CMyGame::OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode)
{
	if (!IsMenuMode() && sym == SDLK_F2)

		NewGame();

	if (IsMenuMode())
	{
		if (sym == SDLK_1)
		{
			level = 1;
			StartGame();
		}
		else if (sym == SDLK_2)
		{
			level = 2;
			StartGame();
		}
	}
	if (sym == SDLK_F4 && (mod & (KMOD_LALT | KMOD_RALT)))
		StopGame();
	if (level == 1 && sym == SDLK_F2)
	{
		NewGame();

		
	}

	if (level == 2 && sym == SDLK_F2)
	{

		NewGame();

		cherry.SetPosition(0, 0);
		pear.SetPosition(0, 0);
		apple.SetPosition(0, 0);

		cherry.SetSpeed(620);
		pear.SetSpeed(700);
		apple.SetSpeed(600);

		apple.SetPosition(float(rand() % 110), 0);
		pear.SetPosition(float(rand() % 100), 0);
		cherry.SetPosition(float(rand() % 90), 0);
	}


}

void CMyGame::OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode)
{
	
}


/////////////////////////////////////////////////////
// Mouse Events Handlers

void CMyGame::OnMouseMove(Uint16 x,Uint16 y,Sint16 relx,Sint16 rely,bool bLeft,bool bRight,bool bMiddle)
{
	// synchronise horizontal paddle position with the mouse position 
	if (IsGameMode()) player.SetPosition(x,y);
}

void CMyGame::OnLButtonDown(Uint16 x,Uint16 y)
{

}

void CMyGame::OnLButtonUp(Uint16 x,Uint16 y)
{
}

void CMyGame::OnRButtonDown(Uint16 x,Uint16 y)
{
}

void CMyGame::OnRButtonUp(Uint16 x,Uint16 y)
{
}

void CMyGame::OnMButtonDown(Uint16 x,Uint16 y)
{
}

void CMyGame::OnMButtonUp(Uint16 x,Uint16 y)
{
}
