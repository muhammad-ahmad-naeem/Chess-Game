#include "Pieces.h"
pawn::pawn()
{
	this->moved_before = false;
}
pawn::pawn(char color, int row, int col) : piece(color, row, col, 'P')
{
	this->moved_before = false;
}
void pawn::set_moved_before()
{
	this->moved_before = true;
}
bool pawn::valid_move(int row, int col, piece* board[8][8]) // to row , to column
{
	int from_row = get_row_num();
	int from_column = get_column_num();
	char color = get_colour();
	int direction = 0;
	if (direction == 'W') // if white then moves up row decrease and vice versa
	{
		direction = -1;
	}
	else
		direction = 1;
	// Move one square
	if (from_column == col && row == from_column + direction && board[row][col] == nullptr)
		return true;
	// Move two squares
	if (col == from_column && row == from_row + 2 * direction && board[from_row + direction][from_column] == nullptr
		&& board[row][col] == nullptr
		)
		return true;
	// diagonally
	if (row == from_row + direction && abs(col - from_column) == 1 &&
		board[row][col] == nullptr && board[row][col]->get_colour() != get_colour()) // can cpatue enemy piece
		return true;
	return false;
}

