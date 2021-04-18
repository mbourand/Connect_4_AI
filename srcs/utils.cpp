#include "utils.hpp"
#include "Grid.hpp"
#include "minimax.hpp"
#include <cmath>

/**
 * @brief Joue un coup généré par l'ia
 *
 * @return vrai si le coup est légal, faux sinon
 */
bool	play_ai_move(Grid& grid, const Turn& turn)
{
	auto ai_move = connect_4_minimax(grid, turn.color, std::min(8 + (turn.count / 3), 8ull));
	if (ai_move.second >= GRID_WIDTH)
		return false;

	return grid.play_move(ai_move.second, turn.color);
}
