#include "game.hpp"
#include <cmath>
#include <list>
#include <iostream>
#include <sstream>
#include "../defines.hpp"

GameScene::GameScene(GameData& gameData, sf::RenderWindow& window) :
		m_gameData(gameData),
		m_window(window),
		m_sceneView(sf::Vector2f(VIEWWIDTH / 2, VIEWHEIGHT / 2), sf::Vector2f(VIEWWIDTH, VIEWHEIGHT)),
		m_scenery(WINDOWWIDTH, WINDOWHEIGHT, VIEWWIDTH, VIEWHEIGHT),
		m_level(),
		m_cube(0.f, 0.f, CUBESIZE),
		m_attemptCount(1),
		m_godMode(false),
		m_floor(sf::Vector2f(0.f, 0.f)),
		m_attemptsText(""),
		m_godModeText(""),
		m_quit(false)
{
	// Create scene view
	m_sceneView.setViewport(sf::FloatRect((1 - VIEWWIDTH / WINDOWWIDTH) / 2, (1 - VIEWHEIGHT / WINDOWHEIGHT) / 2, VIEWWIDTH / WINDOWWIDTH, VIEWHEIGHT / WINDOWHEIGHT));

	// Create and init level
	loadLevel();
	m_level.start();

	m_floor.setSize(sf::Vector2f(m_level.getSize().x, FLOORSIZE));

	// Create Floor
	m_floor.setPosition(0.f, m_level.getSize().y);
	m_floor.setFillColor(sf::Color::White);

	// UI
	std::stringstream ss;
	ss << "Attempts : " << m_attemptCount;
	m_attemptsText.setString(ss.str());
	m_attemptsText.setPosition(floor(window.getSize().x / 2.f - m_attemptsText.getGlobalBounds().width / 2.f), 30.f);
	m_attemptsText.setColor(sf::Color::White);

	m_godModeText.setString(m_godMode ? "Hypercube Mode !" : "");
	m_godModeText.setPosition(window.getSize().x / 2.f - m_godModeText.getGlobalBounds().width / 2.f, 80.f);
	m_godModeText.setColor(sf::Color::White);
}

GameScene::~GameScene()
{

}

void GameScene::onEvent(const sf::Event& event)
{
	if (event.type == sf::Event::KeyPressed)
	{
		if(event.key.code == sf::Keyboard::Return)
		{
			m_godMode = !m_godMode;
			m_godModeText.setString(m_godMode ? "Hypercube Mode !" : "");
			m_godModeText.setPosition(floor(m_window.getSize().x / 2.f - m_godModeText.getGlobalBounds().width / 2.f), 80.f);
		}
		if (event.key.code == sf::Keyboard::Escape || event.key.code == sf::Keyboard::Back)
		{
			m_quit = true;
		}
	}
	if(event.type == sf::Event::JoystickButtonPressed)
	{
		if(event.joystickButton.button == 6)
		{
			m_quit = true;
		}
		else if(event.joystickButton.button == 7)
		{
			m_godMode = !m_godMode;
			m_godModeText.setString(m_godMode ? "Hypercube Mode !" : "");
			m_godModeText.setPosition(floor(m_window.getSize().x / 2.f - m_godModeText.getGlobalBounds().width / 2.f), 80.f);
		}
	}
}

Scene::Type GameScene::update(float time)
{
	// Cube
	float cubeDistToGround = m_level.getSize().y - (m_cube.getBoundingRect().top + m_cube.getBoundingRect().height);
	for (std::list<Block>::iterator it = m_level.getBlocks().begin(); it != m_level.getBlocks().end(); ++it)
	{
		sf::FloatRect rect = it->getRect();
		sf::Vector2f cubePosition = m_cube.getHitSphere().getPosition();

		if(rect.left <= cubePosition.x+PADOFFSET && rect.left+rect.width >= cubePosition.x-PADOFFSET && rect.top >= cubePosition.y && it->isPracticable())
		{
			float newCubeDistToGround = rect.top - (cubePosition.y+CUBESIZE/2);
			if(newCubeDistToGround < cubeDistToGround)
				 cubeDistToGround = newCubeDistToGround;
		}
	}
	m_cube.update(time, cubeDistToGround);

	// Update view according to cube's position
	m_sceneView.setCenter(m_cube.getPosition()+sf::Vector2f(250.f,-150.f));

	// Events
	std::list<Level::Event>::iterator it = m_level.getEvents().begin();
	if(it != m_level.getEvents().end() && it->position <= m_cube.getPosition().x)
	{
		switch(it->type)
		{
		case Level::Event::ROTATE :
			m_sceneView.rotate(it->parameter.f);
			break;

		case Level::Event::COLOR :
			{
				unsigned int r = it->parameter.ui << 8 >> 24;
				unsigned int g = it->parameter.ui << 16 >> 24;
				unsigned int b = it->parameter.ui << 24 >> 24;
				m_scenery.setColor(sf::Color(r,g,b));
			}
			break;

		default :
			break;
		}
		it = m_level.getEvents().erase(it);
	}

	// Blocks
	for (std::list<Block>::iterator it = m_level.getBlocks().begin(); it != m_level.getBlocks().end(); ++it)
	{
		if (it->getHitSphere().intersects(m_cube.getHitSphere()) && !m_godMode && m_cube.getState() == Cube::ALIVE)
			m_cube.setState(Cube::DESTROYING);
	}

	// Start next level or restart
	if (m_cube.getPosition().x >= m_level.getSize().x)
	{
		loadLevel();
		m_level.start();
	}
	if(m_cube.getState() == Cube::DESTROYED)
	{
		m_cube = Cube(0.f, 0.f, CUBESIZE);
		loadLevel();
		m_level.start();
		++m_attemptCount;
		std::stringstream ss;
		ss << "Attempts : " << m_attemptCount;
		m_attemptsText.setString(ss.str());
	}

	return m_quit ? Scene::MENUSCENE : Scene::NONE;
}

void GameScene::draw(sf::RenderTarget& target)
{
	target.setView(target.getDefaultView());
	m_scenery.drawBackground(target);

	target.setView(m_sceneView);
	target.draw(m_floor);

	for (std::list<Block>::iterator it = m_level.getBlocks().begin(); it != m_level.getBlocks().end(); ++it)
		(*it).draw(target);
	m_cube.draw(target);

	target.setView(target.getDefaultView());
	m_scenery.drawForeground(target);
	target.draw(m_attemptsText);
	target.draw(m_godModeText);
}

void GameScene::loadLevel()
{
	m_level.load(m_gameData.levelFileName);

	m_window.setTitle("Imblockible - "+m_level.getName());
	m_scenery.setColor(m_level.getColor());

	m_sceneView = 	sf::View(sf::Vector2f(VIEWWIDTH / 2, VIEWHEIGHT / 2), sf::Vector2f(VIEWWIDTH, VIEWHEIGHT));
	m_sceneView.setViewport(sf::FloatRect((1 - VIEWWIDTH / WINDOWWIDTH) / 2, (1 - VIEWHEIGHT / WINDOWHEIGHT) / 2, VIEWWIDTH / WINDOWWIDTH, VIEWHEIGHT / WINDOWHEIGHT));
}
