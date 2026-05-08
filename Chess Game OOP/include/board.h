#pragma once
#include "Piece.h"
#include "Bishop.h"
#include "Rook.h"
#include "Knight.h"
#include "Queen.h"
#include "King.h"
#include "Pawn.h"

class Board
{
	Piece* Grid[8][8];
public:
	Board();
	~Board();

	Piece* get_piece(int row, int col) const;

	// Returns true if the move was legal and executed
	bool make_move(int from_row, int from_col, int to_row, int to_col, char current_turn);

	// Returns true if 'color' king is currently in check
	bool is_in_check(char color) const;

	// Returns true if 'color' has no legal move (checkmate or stalemate)
	bool has_no_legal_moves(char color);

	void display() const;
};
