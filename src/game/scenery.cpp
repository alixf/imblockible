#include "scenery.hpp"
#include "../defines.hpp"

Scenery::Scenery(float windowWidth, float windowHeight, float sceneWidth, float sceneHeight) : m_background(sf::Quads, 8), m_foreground(sf::Quads, 16)
{
	m_background[0].position = sf::Vector2f(0.f, 0.f);
	m_background[1].position = sf::Vector2f(windowWidth, 0.f);
	m_background[2].position = sf::Vector2f(windowWidth, windowHeight/2);
	m_background[3].position = sf::Vector2f(0.f, sceneHeight/2);
	m_background[4].position = sf::Vector2f(0.f, sceneHeight/2);
	m_background[5].position = sf::Vector2f(windowWidth, windowHeight/2);
	m_background[6].position = sf::Vector2f(windowWidth, windowHeight);
	m_background[7].position = sf::Vector2f(0.f, windowHeight);

	m_foreground[0].position = sf::Vector2f(FOREGROUNDMARGIN, 0.f);
	m_foreground[1].position = sf::Vector2f(FOREGROUNDMARGIN, sceneHeight/2);
	m_foreground[2].position = sf::Vector2f(FOREGROUNDMARGIN+FOREGROUNDPADDING, sceneHeight/2);
	m_foreground[3].position = sf::Vector2f(FOREGROUNDMARGIN+FOREGROUNDPADDING, 0.f);
	m_foreground[4].position = sf::Vector2f(FOREGROUNDMARGIN, sceneHeight/2);
	m_foreground[5].position = sf::Vector2f(FOREGROUNDMARGIN, sceneHeight);
	m_foreground[6].position = sf::Vector2f(FOREGROUNDMARGIN+FOREGROUNDPADDING, sceneHeight);
	m_foreground[7].position = sf::Vector2f(FOREGROUNDMARGIN+FOREGROUNDPADDING, sceneHeight/2);
	m_foreground[8].position = sf::Vector2f(FOREGROUNDMARGIN+sceneWidth-FOREGROUNDPADDING, 0.f);
	m_foreground[9].position = sf::Vector2f(FOREGROUNDMARGIN+sceneWidth-FOREGROUNDPADDING, sceneHeight/2);
	m_foreground[10].position = sf::Vector2f(FOREGROUNDMARGIN+sceneWidth, sceneHeight/2);
	m_foreground[11].position = sf::Vector2f(FOREGROUNDMARGIN+sceneWidth, 0.f);
	m_foreground[12].position = sf::Vector2f(FOREGROUNDMARGIN+sceneWidth-FOREGROUNDPADDING, sceneHeight/2);
	m_foreground[13].position = sf::Vector2f(FOREGROUNDMARGIN+sceneWidth-FOREGROUNDPADDING, sceneHeight);
	m_foreground[14].position = sf::Vector2f(FOREGROUNDMARGIN+sceneWidth, sceneHeight);
	m_foreground[15].position = sf::Vector2f(FOREGROUNDMARGIN+sceneWidth, sceneHeight/2);
}

Scenery::~Scenery()
{

}

void Scenery::setColor(const sf::Color& color)
{
	sf::Color colorT = color;
	colorT.a = 0;
	sf::Color colorD = color;
	colorD.r /= 2;
	colorD.g /= 2;
	colorD.b /= 2;
	sf::Color colorDT = colorD;
	colorDT.a = 0;

	m_background[0].color = colorD;
	m_background[1].color = colorD;
	m_background[2].color = color;
	m_background[3].color = color;
	m_background[4].color = color;
	m_background[5].color = color;
	m_background[6].color = colorD;
	m_background[7].color = colorD;

	m_foreground[0].color = colorD;
	m_foreground[1].color = color;
	m_foreground[2].color = colorT;
	m_foreground[3].color = colorDT;
	m_foreground[4].color = color;
	m_foreground[5].color = colorD;
	m_foreground[6].color = colorDT;
	m_foreground[7].color = colorT;
	m_foreground[8].color = colorDT;
	m_foreground[9].color = colorT;
	m_foreground[10].color = color;
	m_foreground[11].color = colorD;
	m_foreground[12].color = colorT;
	m_foreground[13].color = colorDT;
	m_foreground[14].color = colorD;
	m_foreground[15].color = color;
}

void Scenery::drawBackground(sf::RenderTarget& target)
{
	target.draw(m_background);
}

void Scenery::drawForeground(sf::RenderTarget& target)
{
	target.draw(m_foreground);
}
