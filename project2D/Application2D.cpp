#include "Application2D.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include <string>
#include <iostream>

Application2D::Application2D() {

}

Application2D::~Application2D() {

}

float GeneFunc()
{
	return rand() % 256;
}

bool Application2D::startup() {
	
	m_2dRenderer = new aie::Renderer2D();

	m_x = new aie::Texture("./bin/textures/x.png");
	m_o = new aie::Texture("./bin/textures/o.png");
	m_font = new aie::Font("./bin/font/consolas.ttf", 32);

	for (int y = 0; y < 3; y++)
	{
		for (int x = 0; x < 3; x++)
		{
			m_playArea[x][y] = 0;
		}
	}
	//Values for spawning the areas in the correct areas
	int spawnX = 275;
	int spawnY = 350;
	int arrayCount = 0;
	for (int i = 0; i < 3; i++)
	{
		spawnX = 275;
		for (int j = 0; j < 3; j++)
		{
			//Links up the appropriate areas with the x and y values corrisponding to the 2D array
			m_areas[arrayCount] = new Area({ spawnX, spawnY }, j, i);
			arrayCount++;
			spawnX += 100;
		}
		spawnY -= 100;
	}
	m_cameraX = 0;
	m_cameraY = 0;
	m_timer = 0;	

	return true;
}

void Application2D::shutdown() {
	for (int i = 0; i < 9; i++)
	{
		delete m_areas[i];
		m_areas[i] = nullptr;
	}
	delete m_x;
	delete m_o;
	delete m_font;
	delete m_2dRenderer;
	
}

void Application2D::update(float deltaTime) {

	m_timer += deltaTime;

	// input example
	aie::Input* input = aie::Input::getInstance();
	CheckForVictor();
	if (!m_victory && !m_tie)
	{
		for (int i = 0; i < 9; i++)
		{
			if (m_areas[i]->update(input) == 1)
			{
				//If a open area was clicked the corrisponding player sprite is set
				m_areas[i]->setTexture((m_playerTurn == 1) ? m_x : m_o);
				//Sets the corrisponding 2D area location with the area that was clicked
				m_playArea[m_areas[i]->getLocY()][m_areas[i]->getLocX()] = m_playerTurn;
				//Changes player turn
				m_playerTurn = (m_playerTurn == 1) ? 2 : 1;
				m_movesDone++;
			}
		}
	}
	if (m_victory || m_tie)
	{
		if (input->getPressedKeys().size() > 0)
		{
			Reset();
		}
	}
	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void Application2D::draw() {

	// wipe the screen to the background colour
	clearScreen();

	// set the camera position before we begin rendering
	m_2dRenderer->setCameraPos(m_cameraX, m_cameraY);

	// begin drawing sprites
	m_2dRenderer->begin();
	//Draws the boxes around the play area
	m_2dRenderer->drawLine(225, 300, 525, 300);
	m_2dRenderer->drawLine(225, 200, 525, 200);
	m_2dRenderer->drawLine(325, 400, 325, 100);
	m_2dRenderer->drawLine(425, 400, 425, 100);

	char turn[32];
	//Allows for rendering of char arrays that change
	sprintf_s(turn, 32, "Player: %i", getPlayerTurn());
	m_2dRenderer->drawText(m_font, turn, 10, 400);

	for (int i = 0; i < 9; i++)
	{
		//m_areas[i]->debug(m_2dRenderer);
		m_areas[i]->draw(m_2dRenderer);
	}
	if (m_victory)
	{
		m_2dRenderer->setRenderColour(1, 1, 1, 1);
		char winner[32];
		sprintf_s(winner, 32, "Player %i is the winner", getWinningPlayer());
		m_2dRenderer->drawText(m_font, winner, 175, 50);
	}
	if (m_tie)
	{
		m_2dRenderer->setRenderColour(1, 1, 1, 1);
		m_2dRenderer->drawText(m_font, "Its a tie, no winner", 200, 50);
	}
	// done drawing sprites
	m_2dRenderer->end();
}

int Application2D::getPlayerTurn()
{
	return m_playerTurn;
}

int Application2D::getWinningPlayer()
{
	return m_winningPlayer;
}

void Application2D::Reset()
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			m_playArea[i][j] = 0;
		}
	}
	for (int i = 0; i < 9; i++)
	{
		m_areas[i]->Reset();
	}

	m_playerTurn = 1;
	m_victory = false;
	m_tie = false;
	m_winningPlayer = 0;
	m_movesDone = 0;
}

void Application2D::CheckForVictor()
{
	//Checks each row and makes sure that they match eachother and not the default value
	for (int i = 0; i<3; i++)
	{
		if (m_playArea[i][0] == m_playArea[i][1] && m_playArea[i][0] == m_playArea[i][2] && m_playArea[i][0] != 0)
		{
			m_victory = true;
			m_winningPlayer = m_playArea[i][0];
			return;
		}
	}
	//Checks each column and makes sure that they match eachother and not the default value
	for (int i = 0; i<3; i++)
	{
		if (m_playArea[0][i] == m_playArea[1][i] && m_playArea[0][i] == m_playArea[2][i] && m_playArea[0][i] != 0)
		{
			m_victory = true;
			m_winningPlayer = m_playArea[0][i];
			return;
		}
	}
	//Checks each diagonals and makes sure that they match eachother and not the default value
	if (m_playArea[0][0] == m_playArea[1][1] && m_playArea[1][1] == m_playArea[2][2] && m_playArea[0][0] != 0)
	{
		m_victory = true;
		m_winningPlayer = m_playArea[0][0];
		return;
	}
	if (m_playArea[0][2] == m_playArea[1][1] && m_playArea[1][1] == m_playArea[2][0] && m_playArea[0][2] != 0)
	{
		m_victory = true;
		m_winningPlayer = m_playArea[0][2];
		return;
	}
	//Checks for a tie
	if (m_movesDone == 9 && m_victory != true)
	{
		m_tie = true;
	}
}
