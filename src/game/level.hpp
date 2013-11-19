#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <list>
#include <SFML/Audio.hpp>

#include "block.hpp"

class Level
{
public :
	struct Event
	{
		enum Type
		{
			NONE, ROTATE, COLOR
		};

		union Parameter
		{
			unsigned int 	ui;
			float			f;
			int				i;
		};

		float 		position;
		Type 		type;
		Parameter 	parameter;
	};

	Level();

	std::string getName() const;

	sf::Vector2f getSize() const;

	sf::Color getColor() const;

	std::list<Block>& getBlocks();

	std::list<Event>& getEvents();

	bool load(const std::string& fileName);

	void start();

private :
	void addBlock(Block::Type type, float x, float y);

	std::string 		m_name;
	std::string 		m_musicFileName;
	sf::Color 			m_color;
	sf::Vector2f 		m_size;
	std::list<Block> 	m_blocks;
	std::list<Event> 	m_events;
	sf::Music			m_music;
};

#endif
