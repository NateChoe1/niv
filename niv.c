/*
 * NIV, a text editor.
 * Copyright (C) 2021  Nathaniel Choe
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the license, or
 * {at your option} any later version.
 *
 * This program is distribyted in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <https://www.gnu.org/licenses/>.
 *
 * Email me: natechoe9@gmail.com
 * */


#include <curses.h>
#include <stdlib.h>
#include <string.h>
#include "fileread.h"

int max(int a, int b);
int min(int a, int b);

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
	for (int i = 0; i < LINES - 1; i++) {
		if (lineiter == NULL)
			mvaddch(i, 0, '~');
		else {
			for (int j = 0; j < COLS; j++) {
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

	move(0, 0);
	refresh();
	
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
		cursorx = max(cursorx, 0);
		cursory = max(cursory, 0);
		cursorx = min(cursorx, COLS);
		cursory = min(cursory, LINES);
		move(cursory, cursorx);
		refresh();
		lastpressed = getch();
	}

	endwin();
	exit(0);
}

int max(int a, int b) {
	if (a > b) return a;
	return b;
}

int min(int a, int b) {
	if (a > b) return b;
	return a;
}
