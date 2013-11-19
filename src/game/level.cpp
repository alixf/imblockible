#include "level.hpp"

#include <fstream>
#include <sstream>
#include <iostream>
#include <boost/filesystem.hpp>
#include "../defines.hpp"

namespace fs = boost::filesystem;

Level::Level() : m_color(255, 255, 255)
{
}

std::string Level::getName() const
{
	return m_name;
}

sf::Vector2f Level::getSize() const
{
	return m_size;
}

sf::Color Level::getColor() const
{
	return m_color;
}

std::list<Block>& Level::getBlocks()
{
	return m_blocks;
}

std::list<Level::Event>& Level::getEvents()
{
	return m_events;
}

bool Level::load(const std::string& fileName)
{
	std::stringstream ss;
	ss << fileName;
	std::ifstream file(ss.str().c_str(), std::ios::in);

	if (!file)
	{
		std::cerr << "Error : \"" << ss.str() << "\" no such file or directory" << std::endl;
		return false;
	}

	m_musicFileName = "";
	m_blocks.clear();
	m_events.clear();

	std::string line;
	while (getline(file, line))
	{
		std::stringstream ss(line);
		std::string identifier;
		ss >> identifier;

		if (identifier == "Name")
		{
			m_name = ss.str().substr(5);
		}
		else if (identifier == "Color")
		{
			unsigned int r, g, b;
			ss >> r >> g >> b;
			m_color = sf::Color(r, g, b);
		}
		else if (identifier == "Music")
		{
			fs::path p(fileName);
			m_musicFileName = fs::path(fileName).parent_path().string() + "/" + ss.str().substr(6);
			m_music.openFromFile(m_musicFileName);
		}
		else if (identifier == "Blocks")
		{
			ss >> m_size.y;
			for (unsigned int y = 0; y < m_size.y; ++y)
			{
				std::string blocksLine;
				getline(file, blocksLine);

				for (unsigned int x = 0; x < blocksLine.size(); ++x)
				{
					switch (blocksLine[x])
					{
					case 'O':
						m_blocks.push_back(Block(Block::BLOCK, x * CUBESIZE, y * CUBESIZE));
						break;

					case '^':
						m_blocks.push_back(Block(Block::SPIKE, x * CUBESIZE, y * CUBESIZE));
						break;

					case 'e':
						Event event;
						event.type = Event::NONE;
						event.position = x * CUBESIZE;
						m_events.push_back(event);
						break;

					default:
						break;
					}
				}
				// If the line is larger than previous known level's width,
				// Set the level's width to the line's size
				if(blocksLine.size() > m_size.x)
					m_size.x = blocksLine.size();
			}
			// Remove event line from height
			m_size.y -= 1;

			// Now that width and height are clearly defined, multiply them by the block size
			m_size.x *= CUBESIZE;
			m_size.y *= CUBESIZE;

		}
		else if (identifier == "Events")
		{
			for (std::list<Event>::iterator it = m_events.begin(); it != m_events.end(); ++it)
			{
				std::string eventLine;
				getline(file, eventLine);

				std::stringstream ess(eventLine);

				unsigned int eventId;
				ess >> eventId;

				switch (eventId)
				{
				case 1:
					{
						it->type = Event::ROTATE;
						float rotation;
						ess >> rotation;
						it->parameter.f = rotation;
					}
					break;

				case 2:
					{
						it->type = Event::COLOR;
						unsigned int r, g, b;
						ess >> r >> g >> b;
						it->parameter.ui = ((r << 16) + (g << 8) + b);
					}
					break;

				default:
					break;
				}
			}
		}
	}

	file.close();

	return true;
}

void Level::start()
{
	if(!m_musicFileName.empty())
	{
		m_music.stop();
		m_music.play();
	}
}
