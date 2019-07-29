#include <ncurses.h>
#include <string>
#include <iostream>
#include <unistd.h>
#include <fstream>
#include "state.h"
#include "screen.h"
#include "json.hpp"
#include "main.h"
using namespace std;
using json = nlohmann::json;



int main () {

	/**State state;
	Screen screen;

	screen.initialize();
	screen.create_text_window();
	screen.create_choice_window();

	screen_loop(screen, state);

	json j2 = 1;*/

	fill_states();

	return 0;


};

int screen_loop (Screen screen, State state) {

	while (1) {

		screen.update_text(state.get_text());
		
		if (state.check_if_request()) {
			screen.request_data(state.get_request());
		} else {
			screen.update_choices(state.get_num_choices(), state.get_choices());
		}

	}

};


void fill_states(void) {

	std::ifstream ifs("data.json");
	json j = json::parse(ifs);	
	ifs.close();

	State * statelist = new State[j["statelist"].size() + 1];

	for (int x = 0; x < j["statelist"].size(); x++) {

		json item = j["statelist"][x];

		int state_num = item["state"];
		State state = *(new State);
		statelist[x] = state;

		string text = item["text"];
		string type = item["type"];
		bool is_request = item["is_request"].get<bool>();
		string request = "";
		int num_choices = 1;
		string * choices = NULL;

		if (is_request == true) {
			string request = item["request"];
		} else {
			choices = json_to_str_list(item["choices"]);
			num_choices = item["choices"].size();
		}

		int  * next_states = json_to_int_list(item["next_states"]);

		state.create(type, text, request, num_choices, choices, next_states, is_request);

		int value = state.get_next_state(0);
		if (value) {
			//std::cout << *(value) << "\n";
		}
	}

	
};



int * json_to_int_list (json j) {

	int * final_list = new int[j.size()];

	int i = 0;
	for (auto &item : j) {
		*(final_list + i) = item.get<int>();
		//std::cout << *(final_list + i);
	}

};

string * json_to_str_list (json j) {

	string * final_list = new string[j.size()];

	int i = 0;
	for (auto &item : j) {
		*(final_list + i) = item.get<string>();
	}

};