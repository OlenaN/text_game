#include <ncurses.h>
#include <string>
#include <iostream>
#include <unistd.h>
#include "screen.h"

using namespace std;


int Screen::type_text(WINDOW * window, string text) {
	int max_x, max_y;
	getmaxyx(window, max_y, max_x);

	int x = 1;
	int y = 1;

	for(int i = 0; i < text.length(); i++) {
		string s(1, text[i]);
		string space = " ";
		if (x > max_x - 20 && !s.compare(space)) {
			y++;
			x = 1;
		} else {
			x++; 		
			mvwprintw(window, y, x, s.c_str());
			wrefresh(window);
			usleep(30000);
		}
	}

}

int Screen::refresh_window(WINDOW * window) {
	wclear(window);
	box(window, 0, 0);
	refresh();
	wrefresh(window);
	wmove(window, 0 , 0);
	move(0,0);
	return 0;
}

int Screen::initialize(void) {
	initscr();
	noecho();
	cbreak();
	curs_set(0);
	getmaxyx(stdscr, y_max, x_max);

	return 0;
}

int Screen::create_text_window(void) {
	text_win = newwin(2*y_max/3 - 3, x_max - 10, 2, 5);
	box(text_win, 0, 0);
	refresh();
	wrefresh(text_win);

	return 0;
}

int Screen::create_choice_window(void) {
	choice_win = newwin(y_max/3, x_max - 10, y_max - (y_max/3 + 1), 5);
	box(choice_win, 0, 0);
	refresh();
	wrefresh(choice_win);

	return 0;
}

int Screen::update_text(string text) {
	refresh_window(text_win);
	refresh_window(choice_win);
	type_text(text_win, text);
	return 0;
}


int Screen::update_choices(int num_choices, string * choices) {
	refresh_window(choice_win);
	int choice;
	int highlight = 0;

	// input is arrow keys
	keypad(choice_win, true);

	while(1) {
		for(int i = 0; i < num_choices; i++) {
			if (i == highlight) {
				wattron(choice_win, A_STANDOUT);
			}
			string curr_choice = "> " + *(choices + i);
			mvwprintw(choice_win, i+1, 1, curr_choice.c_str());
			wattroff(choice_win, A_STANDOUT);
		}
		choice = wgetch(choice_win);

		switch(choice) {
			case KEY_UP:
				if (highlight > 0)
					highlight--;
				break;
			case KEY_DOWN:
				if (highlight < num_choices - 1)
					highlight++;
				break;
			default:
				break;
		}

		if (choice == 10) {
			break;
		}
	}

	return highlight;
}

string Screen::request_data(string request) {
	refresh_window(choice_win);
	type_text(choice_win, request);

	char str[100];
	echo();
	mvwgetstr(choice_win, 2, 2, str); 
	noecho();
	return str;
}

int Screen::end(void) {
	getch();
	endwin();

	return 0;
}





/**

int main() {

	Screen screen;
	screen.initialize();
	screen.create_text_window();
	screen.create_choice_window();
	
	string text = "What is your name?";
	screen.update_text(text);

	string request = "Enter name: ";
	string name = screen.request_data(request);

	text = string("Hello ") + name + string("! What would you like to do?");
	screen.update_text(text);

	string choices[3] = {"sit", "dance", "walk"};
	int choice = screen.update_choices(3, choices);
	
	text = "What is your name?";
	screen.update_text(text);

	request = "Enter name: ";
	name = screen.request_data(request);

	screen.end();

	return 0;
}
**/