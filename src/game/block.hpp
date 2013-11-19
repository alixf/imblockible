#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <SFML/Graphics.hpp>
#include "sphere.hpp"

class Block
{
public :
	enum Type
	{
		SPIKE, BLOCK
	};

	Block(Type type, float x, float y);

	~Block();

	bool isPracticable() const;

	sf::Vector2f getPosition() const;

	sf::Color getColor() const;

	Sphere getHitSphere() const;

	sf::FloatRect getRect() const;

	void setPosition(const sf::Vector2f& position);

	void setColor(const sf::Color& color);

	void draw(sf::RenderTarget& target);

private :
	Type m_type;
	sf::Vector2f m_position;
	sf::Color m_color;
};

#endif // OBJECT_HPP
