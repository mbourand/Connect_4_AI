#ifndef MINIMAX_HPP
#define MINIMAX_HPP

#include <map>
#include <cmath>
#include "Grid.hpp"
#include <limits>


size_t	get_best_move(const Grid& grid, const size_t& turn, const size_t& depth);

#endif
