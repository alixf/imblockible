#include "block.hpp"
#include <iostream>
#include "../defines.hpp"

Block::Block(Type type, float x, float y) : m_type(type), m_position(x, y)
{
}

Block::~Block()
{
}

bool Block::isPracticable() const
{
	return m_type == BLOCK;
}

sf::Vector2f Block::getPosition() const
{
	return m_position;
}

sf::Color Block::getColor() const
{
	return m_color;
}

Sphere Block::getHitSphere() const
{
	return Sphere(sf::Vector2f(m_position.x + CUBESIZE / 2, m_position.y + CUBESIZE / 2), CUBESIZE / 2 + SPHERESKIN);
}

sf::FloatRect Block::getRect() const
{
	return sf::FloatRect(m_position, sf::Vector2f(CUBESIZE, CUBESIZE));
}

void Block::setPosition(const sf::Vector2f& position)
{
	m_position = position;
}

void Block::setColor(const sf::Color& color)
{
	m_color = color;
}

void Block::draw(sf::RenderTarget& target)
{
	switch(m_type)
	{
	case BLOCK :
		{
			sf::RectangleShape rect(sf::Vector2f(CUBESIZE, CUBESIZE));
			rect.setFillColor(m_color);
			rect.setPosition(m_position);
			target.draw(rect);
		}
		break;

	case SPIKE :
		{
			sf::VertexArray spike(sf::Triangles, 3);
			spike[0].position = sf::Vector2f(m_position.x, m_position.y+CUBESIZE);
			spike[0].color = m_color;
			spike[1].position = sf::Vector2f(m_position.x+CUBESIZE/2, m_position.y);
			spike[1].color = m_color;
			spike[2].position = sf::Vector2f(m_position.x+CUBESIZE, m_position.y+CUBESIZE);
			spike[2].color = m_color;
			target.draw(spike);
		}
		break;

	default :
		break;
	}
}
