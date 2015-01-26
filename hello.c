#include <curses.h>

int main(void)
{
	initscr();
	box(stdscr, ACS_VLINE, ACS_HLINE); /*draw a box*/
	move(LINES/2, COLS/2); /*move the cursor to the center*/
	waddstr(stdscr, "Hello, world!");
	refresh();
	getch();
	endwin();

	return 0;
}
