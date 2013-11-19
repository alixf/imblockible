#include <SFML/Graphics.hpp>
#include "defines.hpp"
#include "scenes/game.hpp"
#include "scenes/menu.hpp"

#include <iostream>

int main(int argc, char* argv[])
{
	// Create window
	sf::RenderWindow window(sf::VideoMode(WINDOWWIDTH, WINDOWHEIGHT, 32), WINDOWTITLE, sf::Style::Close, sf::ContextSettings(0, 0, 8));
	window.setFramerateLimit(60);

	// Time
	sf::Clock clock;

	// Game data
	GameData data = {""};

	// Scene
	Scene* scene = new MenuScene(data);

	clock.restart();
	while (window.isOpen())
	{
		// Get Time
		float time = clock.getElapsedTime().asSeconds();
		clock.restart();

		// Events
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			scene->onEvent(event);
		}

		switch(scene->update(time))
		{
		case Scene::CLOSE :
			window.close();
			break;

		case Scene::MENUSCENE :
			delete scene;
			scene = new MenuScene(data);
			break;

		case Scene::GAMESCENE :
			delete scene;
			scene = new GameScene(data, window);
			break;

		default : break;
		}

		window.clear(sf::Color::Black);
		scene->draw(window);
		window.display();
	}

	if(scene != NULL)
		delete scene;

	return EXIT_SUCCESS;
}
