#pragma once
#include<iostream>
#include<string>
#include<stdexcept>
#include"Board.h"
#include"Player.h"
using namespace std;

class MoveException : public exception {
protected:
    string errmsg;
public:
    MoveException(string msg) : errmsg(msg) {}
    virtual const char* what() const noexcept {
        return errmsg.c_str();
    }
};

class InvalidSquareFormatException : public MoveException {
public:
    InvalidSquareFormatException(string sq) : MoveException("Error: Invalid square format '" + sq + "' - use format like 'e2'!") {}
};

class InvalidFileException : public MoveException {
public:
    InvalidFileException(char f) : MoveException("Error: File '" + string(1, f) + "' invalid - must be a-h!") {}
};

class InvalidRankException : public MoveException {
public:
    InvalidRankException(char r) : MoveException("Error: Rank '" + string(1, r) + "' invalid - must be 1-8!") {}
};

class EmptyMoveException : public MoveException {
public:
    EmptyMoveException() : MoveException("Error: Move input cannot be empty!") {}
};

class IllegalMoveException : public MoveException {
public:
    IllegalMoveException(string from, string to) : MoveException("Error: Move from " + from + " to " + to + " is illegal!") {}
};

class QuitGameException : public exception {
public:
    virtual const char* what() const noexcept {
        return "Game quit by player";
    }
};

class Game {
private:
    Player player1;
    Player player2;
    Board board;
    char current_turn;
    bool game_over;
    bool parse_square(const string& s, int& row, int& col) const;
public:
    Game();
    void run();
    ~Game();
};
