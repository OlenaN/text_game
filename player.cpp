#include <ncurses.h>
#include <string>
#include <iostream>
#include <unistd.h>
#include "player.h"

using namespace std;

void Player::add_name(string new_name) {
    name = new_name;
}

string Player::get_name(void) {
    return name;
}
