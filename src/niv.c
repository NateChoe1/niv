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

#include <stdlib.h>
#include <string.h>
#include "fileread.h"
#include "draw.h"
#include "controls.h"

int min(int a, int b);
int max(int a, int b);

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
	struct line *head = getHead(path);
	struct line *currentLine = head;

	/*while (iterator->next != NULL) {
		for (int i = 0; i < iterator->lineLength; i++)
			printf("%c", iterator->lineContent[i]);

		iterator = iterator->next;
		printf("\n");
	}*/

	//At this point the file should be loaded into head.

	int cursorX = 0;
	int cursorY = 0;
	char quit = 0;
	char *bottomMessage;
	bottomMessage = "\0";

	while (!quit) {
		int lineLength = currentLine->lineLength;
		drawText(head, min(cursorX, lineLength - 1), cursorY, 0, bottomMessage);
		switch (getch()) {
			case LEFT:
				cursorX = min(cursorX, lineLength - 1);
				if (cursorX > 0)
					cursorX--;
				break;
			case LINE_BEGIN:
				cursorX = 0;
				break;
			case RIGHT:
				if (cursorX < lineLength - 1)
				cursorX++;
				break;
			case LINE_END:
				cursorX = lineLength - 1;
				break;
			case UP:
				if (currentLine->prev != NULL) {
					cursorY--;
					currentLine = currentLine->prev;
				}
				break;
			case BEGIN:
				cursorX = 0;
				cursorY = 0;
				break;
			case DOWN:
				if (currentLine->next != NULL) {
					cursorY++;
					currentLine = currentLine->next;
				}
				break;
			case END:
				while (currentLine->next != NULL) {
					currentLine = currentLine->next;
					cursorY++;
				}
				lineLength = currentLine->lineLength;
				cursorX = lineLength-1;
				break;
			case QUIT:
				quit = 1;
				break;
			case SAVE:
				break;
			case FORWARD_BEGIN:
				break;
			case FORWARD_END:
				break;
			case BACKWARD_BEGIN:
				break;
			case BACKWARD_END:
				break;
			//TODO: Implement these
			default:
				bottomMessage = malloc(16);
				bottomMessage = "Invalid command.";
		}
		//These are defined in controls.h
	}
	endwin();
	exit(0);
}

int min(int a, int b) {
	if (a > b) return b;
	return a;
}

int max(int a, int b) {
	if (a > b) return a;
	return b;
}
