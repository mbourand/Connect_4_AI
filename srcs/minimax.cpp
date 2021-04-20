#include "minimax.hpp"
#include <unordered_map>
#include <numeric>

static inline size_t	change_turn(const size_t& turn)
{
	return (turn == RED_CELL ? YELLOW_CELL : RED_CELL);
}



static std::pair<float, size_t>		connect_4_negamax(const Grid& grid, const size_t& base_turn, const size_t& turn, const size_t& depth, float alpha, float beta)
{
	if (grid.get_move_count() == GRID_WIDTH * GRID_HEIGHT)
		return std::make_pair(0, -1);
	if (depth == 0)
		return std::make_pair((rand() % 100) / 110.0f * (rand() % 2 ? 1 : -1), -1);

	int min_theoretical_score = -(GRID_WIDTH * GRID_HEIGHT - 2 - grid.get_move_count()) / 2;
	if (beta < min_theoretical_score)
	{
		beta = min_theoretical_score;
		if (beta <= alpha)
			return std::make_pair(beta, -1);
	}


	int max_theoretical_score = (GRID_WIDTH * GRID_HEIGHT - 1 - grid.get_move_count()) / 2;
	if (alpha > max_theoretical_score)
	{
		alpha = max_theoretical_score;
		if (beta <= alpha)
			return std::make_pair(alpha, -1);
	}


	auto moves = grid.get_ai_moves(turn);

	float best_value = -std::numeric_limits<float>::infinity();
	size_t best_move = moves.begin()->second;
	for (auto& move_pair : moves)
	{
		const size_t& move = move_pair.second;

		Grid next_grid = grid.get_after_move(move, turn);
		if (next_grid.check_win() == turn)
			return std::make_pair((GRID_WIDTH * GRID_HEIGHT + 1 - next_grid.get_move_count()) / 2, move);

		auto branch = connect_4_negamax(next_grid, base_turn, change_turn(turn), depth - 1, -beta, -alpha);

		if (-branch.first > best_value)
		{
			best_value = -branch.first;
			best_move = move;
		}
		alpha = std::max(alpha, best_value);
		if (beta <= alpha)
			break;
	}

	return std::make_pair(best_value, best_move);
}

size_t	get_best_move(const Grid& grid, const size_t& turn, const size_t& depth)
{
	return connect_4_negamax(grid, turn, turn, depth, -std::numeric_limits<float>::infinity(), std::numeric_limits<float>::infinity()).second;
}
