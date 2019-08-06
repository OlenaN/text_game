#include <ncurses.h>
#include <string>
#include <iostream>
#include <unistd.h>
#include "state.h"

using namespace std;

int State::create(string type_val, string text_val, string request_val, int num_choices_val, string * choices_val, int * next_states_val, bool is_request_val) {
    type = type_val;
    text = text_val;
    request = request_val;
    num_choices = num_choices_val;
    choices = choices_val;
    next_states = next_states_val;
    is_request = is_request_val;

    return 0;
}

string State::get_type(void) {
    return type;
}

string State::get_text(void) {
    return text;
}

string State::get_request(void) {
    return request;
}

string * State::get_choices(void) {
    return choices;
}

int State::get_num_choices(void) {
    return num_choices;
}

int State::get_next_state(int index) {
    return *(next_states + index);
}

bool State::check_if_request() {
    return is_request;
}
