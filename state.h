#ifndef STATE
#define STATE
#include <ncurses.h>
#include <string>
#include <iostream>
#include <unistd.h>
using namespace std;


class State {

    private:

    string type;
    string text;
    string request;
    int num_choices;
    string * choices;
    int * next_states;
    bool is_request;

    public:

    int create (string type, string text, string request, int num_choices, string * choices, int * next_states, bool is_request);
    string get_text(void);
    string get_request(void);
    string * get_choices(void);
    int get_num_choices(void);
    int get_next_state(int index);
    bool check_if_request();

};

#endif // STATE