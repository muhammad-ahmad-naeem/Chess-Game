#include "Game.h"
#include <iostream>
#include <cctype>
using namespace std;

Game::Game() : player1("", 'W'), player2("", 'B'), current_turn('W'), game_over(false) {
    string name1, name2;
    cout << "Enter White player name: ";
    getline(cin, name1);
    cout << "Enter Black player name: ";
    getline(cin, name2);
    player1 = Player(name1, 'W');
    player2 = Player(name2, 'B');
}

Game::~Game() {}

bool Game::parse_square(const string& s, int& row, int& col) const {
    try {
        if (s.empty()) {
            throw EmptyMoveException();
        }
        if (s.size() < 2) {
            throw InvalidSquareFormatException(s);
        }
        char file = tolower(s[0]);
        char rank = s[1];
        if (file < 'a' || file > 'h') {
            throw InvalidFileException(file);
        }
        if (rank < '1' || rank > '8') {
            throw InvalidRankException(rank);
        }
        col = file - 'a';
        row = 8 - (rank - '0');
        return true;
    }
    catch (MoveException& e) {
        cerr << e.what() << endl;
        return false;
    }
    catch (exception& e) {
        cerr << "Unexpected error in parse_square: " << e.what() << endl;
        return false;
    }
}

void Game::run() {
    cout << "========================================\n";
    cout << "               CHESS  \n";
    cout << "========================================\n";
    cout << "  Enter moves like:  e2 e4   (from  to)\n";
    cout << "  Type 'quit' to exit.\n\n";
    while (!game_over) {
        try {
            board.display();
            bool in_check = board.is_in_check(current_turn);
            bool no_moves = board.has_no_legal_moves(current_turn);
            if (no_moves) {
                if (in_check) {
                    char winner = (current_turn == 'W') ? 'B' : 'W';
                    cout << "CHECKMATE!  "
                        << (winner == 'W' ? "White" : "Black")
                        << " wins!\n";
                }
                else {
                    cout << "STALEMATE!  It's a draw.\n";
                }
                game_over = true;
                break;
            }
            if (in_check) {
                cout << ">>> " << (current_turn == 'W' ? "White" : "Black")
                    << " is in CHECK!\n";
            }
            string whose_turn = (current_turn == 'W')
                ? player1.get_name()
                : player2.get_name();
            cout << whose_turn
                << " ("
                << (current_turn == 'W' ? "White" : "Black")
                << ") enter move (e.g. e2 e4) or quit: ";
            string from_str, to_str;
            cin >> from_str;
            if (from_str == "quit") {
                throw QuitGameException();
            }
            cin >> to_str;
            if (from_str.empty() || to_str.empty()) {
                throw EmptyMoveException();
            }
            int fr, fc, tr, tc;
            if (!parse_square(from_str, fr, fc)) {
                cout << "  Invalid source square. Try again.\n";
                continue;
            }
            if (!parse_square(to_str, tr, tc)) {
                cout << "  Invalid destination square. Try again.\n";
                continue;
            }
            if (!board.make_move(fr, fc, tr, tc, current_turn)) {
                throw IllegalMoveException(from_str, to_str);
            }
            current_turn = (current_turn == 'W') ? 'B' : 'W';
        }
        catch (QuitGameException& e) {
            cout << "Game ended by player.\n";
            game_over = true;
            break;
        }
        catch (IllegalMoveException& e) {
            cerr << e.what() << endl;
            cout << "  Please try again.\n";
            continue;
        }
        catch (MoveException& e) {
            cerr << e.what() << endl;
            cout << "  Please try again.\n";
            continue;
        }
        catch (exception& e) {
            cerr << "Unexpected error occured in game loop: " << e.what() << endl;
            cout << "  Please try again.\n";
            continue;
        }
    }
    board.display();
    cout << "Thanks for playing!\n";
}
