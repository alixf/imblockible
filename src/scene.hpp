#ifndef SCENE_HPP
#define SCENE_HPP

struct GameData
{
	std::string levelFileName;
};

class Scene
{
public :
	enum Type
	{
		NONE, CLOSE, MENUSCENE, GAMESCENE
	};

	Scene()
	{
	}
	virtual ~Scene()
	{
	}

	virtual void onEvent(const sf::Event& event) = 0;
	virtual Type update(float time) = 0;
	virtual void draw(sf::RenderTarget& target) = 0;
};

#endif // SCENE_HPP
