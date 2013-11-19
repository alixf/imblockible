#ifndef CUBE_HPP
#define CUBE_HPP

#include <SFML/Graphics.hpp>
#include "sphere.hpp"

class Cube
{
public :
	enum State
	{
		ALIVE, DESTROYING, DESTROYED
	};

	Cube(float x, float y, float size);

	State getState() const;

	sf::Vector2f getPosition() const;

	Sphere getHitSphere() const;

	sf::FloatRect getBoundingRect() const;

	void setState(State state);

	void jump();

	void update(float time, float distanceToGround);

	void draw(sf::RenderTarget& target);

private :
	State				m_state;
	float				m_size;
	bool				m_jumping;
	float				m_jumpingTime;
	float 				m_destructionTime;
	bool 				m_onSolidGround;
	sf::RectangleShape	m_shape;
};

#endif // CUBE_HPP
