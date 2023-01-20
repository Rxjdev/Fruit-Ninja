#pragma once

class CMyGame : public CGame
{
	CSprite player;  // player sprite declaration
	CSprite pear;
	CSprite cherry;
	CSprite apple;
	CSprite startScreen;
	CSprite bg;

	int score;		 // score

	bool gamewon;

	// music and sounds
	CSoundPlayer music;
	CSoundPlayer slash;
	CSoundPlayer splat;

public:
	CMyGame(void);	 // Constructor
	~CMyGame(void);  // Destructor

	int level;
	void SetUpLevel1();
	void SetUpLevel2();

	// Per-Frame Callback Funtions (must be implemented!)
	virtual void OnUpdate();
	virtual void OnDraw(CGraphics* g);

	// Game Life Cycle
	virtual void OnInitialize();
	virtual void OnDisplayMenu();
	virtual void OnStartGame();
	virtual void OnGameOver();
	virtual void OnTerminate();

	// Keyboard Event Handlers
	virtual void OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode);
	virtual void OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode);

	// Mouse Events Handlers
	virtual void OnMouseMove(Uint16 x,Uint16 y,Sint16 relx,Sint16 rely,bool bLeft,bool bRight,bool bMiddle);
	virtual void OnLButtonDown(Uint16 x,Uint16 y);
	virtual void OnLButtonUp(Uint16 x,Uint16 y);
	virtual void OnRButtonDown(Uint16 x,Uint16 y);
	virtual void OnRButtonUp(Uint16 x,Uint16 y);
	virtual void OnMButtonDown(Uint16 x,Uint16 y);
	virtual void OnMButtonUp(Uint16 x,Uint16 y);
};