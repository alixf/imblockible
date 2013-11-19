#include "menu.hpp"

#include <boost/filesystem.hpp>
#include <fstream>
#include <sstream>
#include <cmath>
#include "../defines.hpp"

namespace fs = boost::filesystem;

MenuScene::MenuScene(GameData& gameData) : m_gameData(gameData), m_cursor(0), m_selection(false)
{
	fs::path p(LEVELSDIR);

	if (exists(p))
	{
		for(fs::directory_iterator dir(p); dir != fs::directory_iterator(); ++dir)
		{
			if(dir->path().extension() == ".lvl")
			{
				std::string levelTitle;

				std::ifstream file(dir->path().string().c_str(), std::ios::in);

				std::string line;
				bool nameFound = false;

				while (getline(file, line) && !nameFound)
				{
					std::stringstream ss(line);
					std::string identifier;
					ss >> identifier;

					if (identifier == "Name")
					{
						levelTitle = ss.str().substr(5);
						nameFound = true;
					}
				}

				m_levels.push_back(dir->path().string());
				m_levelTexts.push_back(sf::Text(levelTitle));
			}
		}
	}
}

MenuScene::~MenuScene()
{

}

void MenuScene::onEvent(const sf::Event& event)
{
	if(event.type == sf::Event::KeyPressed)
	{
		if(event.key.code == sf::Keyboard::Up && m_cursor > 0)
			--m_cursor;
		if(event.key.code == sf::Keyboard::Down && m_cursor < m_levels.size()-1)
			++m_cursor;
		if(event.key.code == sf::Keyboard::Return)
		{
			m_gameData.levelFileName = m_levels[m_cursor];
			m_selection = true;
		}
	}
	if(event.type == sf::Event::JoystickMoved)
	{
		if(event.joystickMove.position == -100.f && m_cursor > 0)
			--m_cursor;
		if(event.joystickMove.position == 100.f && m_cursor < m_levels.size()-1)
			++m_cursor;
	}
	if(event.type == sf::Event::JoystickButtonPressed)
	{
		if(event.joystickButton.button == 0)
		{
			m_gameData.levelFileName = m_levels[m_cursor];
			m_selection = true;
		}
	}
}

Scene::Type MenuScene::update(float time)
{
	for(int i = static_cast<int>(m_cursor)-3; i <= static_cast<int>(m_cursor)+3 && i < static_cast<int>(m_levelTexts.size()); ++i)
	{
		if(i >= 0)
		{
			m_levelTexts[i].setScale(1.f-abs(i-m_cursor)*0.20f, 1.f-abs(i-m_cursor)*0.20f);
			m_levelTexts[i].setColor(sf::Color(255,255,255, 255-abs(i-m_cursor)*50.f));
			m_levelTexts[i].setPosition(floor((WINDOWWIDTH-m_levelTexts[i].getLocalBounds().width*m_levelTexts[i].getScale().x)/2.f),
										floor(300.f+(i-static_cast<int>(m_cursor))*42.f));
		}
	}

	return m_selection ? Scene::GAMESCENE : Scene::NONE;
}

void MenuScene::draw(sf::RenderTarget& target)
{
	for(int i = static_cast<int>(m_cursor)-3; i <= static_cast<int>(m_cursor)+3 && i < static_cast<int>(m_levelTexts.size()); ++i)
	{
		if(i >= 0)
		{
			target.draw(m_levelTexts[i]);
		}
	}
}
