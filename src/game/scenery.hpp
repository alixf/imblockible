#ifndef SCENERY_HPP
#define SCENERY_HPP

#include <SFML/Graphics.hpp>

class Scenery
{
public :
	Scenery(float windowWidth, float windowHeight, float sceneWidth, float sceneHeight);
	~Scenery();

	void setColor(const sf::Color& color1);

	void drawBackground(sf::RenderTarget& target);
	void drawForeground(sf::RenderTarget& target);

private :
	sf::VertexArray m_background;
	sf::VertexArray m_foreground;
};

#endif // SCENERY_HPP
