#include <curses.h>
#include <stdlib.h>
#include <string.h>
#include "fileread.h"


int main(int argc, char *argv[]) {
	int filesize;
	if (argc != 2) {
		printf("You need to input a file.\n");
		exit(1);
	}
	initscr();
	cbreak();
	noecho();
	clear();

	char path[sizeof(argv[1]) / sizeof(char)];
	strcpy(path, argv[1]);
	struct line head = getHead(path);

	//At this point, first will have every line which contains every char.
	
	struct line *lineiter = &head;
	struct linechar *chariter = lineiter->beginning;
	for (int i = 0; i < LINES; i++) {       //y values
		if (lineiter == NULL)
			mvaddch(i, 0, '~');
		else {
			for (int j = 0; j < COLS; j++) {//x values
				mvaddch(i, j, chariter->value);
				chariter = chariter->next;
				if (chariter == NULL) {
					lineiter = lineiter->next;
					if (lineiter != NULL)
						chariter = lineiter->beginning;
					break;
				}
			}
		}
	}
	
	int cursorx = 0;
	int cursory = 0;
	char lastpressed = getch();
	int i = 0;
	while (lastpressed != ' ') {
		switch (lastpressed) {
			case 'j':
				cursorx--;
				break;
			case 'k':
				cursory++;
				break;
			case 'l':
				cursory--;
				break;
			case ';':
				cursorx++;
				break;
		}
		move(cursory, cursorx);
		refresh();
		lastpressed = getch();
	}

	endwin();
	exit(0);
}
