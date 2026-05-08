#include "Game.h"
#include <iostream>
#include <cctype>
using namespace std;

Game::Game() : current_turn('W'), game_over(false) {}

// Convert "e2" -> row=6, col=4  (column a=0 .. h=7, rank 1=row7 .. 8=row0)
bool Game::parse_square(const string& s, int& row, int& col) const
{
	if (s.size() < 2) return false;
	char file = tolower(s[0]);
	char rank = s[1];
	if (file < 'a' || file > 'h') return false;
	if (rank < '1' || rank > '8') return false;
	col = file - 'a';
	row = 8 - (rank - '0');
	return true;
}

void Game::run()
{
	cout << "========================================\n";
	cout << "     CHESS — OOP Lab Project  NUCES\n";
	cout << "========================================\n";
	cout << "  Enter moves like:  e2 e4   (from  to)\n";
	cout << "  Type 'quit' to exit.\n\n";

	while (!game_over)
	{
		board.display();

		// ── Check / Checkmate / Stalemate detection ───────────────────────
		bool in_check = board.is_in_check(current_turn);
		bool no_moves = board.has_no_legal_moves(current_turn);

		if (no_moves)
		{
			if (in_check)
			{
				char winner = (current_turn == 'W') ? 'B' : 'W';
				cout << "CHECKMATE!  "
				     << (winner == 'W' ? "White" : "Black")
				     << " wins!\n";
			}
			else
			{
				cout << "STALEMATE!  It's a draw.\n";
			}
			game_over = true;
			break;
		}

		if (in_check)
			cout << ">>> " << (current_turn == 'W' ? "White" : "Black")
			     << " is in CHECK!\n";

		cout << (current_turn == 'W' ? "White" : "Black") << "'s turn > ";

		string from_str, to_str;
		cin >> from_str;

		if (from_str == "quit")
		{
			cout << "Game ended by player.\n";
			break;
		}

		cin >> to_str;

		int fr, fc, tr, tc;
		if (!parse_square(from_str, fr, fc) || !parse_square(to_str, tr, tc))
		{
			cout << "  Bad input. Use format like: e2 e4\n";
			continue;
		}

		if (!board.make_move(fr, fc, tr, tc, current_turn))
		{
			cout << "  Illegal move! Try again.\n";
			continue;
		}

		// Flip turn
		current_turn = (current_turn == 'W') ? 'B' : 'W';
	}

	board.display();
	cout << "Thanks for playing!\n";
}
