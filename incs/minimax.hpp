#ifndef MINIMAX_HPP
#define MINIMAX_HPP

#include <map>
#include <cmath>
#include "Grid.hpp"
#include <limits>


std::pair<float, size_t>	connect_4_minimax(const Grid& grid, const size_t& turn, const size_t& depth);

#endif
