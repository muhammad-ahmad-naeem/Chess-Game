#include "Player.h"
Player::Player(string name, char color) 
{
    this->name = name;
    this->color = color;
}
string Player::get_name()  const 
{ 
    return name;
}
char   Player::get_color() const 
{
    return color; 
}
bool Player::get_input(string& from_str, string& to_str) const 
{
    if (color == 'W')
        cout << "White";
    else
        cout << "Black";
    cout << " (" << name << ") enter move" << " (e.g. e2 e4) or 'quit': ";
    cin >> from_str;
    // Let Game.h handle quit — just pass it through
    if (from_str == "quit") 
    {
        to_str = "";
        return true;
    }
    cin >> to_str;
    // Basic length check
    if (from_str.length() != 2 || to_str.length() != 2) 
    {
        cout << "  Wrong format! Use something like: e2 e4\n";
        return false;
    }
    return true;
}
