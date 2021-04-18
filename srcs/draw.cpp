#include <SFML/Graphics.hpp>
#include "globals.hpp"
#include "Grid.hpp"

static void		draw_cells(sf::RenderWindow& window, const Grid& grid)
{
	static sf::Color colors[] = { sf::Color(EMPTY_CELL_COLOR), sf::Color(RED_CELL_COLOR), sf::Color(YELLOW_CELL_COLOR) };
	static sf::CircleShape cell;

	cell.setRadius(CELL_SIZE / 2.0);

	for (unsigned x = 0; x < GRID_WIDTH; x++)
	{
		for (unsigned y = 0; y < GRID_HEIGHT; y++)
		{
			cell.setPosition({ static_cast<float>(x * CELL_SIZE + CELL_DRAW_OFFSET * (x + 1)), static_cast<float>(y * CELL_SIZE + CELL_DRAW_OFFSET * (y + 1)) });
			cell.setFillColor(colors[grid.get(x, y)]);
			window.draw(cell);
		}
	}
}



/**
 * @brief Gère tout ce qu'il faut dessiner dans la fenêtre
 *
 * @param window
 */
void	update_display(sf::RenderWindow& window, const Grid& grid)
{
	window.clear(sf::Color(BACKGROUND_COLOR));
	draw_cells(window, grid);
	window.display();
}
