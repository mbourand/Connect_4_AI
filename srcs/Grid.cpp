#include "Grid.hpp"
#include <list>
#include <map>

Grid& Grid::operator=(const Grid& other)
{
	_cells = other._cells;
	return *this;
}

Grid::Grid(const Grid& other)
{
	*this = other;
}


/**
 * @brief Lance l'algorithme de gravité pour jouer les coups
 *
 * @param x
 * @return true si le coup est légal, faux sinon
 */
bool Grid::play_move(const size_t& x, const size_t& val)
{
	if (get(x, 0) != EMPTY_CELL)
		return false;

	size_t y = 0;
	while (y < GRID_HEIGHT && get(x, y) == 0)
		y++;

	set(x, y - 1, val);
	return true;
}


/**
 * @brief Retourne une copie de la grille après un coup sur la colonne move
 *
 * @param move
 * @param val
 * @return Une copie de la grille après un coup sur la colonne move
 */
Grid Grid::get_after_move(const size_t& move, const size_t& val) const
{
	Grid cpy(*this);
	cpy.play_move(move, val);
	return cpy;
}



std::list<std::array<int, 2>> Grid::get_winning_positions(const size_t& turn)
{
	std::list<std::array<int, 2>> res;

	for (int x = 0; x < GRID_WIDTH; x++)
	{
		for (int y = 0; y < GRID_HEIGHT; y++)
		{
			if (!get(x, y) == EMPTY_CELL)
				continue;
			set(x, y, turn);
			if (check_win() == turn)
				res.push_back({ x, y });
			set(x, y, EMPTY_CELL);
		}
	}

	return res;
}


/**
 * @brief Retourne la liste des coups légaux dans la grille
 *
 * @return La liste des coups légaux dans la grille
 */
std::multimap<size_t, size_t, std::greater<size_t>> Grid::get_ai_moves(const size_t& turn) const
{
	std::multimap<size_t, size_t, std::greater<size_t>> moves;

	for (int x = 0; x < GRID_WIDTH; x++)
	{
		if (get(x, 0) != EMPTY_CELL)
			continue;
		moves.insert(std::make_pair(get_after_move(x, turn).get_winning_positions(turn).size(), x));
	}

	return moves;
}


/**
 * @brief Vérifie si la partie est gagnée et qui l'a gagnée
 *
 * @return EMPTY_CELL si la partie n'est pas gagnée, YELLOW_CELL si les jaunes ont gagné, RED_CELL si les rouges ont gagné
 */
size_t Grid::check_win() const
{
	for (size_t y = 0; y < GRID_HEIGHT; y++)
	{
		for (size_t x = 0; x < GRID_WIDTH; x++)
		{
			size_t val = get(x, y);
			if (val == EMPTY_CELL)
				continue;

			size_t res;
			if ((res = check_win_raw(x, y, val)) != EMPTY_CELL || (res = check_win_col(x, y, val)) != EMPTY_CELL || (res = check_win_diag(x, y, val)) != EMPTY_CELL)
				return res;
		}
	}
	return EMPTY_CELL;
}

size_t Grid::check_win_raw(size_t x, const size_t& y, const size_t& val) const
{
	size_t i = 0;
	for (; i < 4 && x < GRID_WIDTH; i++, x++)
		if (get(x, y) != val)
			return EMPTY_CELL;

	if (x >= GRID_WIDTH && i < 4)
		return EMPTY_CELL;

	return val;
}

size_t Grid::check_win_col(const size_t& x, size_t y, const size_t& val) const
{
	size_t i = 0;
	for (; i < 4 && y < GRID_HEIGHT; i++, y++)
		if (get(x, y) != val)
			return EMPTY_CELL;

	if (y >= GRID_HEIGHT && i < 4)
		return EMPTY_CELL;

	return val;
}

size_t Grid::check_win_diag(size_t x, size_t y, const size_t& val) const
{
	int y_tmp = y;
	int x_tmp = x;

	for (size_t i = 0; i < 4 && y < GRID_HEIGHT && x < GRID_WIDTH; i++, y++, x++)
	{
		if (get(x, y) != val)
			break;
		if (i == 3)
			return val;
	}

	for (size_t i = 0; i < 4 && y_tmp < GRID_HEIGHT && x_tmp >= 0; i++, y_tmp++, x_tmp--)
	{
		if (get(x_tmp, y_tmp) != val)
			break;
		if (i == 3)
			return val;
	}

	return EMPTY_CELL;
}



void	Grid::print() const
{
	for (size_t y = 0; y < GRID_HEIGHT; y++)
	{
		for (size_t x = 0; x < GRID_WIDTH; x++)
		{
			size_t val = get(x, y);
			switch (val)
			{
				case EMPTY_CELL:
					std::cout << '.';
					break;
				case RED_CELL:
					std::cout << 'O';
					break;
				case YELLOW_CELL:
					std::cout << 'X';
					break;
			}
		}
		std::cout << '\n';
	}
	size_t val = check_win();
	std::cout << (val == 0 ? "Pas win" : (val == 1 ? "Rouge win" : "Jaune win")) << std::endl << std::endl;
}
