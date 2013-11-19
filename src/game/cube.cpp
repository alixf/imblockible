#include "cube.hpp"
#include <iostream>
#include <cmath>
#include "../defines.hpp"

Cube::Cube(float x, float y, float size) :
	m_state(ALIVE),
	m_size(size),
	m_jumping(false),
	m_jumpingTime(0.f),
	m_destructionTime(0.f),
	m_onSolidGround(false),
	m_shape(sf::Vector2f(CUBESIZE, CUBESIZE))
{
	m_shape.setOrigin(m_size / 2, m_size / 2);
	m_shape.setPosition(x, y);
	m_shape.setFillColor(sf::Color::Black);
	m_shape.setOutlineColor(sf::Color::White);
	m_shape.setOutlineThickness(1.f);
}

void Cube::jump()
{
	if (m_onSolidGround && !m_jumping)
	{
		m_jumpingTime = 0.f;
		m_jumping = true;
		m_onSolidGround = false;
	}
}

Cube::State Cube::getState() const
{
	return m_state;
}

sf::Vector2f Cube::getPosition() const
{
	return m_shape.getPosition();
}

Sphere Cube::getHitSphere() const
{
	return Sphere(m_shape.getPosition(), m_size / 2 + SPHERESKIN);
}

sf::FloatRect Cube::getBoundingRect() const
{
	return sf::FloatRect(m_shape.getPosition() - m_shape.getOrigin(), sf::Vector2f(m_size, m_size));
}

void Cube::setState(Cube::State state)
{
	m_state = state;
}

float jumpFunc(float x)
{
	return -((x * 2 - 1) * (x * 2 - 1)) * JUMPHEIGHT + JUMPHEIGHT;
}

void Cube::update(float time, float distanceToGround)
{
	if (m_state == ALIVE)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Joystick::isButtonPressed(1, 0))
			jump();

		m_shape.setPosition(m_shape.getPosition()+sf::Vector2f(time * SPEED, 0.f));

		if (m_jumping)
		{
			m_jumpingTime += time;

			float x0 = (m_jumpingTime - time) / JUMPTIME;
			float x1 = (m_jumpingTime) / JUMPTIME;
			float height = jumpFunc(x1) - jumpFunc(x0);

			if (m_jumpingTime > JUMPTIME / 2)
			{
				m_jumping = false;
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Joystick::isButtonPressed(1, 0))
					jump();
			}
			else if (m_jumpingTime > JUMPTIME)
			{
				m_jumping = false;
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Joystick::isButtonPressed(1, 0))
					jump();
			}

			if (m_jumping)
			{
				m_shape.setPosition(m_shape.getPosition() + sf::Vector2f(0.f, -height));
				m_shape.setRotation(m_shape.getRotation() + (time / JUMPTIME) * 180.f);
			}
		}
		if (!m_jumping)
		{
			if (distanceToGround < 2 * M_PI * JUMPHEIGHT * time) // Land
			{
				if (!m_onSolidGround)
				{
					m_onSolidGround = true;
					m_shape.setPosition(m_shape.getPosition() + sf::Vector2f(0.f, distanceToGround));
					distanceToGround = 0.f;
					m_shape.setRotation(0.f);
				}
			}
			else // Fall
			{
				m_onSolidGround = false;
				m_shape.setPosition(m_shape.getPosition() + sf::Vector2f(0.f, 2 * M_PI * JUMPHEIGHT * time));
				m_shape.setRotation(m_shape.getRotation() + (time / JUMPTIME) * 180.f);
			}
		}
	}
	else if (m_state == DESTROYING)
	{
		m_destructionTime += time;
		if (m_destructionTime > 0.5f)
		{
			m_state = DESTROYED;
			m_destructionTime = 0.5f;
		}
		m_shape.setScale(1.f + m_destructionTime * 5.f, 1.f + m_destructionTime * 5.f);
		m_shape.setFillColor(sf::Color(0, 0, 0, (0.5f - m_destructionTime) * 255));
		m_shape.setOutlineColor(sf::Color(255, 255, 255, (0.5f - m_destructionTime) * 255));
	}

	if (distanceToGround < 0.f)
	{
		m_shape.setPosition(m_shape.getPosition() - sf::Vector2f(0.f, distanceToGround));
		distanceToGround = 0.f;
	}
}

void Cube::draw(sf::RenderTarget& target)
{
	target.draw(m_shape);

	/* Debug : Draw hit sphere

	Sphere hitSphere = GetHitSphere();
	sf::CircleShape sphere(hitSphere.getRadius());
	sphere.setPosition(hitSphere.getPosition());
	sphere.setFillColor(sf::Color::Green);
	sphere.setOrigin(hitSphere.getRadius(), hitSphere.getRadius());
	target.Draw(sphere);
	*/
}
