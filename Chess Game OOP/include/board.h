#pragma once
#include "piece.h"

class Board
{
protected:
	Piece* Grid[8][8];
public:
	Board();
	void displayboard();
};
