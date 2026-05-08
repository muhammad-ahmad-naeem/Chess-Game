Chess Game OOP\src\game.cpp
#include "game.h"
#include <iostream>
#include <sstream>
#include <cctype>

Game::Game() : Board(), current_player('W') {}

Game::~Game()
{
	// cleanup allocated pieces
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (Grid[i][j] != nullptr)
			{
				delete Grid[i][j];
				Grid[i][j] = nullptr;
			}
		}
	}
}

void Game::play()
{
	std::string line;
	while (true)
	{
		displayboard();
		std::cout << "Current player: " << current_player << "  (enter move like e2 e4 or 'exit')\n> ";
		if (!std::getline(std::cin, line))
			break;

		if (line == "exit" || line == "quit")
			break;

		std::istringstream iss(line);
		std::string from, to;
		if (!(iss >> from >> to))
		{
			std::cout << "Invalid input. Use format: <from> <to> (e.g. e2 e4)\n";
			continue;
		}

		if (!make_move(from, to))
		{
			std::cout << "Move failed. Try again.\n";
			continue;
		}
	}
}

bool Game::make_move(const std::string& from, const std::string& to)
{
	int fr, fc, tr, tc;
	if (!parse_pos(from, fr, fc) || !parse_pos(to, tr, tc))
	{
		std::cout << "Invalid square format. Use a-h and 1-8.\n";
		return false;
	}
	return move_piece(fr, fc, tr, tc);
}

bool Game::move_piece(int fr, int fc, int tr, int tc)
{
	// bounds already validated by parse_pos but double-check
	if (fr < 0 || fr > 7 || fc < 0 || fc > 7 || tr < 0 || tr > 7 || tc < 0 || tc > 7)
		return false;

	Piece* p = Grid[fr][fc];
	if (p == nullptr)
	{
		std::cout << "No piece at source square.\n";
		return false;
	}
	if (p->get_colour() != current_player)
	{
		std::cout << "That's not your piece.\n";
		return false;
	}
	// ask piece if move is valid (uses current piece position internally)
	if (!p->valid_move(tr, tc, Grid))
	{
		std::cout << "Piece cannot move like that.\n";
		return false;
	}
	// cannot capture own piece (piece->valid_move should have checked, but double-check)
	if (Grid[tr][tc] != nullptr && Grid[tr][tc]->get_colour() == p->get_colour())
	{
		std::cout << "Destination occupied by your own piece.\n";
		return false;
	}

	// capture if enemy present
	if (Grid[tr][tc] != nullptr)
	{
		// detect king capture to end game
		if (Grid[tr][tc]->get_symbol() == 'K')
		{
			std::cout << "King captured! Player " << current_player << " wins.\n";
		}
		delete Grid[tr][tc];
		Grid[tr][tc] = nullptr;
	}

	// move piece
	Grid[tr][tc] = p;
	Grid[fr][fc] = nullptr;
	p->set_position(tr, tc);

	// switch turn
	switch_turn();
	return true;
}

bool Game::parse_pos(const std::string& s, int& r, int& c)
{
	if (s.size() != 2)
		return false;
	char file = std::tolower(s[0]);
	char rank = s[1];
	if (file < 'a' || file > 'h' || rank < '1' || rank > '8')
		return false;
	c = file - 'a';
	// board row 0 is rank 8, row 7 is rank 1
	r = 8 - (rank - '0');
	return true;
}

void Game::switch_turn()
{
	current_player = (current_player == 'W') ? 'B' : 'W';
}
