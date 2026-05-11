#pragma once
#include "Board.h"
#include "Player.h"
class Game
{
	Board board;
	Player player1;    // White player
	Player player2;    // Black player
	char  current_turn;   // 'W' or 'B'
	bool  game_over;

	// Convert chess notation like "e2" -> row/col indices
	bool parse_square(const string& s, int& row, int& col) const;

public:
	Game();
	void run();
};
