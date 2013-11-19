#ifndef MENUSCENE_HPP
#define MENUSCENE_HPP

#include <SFML/Graphics.hpp>
#include "../scene.hpp"

class MenuScene : public Scene
{
public :
	MenuScene(GameData& gameData);
	~MenuScene();

	void onEvent(const sf::Event& event);
	Scene::Type update(float time);
	void draw(sf::RenderTarget& target);

private :
	GameData& m_gameData;
	std::vector<std::string> m_levels;
	std::vector<sf::Text> m_levelTexts;
	unsigned int m_cursor;
	bool m_selection;
};

#endif // MENUSCENE_HPP
