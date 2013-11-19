#ifndef GAMESCENE_HPP
#define GAMESCENE_HPP

#include <SFML/Graphics.hpp>
#include "../game/block.hpp"
#include "../game/cube.hpp"
#include "../game/scenery.hpp"
#include "../game/level.hpp"

#include "../scene.hpp"

class GameScene : public Scene
{
public :
	GameScene(GameData& gameData, sf::RenderWindow& window);
	~GameScene();

	void onEvent(const sf::Event& event);
	Scene::Type update(float time);
	void draw(sf::RenderTarget& target);

private :
	void loadLevel();

	GameData& 			m_gameData;
	sf::RenderWindow&	m_window;
	sf::View			m_sceneView;
	Scenery				m_scenery;
	Level				m_level;
	Cube				m_cube;
	unsigned int		m_attemptCount;
	bool				m_godMode;
	sf::RectangleShape	m_floor;
	sf::Text			m_attemptsText;
	sf::Text			m_godModeText;
	bool 				m_quit;
};

#endif // GAMESCENE_HPP
