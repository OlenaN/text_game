#include <ncurses.h>
#include <string>
#include <iostream>
#include <unistd.h>
using namespace std;

int type_text (WINDOW * window, string text) {
	
	int max_x, max_y;
	getmaxyx(window, max_y, max_x);

	int x, y = 1;

	for(int i = 0; i < text.length(); i++) {
		string s(1, text[i]);
		string space = " ";
		if (x > max_x - 20 && !s.compare(space)) {
			y++;
			x = 0;
		} else {
			x++; 		
			mvwprintw(window, y, x, s.c_str());
  			wrefresh(window);
			usleep(30000);
		}
	}
}


int main() {

  initscr();
  noecho();
  cbreak();
  curs_set(0);

  int x_max, y_max;
  getmaxyx(stdscr, y_max, x_max);

  WINDOW * text_win = newwin(2*y_max/3 - 3, x_max - 10, 2, 5);
  box(text_win, 0, 0);
  refresh();
  wrefresh(text_win);


  WINDOW * choice_win = newwin(y_max/3, x_max - 10, y_max - (y_max/3 + 1), 5);
  box(choice_win, 0, 0);
  refresh();
  wrefresh(choice_win);
  
  string text = "Although C and C++ have different name mangling, which can be a source of bugs and incompatibilities, in most cases it's fine to use C headers in C++. However, if you want to be absolutely sure that nothing goes wrong, #include the C header inside an extern C block";
  type_text(text_win, text);
  
  // input is arrow keys
  keypad(choice_win, true);

  int num_choices = 3;
  string choices[num_choices] = {"Walk left", "Walk right", "Sit down"};
  int choice;
  int highlight = 0;

  while(1) {
	  for(int i = 0; i < num_choices; i++) {
		  if (i == highlight) {
		  	wattron(choice_win, A_STANDOUT);
		  }
		  mvwprintw(choice_win, i+1, 1, choices[i].c_str());
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

  // Make sure ncurses waits and exits
  getch();
  endwin();


  return 0;

}
