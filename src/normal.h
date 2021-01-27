//#include "structs.h"
#include "controls.h"
#include "modes.h"

int min(int a, int b);
int max(int a, int b);

struct line *handleKeypress(int keyPressed, int *cursorX, int *cursorY, struct line *currentLine, int lineLength, char path[], struct line *head, int *mode, int *condition) {
	*condition = OKAY;
	*mode = NORMAL_MODE;
	switch (keyPressed) {
		case LEFT:
			*cursorX = min(*cursorX, lineLength - 1);
			if (*cursorX > 0)
				*cursorX = *cursorX - 1;
			break;
		case LINE_BEGIN:
			*cursorX = 0;
			break;
		case RIGHT:
			if (*cursorX < lineLength - 1)
				*cursorX = *cursorX + 1;
			break;
		case LINE_END:
			*cursorX = lineLength - 1;
			break;
		case UP:
			if (currentLine->prev != NULL) {
				*cursorY = *cursorY - 1;
				currentLine = currentLine->prev;
			}
			break;
		case BEGIN:
			while (currentLine->prev != NULL)
				currentLine = currentLine->prev;
			*cursorX = 0;
			*cursorY = 0;
			break;
		case DOWN:
			if (currentLine->next != NULL) {
				*cursorY = *cursorY + 1;
				currentLine = currentLine->next;
			}
			break;
		case END:
			while (currentLine->next != NULL) {
				currentLine = currentLine->next;
				*cursorY = *cursorY + 1;
			}
			*cursorX = currentLine->lineLength - 1;
			break;
		case QUIT:
			*condition = EXIT;
			break;
		case SAVE:
			writeFile(path, head);
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
		case ENTER_INSERT:
			*mode = INSERT_MODE;
			break;
		case APPEND:
			*mode = INSERT_MODE;
			*cursorX = *cursorX + 1;
			break;
		case ENTER_COMMAND:
			*mode = COMMAND_MODE;
			break;
		default:
			*condition=INVALID_COMMAND_INPUTTED;
	}
	return currentLine;
}

int min(int a, int b) {
	if (a > b) return b;
	return a;
}

int max(int a, int b) {
	if (a > b) return a;
	return b;
}
