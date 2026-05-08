#include "Board.h"
#include <iostream>
#include <cstring>
using namespace std;

// ─── Constructor: place all pieces ────────────────────────────────────────────
Board::Board()
{
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			Grid[i][j] = nullptr;

	// Black major pieces — row 0
	Grid[0][0] = new Rook('B', 0, 0);
	Grid[0][1] = new Knight('B', 0, 1);
	Grid[0][2] = new Bishop('B', 0, 2);
	Grid[0][3] = new Queen('B', 0, 3);
	Grid[0][4] = new King('B', 0, 4);
	Grid[0][5] = new Bishop('B', 0, 5);
	Grid[0][6] = new Knight('B', 0, 6);
	Grid[0][7] = new Rook('B', 0, 7);

	// Black pawns — row 1
	for (int j = 0; j < 8; j++)
		Grid[1][j] = new Pawn('B', 1, j);

	// White pawns — row 6
	for (int j = 0; j < 8; j++)
		Grid[6][j] = new Pawn('W', 6, j);

	// White major pieces — row 7
	Grid[7][0] = new Rook('W', 7, 0);
	Grid[7][1] = new Knight('W', 7, 1);
	Grid[7][2] = new Bishop('W', 7, 2);
	Grid[7][3] = new Queen('W', 7, 3);
	Grid[7][4] = new King('W', 7, 4);
	Grid[7][5] = new Bishop('W', 7, 5);
	Grid[7][6] = new Knight('W', 7, 6);
	Grid[7][7] = new Rook('W', 7, 7);
}

// ─── Destructor ────────────────────────────────────────────────────────────────
Board::~Board()
{
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
		{
			delete Grid[i][j];
			Grid[i][j] = nullptr;
		}
}

// ─── Getter ────────────────────────────────────────────────────────────────────
Piece* Board::get_piece(int row, int col) const
{
	return Grid[row][col];
}

// ─── Display ──────────────────────────────────────────────────────────────────
void Board::display() const
{
	using std::cout;
	using std::endl;
	cout << "\n    A  B  C  D  E  F  G  H" << endl;

	for (int i = 0; i < 8; i++)
	{
		cout << 8 - i << " "; // Rank number

		for (int j = 0; j < 8; j++)
		{
			if (Grid[i][j] != nullptr)
				cout << " " << Grid[i][j]->get_colour() << Grid[i][j]->get_symbol();
			else
				cout << " ..";

			
		}
		cout << "  " << 8 - i << endl;
	}
	cout << "    A  B  C  D  E  F  G  H\n" << endl;
}
// ─── is_in_check ──────────────────────────────────────────────────────────────
// Find 'color' king, then ask every opponent piece if it can reach the king.
bool Board::is_in_check(char color) const
{
	// Step 1: find the king
	int king_row = -1, king_col = -1;
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			if (Grid[i][j] != nullptr &&
				Grid[i][j]->get_colour() == color &&
				Grid[i][j]->get_symbol() == 'K')
			{
				king_row = i;
				king_col = j;
			}

	if (king_row == -1) return false;   // safety (should never happen)

	// Step 2: ask every enemy piece if it attacks the king square
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			if (Grid[i][j] != nullptr && Grid[i][j]->get_colour() != color)
				if (Grid[i][j]->valid_move(king_row, king_col, (Piece * (*)[8])Grid))
					return true;

	return false;
}

// ─── make_move ────────────────────────────────────────────────────────────────
bool Board::make_move(int fr, int fc, int tr, int tc, char current_turn)
{
	// Bounds check
	if (fr < 0 || fr > 7 || fc < 0 || fc > 7 ||
		tr < 0 || tr > 7 || tc < 0 || tc > 7)
		return false;

	// Must have a piece at source
	if (Grid[fr][fc] == nullptr)
		return false;

	// Piece must belong to current player
	if (Grid[fr][fc]->get_colour() != current_turn)
		return false;

	// Ask the piece itself whether the geometry is legal
	if (!Grid[fr][fc]->valid_move(tr, tc, (Piece * (*)[8])Grid))
		return false;

	// ── Simulate the move ────────────────────────────────────────────────
	Piece* moving_piece = Grid[fr][fc];
	Piece* captured = Grid[tr][tc];

	Grid[tr][tc] = moving_piece;
	Grid[fr][fc] = nullptr;
	moving_piece->set_position(tr, tc);

	// ── Own king must NOT be in check after the move ─────────────────────
	if (is_in_check(current_turn))
	{
		// Undo
		Grid[fr][fc] = moving_piece;
		Grid[tr][tc] = captured;
		moving_piece->set_position(fr, fc);
		return false;
	}

	// ── Commit: delete captured piece ────────────────────────────────────
	if (captured != nullptr)
	{
		captured->capture();
		delete captured;
	}

	// Mark pawn as having moved (enables double-step restriction)
	if (moving_piece->get_symbol() == 'P')
		static_cast<Pawn*>(moving_piece)->set_moved_before();

	return true;
}

// ─── has no legal_moves ───────────────────────────────────────────────────────
// Try every piece of 'color' against every destination square.
// If even one move leaves the king safe, return false (has moves).
bool Board::has_no_legal_moves(char color)
{
	for (int fr = 0; fr < 8; fr++)
		for (int fc = 0; fc < 8; fc++)
		{
			if (Grid[fr][fc] == nullptr) continue;
			if (Grid[fr][fc]->get_colour() != color) continue;

			for (int tr = 0; tr < 8; tr++)
				for (int tc = 0; tc < 8; tc++)
				{
					if (!Grid[fr][fc]->valid_move(tr, tc, (Piece * (*)[8])Grid))
						continue;

					// Simulate
					Piece* moving = Grid[fr][fc];
					Piece* captured = Grid[tr][tc];
					Grid[tr][tc] = moving;
					Grid[fr][fc] = nullptr;
					moving->set_position(tr, tc);

					bool still_in_check = is_in_check(color);

					// Undo
					Grid[fr][fc] = moving;
					Grid[tr][tc] = captured;
					moving->set_position(fr, fc);

					if (!still_in_check)
						return false;   // found at least one legal escape
				}
		}
	return true;  // no legal move found
}
