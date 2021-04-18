#include <SFML/Graphics.hpp>
#include "globals.hpp"
#include "draw.hpp"
#include "user_input.hpp"
#include "Grid.hpp"

/**
 * @brief Gère les events dans le projet
 *
 * @param window
 * @return Vrai si le programme doit continuer, faux sinon
 */
bool	event_loop(sf::RenderWindow& window)
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		switch (event.type)
		{
			case sf::Event::Closed:
				return false;
		}
	}
	return true;
}

int		main()
{
	srand(time(NULL));
	sf::RenderWindow window;
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	settings.depthBits = 24;
	settings.stencilBits = 8;
	settings.majorVersion = 3;
	settings.minorVersion = 1;
	Grid grid;

	window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Connect 4", sf::Style::Default, settings);

	bool running = true;
	while (running)
	{
		update_display(window, grid);
		handle_user_input(window, grid);
		running = event_loop(window);
	}
}
