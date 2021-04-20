#ifndef GRID_HPP
#define GRID_HPP

#include "globals.hpp"
#include <stdexcept>
#include <type_traits>
#include <array>
#include <list>
#include <iostream>
#include <map>

/*
** Chaque cell = 2 bits : 00 -> Vide, 01 -> Rouge, 10 -> Jaune
*/

#define EMPTY_CELL 0
#define RED_CELL 1
#define YELLOW_CELL 2

struct Turn
{
	size_t color;
	size_t count;

	void next_turn()
	{
		color = (color == RED_CELL ? YELLOW_CELL : RED_CELL);
		count++;
	}
};

class Grid
{
	std::array<size_t, GRID_WIDTH> _cells;
	uint8_t _move_count;

	private:

		/**
		 * @brief Retourne le masque binaire pour la ligne
		 *
		 * @param y
		 * @return le masque binaire pour la ligne
		 */
		inline size_t get_mask(const size_t& y) const
		{
			return (1 << (y * 2 + 1)) | (1 << (y * 2));
		}

		size_t check_win_raw(size_t x, const size_t& y, const size_t& val) const;
		size_t check_win_col(const size_t& x, size_t y, const size_t& val) const;
		size_t check_win_diag(size_t x, size_t y, const size_t& val) const;

	public:
		Grid()
		{
			std::fill(_cells.begin(), _cells.end(), 0);
			_move_count = 0;
		}

		Grid(const Grid& other);
		Grid& operator=(const Grid& other);


		/**
		 * @brief Change la valeur de la cellule à l'emplacement x, y
		 *
		 * @param x
		 * @param y
		*/
		inline void set(const size_t& x, const size_t& y, const size_t& val)
		{
			_cells[x] = (_cells[x] & ~get_mask(y)) | (val << (y * 2));
		}

		/**
		 * @brief Equivalent à un operator[] d'un tableau 2D
		 *
		 * @param x
		 * @param y
		 * @return La couleur de la cellule à l'emplacement x, y
		*/
		inline size_t get(const size_t& x, const size_t& y) const
		{
			return ((_cells[x] & get_mask(y)) >> (y * 2));
		}

		bool play_move(const size_t& x, const size_t& val);
		Grid get_after_move(const size_t& move, const size_t& val) const;
		std::multimap<float, size_t, std::greater<float>> get_ai_moves(const size_t& turn) const;
		size_t check_win() const;
		std::list<std::array<int, 2>> get_winning_positions(const size_t& turn);

		uint8_t get_move_count() const;

		void print() const;
};

#endif
