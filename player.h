#ifndef PLAYER
#define PLAYER
#include <ncurses.h>
#include <string>
#include <iostream>
#include <unistd.h>
using namespace std;


class Player {

    private:

  	string name;

    public:

    void add_name(string new_name);
    string get_name(void);

};

#endif // PLAYER