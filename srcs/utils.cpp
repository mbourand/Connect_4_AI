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
	size_t ai_move = get_best_move(grid, turn.color, 12);
	if (ai_move >= GRID_WIDTH)
		return false;

	return grid.play_move(ai_move, turn.color);
}
