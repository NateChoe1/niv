#include <curses.h>

void drawText(struct line head, int cursorX, int cursorY, int drawStart, char bottomText[]) {
	clear();
	struct line *lineIter = &head;
	struct linechar *charIter = lineIter->beginning;
	for (int i = 0; i < drawStart; i++)
		lineIter = lineIter->next;
	int lineDrawn = drawStart;
	int displayX;
	int displayY;
	char cursorSet = 0;
	for (int i = 0; i < LINES - 1; i++) {
		if (lineIter == NULL) {
			mvaddch(i, 0, '~');
			lineDrawn++;
		}
		else {
			for (int j = 0; j < COLS; j++) {
				if (j == cursorX && lineDrawn == cursorY && !cursorSet) {
					cursorSet = 1;
					displayX = j;
					displayY = i;
				}
				if (charIter == NULL) {
					lineIter = lineIter->next;
					lineDrawn++;
					if (lineIter != NULL)
						charIter = lineIter->beginning;
					break;
				}
				mvaddch(i, j, charIter->value);
				charIter = charIter->next;
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
