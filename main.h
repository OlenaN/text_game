#ifndef MAIN
#define MAIN
#include <string>
#include "state.h"
#include "screen.h"
#include "json.hpp"
using namespace std;
using json = nlohmann::json;

int screen_loop (Screen screen, State state, Player player);

void fill_states (void);

int * json_to_int_list (json j);

string * json_to_str_list (json j);

string replace_name(string text, string name);

#endif // MAIN