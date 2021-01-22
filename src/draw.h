#include <curses.h>

void drawText(struct line *head, int cursorX, int cursorY, int drawStart, char bottomText[]) {
	clear();
	int lineDrawn = drawStart;
	int charsDrawn = 0;
	int displayX;
	int displayY;
	char cursorSet = 0;
	for (int i = 0; i < LINES - 1; i++) {
		if (head == NULL) {
			mvaddch(i, 0, '~');
			lineDrawn++;
		}
		else {
			for (int j = 0; j < COLS; j++) {
				if (charsDrawn == cursorX && lineDrawn == cursorY && !cursorSet) {
					cursorSet = 1;
					displayX = j;
					displayY = i;
				}
				if (charsDrawn >= head->lineLength - 1) {
					head = head->next;
					lineDrawn++;
					charsDrawn = 0;
					break;
				}
				mvaddch(i, j, head->lineContent[charsDrawn]);
				charsDrawn++;
			}
		}
	}
	for (int i = 0; i < COLS; i++) {
		if (bottomText[i])
			mvaddch(LINES-1, i, bottomText[i]);
		else
			break;
	}
	move(displayY, displayX);
	refresh();
}
