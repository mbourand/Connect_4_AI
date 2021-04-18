#include "minimax.hpp"

static std::pair<float, size_t>		connect_4_minimax_minimize(const Grid& grid, const size_t& base_turn, const size_t& turn, const size_t& depth, float alpha, float beta);



static inline	size_t change_turn(const size_t& turn)
{
	return (turn == RED_CELL ? YELLOW_CELL : RED_CELL);
}



static std::pair<float, size_t>		connect_4_minimax_maximize(const Grid& grid, const size_t& base_turn, const size_t& turn, const size_t& depth, float alpha, float beta)
{
	auto moves = grid.get_ai_moves(turn);
	size_t win = grid.check_win();

	if (win != EMPTY_CELL)
		return std::make_pair((win == base_turn ? 1000000 : -1000000), -1);
	if (moves.empty())
		return std::make_pair(0, -1);
	if (depth == 0)
		return std::make_pair((rand() % 100) / 100.0f * (rand() % 2 ? 1 : -1), -1);

	float best_value = -std::numeric_limits<float>::infinity();
	size_t best_move = moves.begin()->second;
	for (auto& move_pair : moves)
	{
		const size_t& move = move_pair.second;
		auto branch = connect_4_minimax_minimize(grid.get_after_move(move, turn), base_turn, change_turn(turn), depth - 1, alpha, beta);

		if (branch.first > best_value)
		{
			best_value = branch.first;
			best_move = move;
		}
		alpha = std::max(alpha, best_value);
		if (beta <= alpha)
			break;
	}


	return std::make_pair(best_value, best_move);
}



static std::pair<float, size_t>		connect_4_minimax_minimize(const Grid& grid, const size_t& base_turn, const size_t& turn, const size_t& depth, float alpha, float beta)
{
	auto moves = grid.get_ai_moves(turn);
	size_t win = grid.check_win();

	if (win != EMPTY_CELL)
		return std::make_pair((win == base_turn ? 1000000 : -1000000), -1);
	if (moves.empty())
		return std::make_pair(0, -1);
	if (depth == 0)
		return std::make_pair((rand() % 100) / 100.0f * (rand() % 2 ? 1 : -1), -1);


	float best_value = std::numeric_limits<float>::infinity();
	size_t best_move = moves.begin()->second;
	for (auto& move_pair : moves)
	{
		const size_t& move = move_pair.second;
		auto branch = connect_4_minimax_maximize(grid.get_after_move(move, turn), base_turn, change_turn(turn), depth - 1, alpha, beta);

		if (branch.first < best_value)
		{
			best_value = branch.first;
			best_move = move;
		}
		beta = std::min(beta, best_value);
		if (beta <= alpha)
			break;
	}


	return std::make_pair(best_value, best_move);
}



std::pair<float, size_t>	connect_4_minimax(const Grid& grid, const size_t& turn, const size_t& depth)
{
	return connect_4_minimax_maximize(grid, turn, turn, depth, -std::numeric_limits<float>::infinity(), std::numeric_limits<float>::infinity());
}
