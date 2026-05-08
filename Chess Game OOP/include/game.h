#pragma once
#include "Board.h"

class Game
{
	Board board;
	char  current_turn;   // 'W' or 'B'
	bool  game_over;

	// Convert chess notation like "e2" -> row/col indices
	bool parse_square(const string& s, int& row, int& col) const;

public:
	Game();
	void run();
};
