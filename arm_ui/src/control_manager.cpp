#include <cstdio>
#include <curses.h>

int main(int argc, char ** argv)
{
  (void) argc;
  (void) argv;
  printf("hello world arm_ui package\n");

  initscr();
  noecho();
  curs_set(0);

  int x_max, y_max;

  getmaxyx(stdscr, y_max, x_max);

  WINDOW *win = newwin(y_max / 2, x_max / 2, y_max / 4, x_max / 4);
  box(win, 0, 0);

  wgetch(win);

  endwin();
  return 0;
}
