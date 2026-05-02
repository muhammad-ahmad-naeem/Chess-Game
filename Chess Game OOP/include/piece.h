#pragma once
#include <iostream>
#include <cstring>
#include <string>
using namespace std;
class piece
{
	char colour;
	int row_num;
	int column_num;
	char symbol;
	bool is_alive;
public:
	piece();
	piece(char color, int row, int col, char symbol);
	char get_colour();
	int get_row_num();
	int get_column_num();
	char get_symbol();
	bool get_is_alive();
	void set_position(int r, int c);
	void capture();
	virtual bool valid_move(int row, int column, piece* board[8][8]) = 0;  // pure virtual function // why piece*? because it is an abstract class we can't create just piece array here and we have to set nullptr if square is empty and only pointer can do that
	virtual ~piece();
};
