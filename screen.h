#ifndef SCREEN
#define SCREEN
#include <ncurses.h>
#include <string>
#include <iostream>
#include <unistd.h>
using namespace std;


class Screen {

    private:

  	int x_max;
	int y_max;
	WINDOW * text_win;
	WINDOW * choice_win;
    int type_text(WINDOW * window, string text);

    public:

    int refresh_window(WINDOW * window);
    int initialize(void);
    int create_text_window(void);
    int create_choice_window(void);
    int update_text(string text);
    int update_choices(int num_choices, string * choices);
    string request_data(string request);
    int end(void);

};

#endif // SCREEN