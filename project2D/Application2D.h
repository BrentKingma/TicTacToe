#pragma once

#include "Application.h"
#include "Renderer2D.h"
#include "Area.h"

class Application2D : public aie::Application {
public:

	Application2D();
	virtual ~Application2D();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

	int getPlayerTurn();
	int getWinningPlayer();

	void Reset();

protected:

	aie::Renderer2D*	m_2dRenderer;

	aie::Texture* m_x;
	aie::Texture* m_o;

	aie::Font* m_font;

	int m_playArea[3][3];
	Area* m_areas[9];

	float m_cameraX, m_cameraY;
	float m_timer;

	int m_playerTurn = 1;

	bool m_victory = false;
	bool m_tie = false;
	int m_winningPlayer = 0;
	int m_movesDone = 0;

	void CheckForVictor();
};