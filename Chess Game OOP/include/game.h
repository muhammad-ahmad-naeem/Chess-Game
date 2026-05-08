#pragma once
#include "board.h"
#include <string>

class Game : public Board
{
public:
	Game();
	~Game();
	void play();                    // main loop for two players (hotseat)
	bool make_move(const std::string& from, const std::string& to);

private:
	char current_player;                           // 'W' or 'B'
	bool move_piece(int fr, int fc, int tr, int tc);
	bool parse_pos(const std::string& s, int& r, int& c);
	void switch_turn();
};
