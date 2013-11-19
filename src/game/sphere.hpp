#ifndef SPHERE_HPP
#define SPHERE_HPP

#include <SFML/Graphics.hpp>

struct Sphere
{
public :
	Sphere(sf::Vector2f position, float radius);

	sf::Vector2f getPosition() const;

	float getRadius() const;

	bool intersects(const Sphere& sphere) const;

private :
	sf::Vector2f m_position;
	float m_radius;
};

#endif // SPHERE_HPP
