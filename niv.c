#include <curses.h>
#include <stdlib.h>
#include <string.h>
#include "os.h"

struct linechar {
	char value;
	struct linechar *prev;
	struct linechar *next;
};

struct line {
	struct linechar *beginning;
	struct line *prev;
	struct line *next;
};

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
	FILE *file;
	file = fopen(path, "r");

	struct line first;
	struct line *iterator = &first;
	iterator->beginning = malloc(sizeof(struct linechar));
	struct linechar *chariterator = iterator->beginning;

	int c = fgetc(file);
	while (c != EOF) {
		if (c == '\n') {
			iterator->next = malloc(sizeof(struct line));
			iterator->next->prev = iterator;
			iterator = iterator->next;
			iterator->beginning = malloc(sizeof(struct linechar));
			chariterator = iterator->beginning;
		}
		else {
			chariterator->value = c;
			chariterator->next = malloc(sizeof(struct linechar));
			chariterator->next->prev = chariterator;
			chariterator = chariterator->next;
		}
		
		c = fgetc(file);
	}

	iterator = iterator->prev;
	free(iterator->next);//I don't know why, but there's always a newline at the end of every file.
	iterator->next = NULL;

	//At this point, first will have every line which contains every char.
	
	//Everything beyond this point is just me messing around with curses.

	/*for (int i = 0; i < LINES; i++) {       //y values
		int failed = 0;
		for (int j = 0; j < COLS; j++) {//x values
			int intchar = fgetc(file);
			if (intchar == EOF) {
				failed = 1;
				break;
			}
			char c = (char) intchar;
			mvaddch(i, j, c);
		}
		if (failed) break;
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
	}*/

	endwin();
	exit(0);
}
