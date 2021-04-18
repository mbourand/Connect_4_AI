#include "Grid.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <limits>
#include "minimax.hpp"
#include "utils.hpp"

static bool	handle_mouse_input(const sf::Vector2i& mouse_pos, Grid& grid, Turn& turn)
{
	static bool clicked = false;

	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
	{
		if (clicked)
			return false;
		clicked = true;
	}
	else
	{
		clicked = false;
		return false;
	}
	if (mouse_pos.x < 0 || mouse_pos.y < 0 || mouse_pos.x >= WINDOW_WIDTH || mouse_pos.y >= WINDOW_HEIGHT)
		return false;

	if (!grid.play_move(mouse_pos.x / CELL_SIZE, turn.color))
		return false;
	turn.next_turn();

	return true;
}

static void	handle_keyboard_input(Grid& grid, Turn& turn)
{
	static bool space_pressed = false;
	static size_t turn_count = 0;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		if (space_pressed)
			return;
		space_pressed = true;
	}
	else
	{
		space_pressed = false;
		return;
	}

	if (!play_ai_move(grid, turn))
		return;
	turn.next_turn();
}


/**
 * @brief Gère les input clavier/souris
 *
 * @param window
 * @param grid
 */
void	handle_user_input(const sf::RenderWindow& window, Grid& grid)
{
	static bool next_frame_ai = false;
	static Turn turn = { RED_CELL, 0 };
	sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);

	if (next_frame_ai)
	{
		play_ai_move(grid, turn);
		turn.next_turn();
		next_frame_ai = false;
		return;
	}

	next_frame_ai = handle_mouse_input(mouse_pos, grid, turn);
	handle_keyboard_input(grid, turn);
}

