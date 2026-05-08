#include "bishop.h"
#include "game.h"
#include "king.h"
#include "knight.h"
#include "pawn.h"
#include "piece.h"
#include "queen.h"
#include "rook.h"
#include "board.h"
#include <iostream>

Board::Board()
{
	// initialize all squares to nullptr
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			Grid[i][j] = nullptr;
		}
	}

	// Place black major pieces on row 0
	Grid[0][0] = new Rook('B', 0, 0);
	Grid[0][1] = new Knight('B', 0, 1);
	Grid[0][2] = new Bishop('B', 0, 2);
	Grid[0][3] = new Queen('B', 0, 3);
	Grid[0][4] = new King('B', 0, 4);
	Grid[0][5] = new Bishop('B', 0, 5);
	Grid[0][6] = new Knight('B', 0, 6);
	Grid[0][7] = new Rook('B', 0, 7);

	// Place black pawns on row 1
	for (int j = 0; j < 8; j++)
	{
		Grid[1][j] = new Pawn('B', 1, j);
	}

	// Place white pawns on row 6
	for (int j = 0; j < 8; j++)
	{
		Grid[6][j] = new Pawn('W', 6, j);
	}

	// Place white major pieces on row 7
	Grid[7][0] = new Rook('W', 7, 0);
	Grid[7][1] = new Knight('W', 7, 1);
	Grid[7][2] = new Bishop('W', 7, 2);
	Grid[7][3] = new Queen('W', 7, 3);
	Grid[7][4] = new King('W', 7, 4);
	Grid[7][5] = new Bishop('W', 7, 5);
	Grid[7][6] = new Knight('W', 7, 6);
	Grid[7][7] = new Rook('W', 7, 7);
}

void Board::displayboard()
{
	using std::cout;
	using std::endl;

	// Column labels
	cout << "   A  B  C  D  E  F  G  H" << endl;

	for (int i = 0; i < 8; i++)
	{
		// Print rank (8..1)
		cout << 8 - i << " ";

		for (int j = 0; j < 8; j++)
		{
			if (Grid[i][j] != nullptr)
			{
				// Print color + symbol, e.g. "WP" or "BR"
				cout << " " << Grid[i][j]->get_colour() << Grid[i][j]->get_symbol();
			}
			else
			{
				cout << " ..";
			}

			// spacing between squares
			if (j < 7)
				cout << " ";
		}
		cout << " " << 8 - i << endl;
	}

	// Column labels again
	cout << "   A  B  C  D  E  F  G  H" << endl;
}
