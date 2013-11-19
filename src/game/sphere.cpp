#include "sphere.hpp"
#include <cmath>

Sphere::Sphere(sf::Vector2f position, float radius) : m_position(position), m_radius(radius)
{
}

sf::Vector2f Sphere::getPosition() const
{
	return m_position;
}

float Sphere::getRadius() const
{
	return m_radius;
}

bool Sphere::intersects(const Sphere& sphere) const
{
	float x0 = m_position.x;
	float y0 = m_position.y;
	float x1 = sphere.m_position.x;
	float y1 = sphere.m_position.y;
	return sqrt((x1-x0)*(x1-x0)+(y1-y0)*(y1-y0)) < m_radius+sphere.m_radius;
}
