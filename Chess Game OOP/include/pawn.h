#pragma once
#include "piece.h"
#include <cmath>
using namespace std;
class pawn : public piece
{
	bool moved_before;
public:
	pawn();
	pawn(char color, int row, int col);
	void set_moved_before();
	bool valid_move(int row, int col, piece* board[8][8]) override;
};
