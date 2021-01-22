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
#include "modes.h"
#include "normal.h"

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

	//At this point the file should be loaded into head.

	int cursorX = 0;
	int cursorY = 0;
	char quit = 0;
	char *bottomMessage = malloc(1);
	bottomMessage = "\0";

	int mode = NORMAL_MODE;
	while (!quit) {
		drawText(head, min(cursorX, currentLine->lineLength - 1), cursorY, 0, bottomMessage);
		int keyPressed = getch();
		switch (mode) {
			case NORMAL_MODE:;
				struct editorState newState;
				newState = handleKeypress(keyPressed, cursorX, cursorY, currentLine, currentLine->lineLength, path, head);
				cursorX = newState.cursorX;
				cursorY = newState.cursorY;
				mode = newState.mode;
				switch (newState.condition) {
					case EXIT:
						quit = 1;
						break;
					case INVALID_COMMAND_INPUTTED:
						bottomMessage = malloc(16);
						bottomMessage = "Invalid command inputted.";
						break;
				}
				currentLine = newState.currentLine;
				break;
			case INSERT_MODE:
				switch(keyPressed) {
					case ENTER_NORMAL:
						mode = NORMAL_MODE;
						break;
					default:
						currentLine = addToLine(currentLine, '\0');
						for (int i = currentLine->lineLength - 1; i > cursorX; i--)
							currentLine->lineContent[i] = currentLine->lineContent[i-1];
						currentLine->lineContent[cursorX] = keyPressed;
						cursorX++;
						break;
				}
		}
	}
	endwin();
	exit(0);
}
