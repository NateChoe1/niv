//#include "structs.h"
#include "controls.h"
#include "modes.h"

int min(int a, int b);
int max(int a, int b);

struct editorState handleKeypress(int keyPressed, int cursorX, int cursorY, struct line *currentLine, int lineLength, char path[], struct line *head) {
	struct editorState newState;
	newState.condition = OKAY;
	newState.mode = NORMAL_MODE;
	newState.currentLine = currentLine;
	newState.cursorX = cursorX;
	newState.cursorY = cursorY;
	switch (keyPressed) {
		case LEFT:
			newState.cursorX = min(cursorX, lineLength - 1);
			if (cursorX > 0)
				newState.cursorX--;
			break;
		case LINE_BEGIN:
			newState.cursorX = 0;
			break;
		case RIGHT:
			if (cursorX < lineLength - 1)
			newState.cursorX = cursorX + 1;
			break;
		case LINE_END:
			newState.cursorX = lineLength - 1;
			break;
		case UP:
			if (currentLine->prev != NULL) {
				newState.cursorY = cursorY - 1;
				newState.currentLine = currentLine->prev;
			}
			break;
		case BEGIN:
			while (newState.currentLine->prev != NULL)
				newState.currentLine = newState.currentLine->prev;
			newState.cursorX = 0;
			newState.cursorY = 0;
			break;
		case DOWN:
			if (currentLine->next != NULL) {
				newState.cursorY = cursorY + 1;
				newState.currentLine = newState.currentLine->next;
			}
			printf("No segfault yet\n");
			break;
		case END:
			while (newState.currentLine->next != NULL) {
				newState.currentLine = newState.currentLine->next;
				newState.cursorY = newState.cursorY + 1;
			}
			newState.cursorX = newState.currentLine->lineLength - 1;
			break;
		case QUIT:
			newState.condition = EXIT;
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
			newState.mode = INSERT_MODE;
			break;
		default:
			newState.condition=INVALID_COMMAND_INPUTTED;
	}
	return newState;
}

int min(int a, int b) {
	if (a > b) return b;
	return a;
}

int max(int a, int b) {
	if (a > b) return a;
	return b;
}
