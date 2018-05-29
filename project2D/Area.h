#pragma once
#include <glm/glm.hpp>
#include <Texture.h>
namespace aie
{
	class Input;
	class Renderer2D;
}
class Area
{
public:
	Area() = delete;
	Area(glm::vec2 a_position, int a_locX, int a_locY);
	~Area();

	int update(aie::Input* a_input);
	void draw(aie::Renderer2D* a_renderer);
	void debug(aie::Renderer2D* a_renderer);

	int getLocX() { return m_locX; }
	int getLocY() { return m_locY; }

	void setTexture(aie::Texture* a_texture) { m_texture = a_texture; }

	void Reset();

protected:
	aie::Texture* m_texture;
	glm::vec2 m_position;
	int m_locX, m_locY;
	bool m_filled = false;
};

