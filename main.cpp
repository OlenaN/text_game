#include <ncurses.h>
#include <string>
#include <iostream>
#include <unistd.h>
#include <fstream>
#include <regex>
#include "state.h"
#include "screen.h"
#include "player.h"
#include "json.hpp"
#include "main.h"
using namespace std;
using json = nlohmann::json;


State * statelist;

int main () {

	State state;
	Screen screen;
	Player player;

	screen.initialize();
	screen.create_text_window();
	screen.create_choice_window();


	json j2 = 1;
	
	fill_states();

	State start_state = *(statelist);

	screen_loop(screen, start_state, player);

	return 0;


};

int screen_loop (Screen screen, State state, Player player) {

	while (1) {

		screen.update_text(replace_name(state.get_text(), player.get_name()));
		
		int next_state_num;
		
		if (state.check_if_request()) {
			string data = screen.request_data(state.get_request());
			next_state_num = state.get_next_state(0);

			if (state.get_type() == "NAME") {
				player.add_name(data);
			}

		} else {
			int choice = screen.update_choices(state.get_num_choices(), state.get_choices());
			next_state_num = state.get_next_state(choice);
		}

		state = *(statelist + next_state_num);

	}

};


void fill_states(void) {

	std::ifstream ifs("data.json");
	json j = json::parse(ifs);	
	ifs.close();

	statelist = new State[j["statelist"].size() + 1];

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
			request = item["request"];
		} else {
			choices = json_to_str_list(item["choices"]);
			num_choices = item["choices"].size();
		}

		int  * next_states = json_to_int_list(item["next_states"]);

		state.create(type, text, request, num_choices, choices, next_states, is_request);

		*(statelist + x) = state;
	}

	
};



int * json_to_int_list (json j) {

	int * final_list = new int[j.size()];

	int i = 0;
	for (auto &item : j) {
		*(final_list + i) = item.get<int>();
		i++;
	}

	return final_list;

};

string * json_to_str_list (json j) {

	string * final_list = new string[j.size()];

	int i = 0;
	for (auto &item : j) {
		*(final_list + i) = item.get<string>();
		i++;
	}

	return final_list;
};


string replace_name(string text, string name) {
	return regex_replace(text, regex("_NAME_"), name);
}