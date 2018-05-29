#include "Area.h"
#include <Renderer2D.h>
#include <Input.h>
Area::Area(glm::vec2 a_position, int a_locX, int a_locY)
	:m_position(a_position)
	,m_locX(a_locX)
	,m_locY(a_locY)
{
}

Area::~Area()
{
	
}

int Area::update(aie::Input * a_input)
{
	if (!m_filled)
	{
		int mouseX, mouseY;
		a_input->getMouseXY(&mouseX, &mouseY);
		 
		if (a_input->isMouseButtonDown(aie::INPUT_MOUSE_BUTTON_LEFT) && glm::distance({ mouseX, mouseY }, m_position) <= 50)
		{
			m_filled = true;
			return 1;
		}
	}
	return 0;
}

void Area::draw(aie::Renderer2D * a_renderer)
{
	if (m_filled)
	{
		a_renderer->setRenderColour(1, 0, 0, 1);
		a_renderer->drawSprite(m_texture, m_position.x, m_position.y, 100.0f, 100.0f);
	}
}



void Area::debug(aie::Renderer2D * a_renderer)
{
	if (!m_filled)
	{
		a_renderer->setRenderColour(1, 1, 1, 1);
	}
	else
	{
		a_renderer->setRenderColour(1, 0, 0, 1);
	}
	a_renderer->drawCircle(m_position.x, m_position.y, 50);
}

void Area::Reset()
{
	m_texture = nullptr;
	m_filled = false;
}
