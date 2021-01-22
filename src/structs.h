#define OKAY 0
#define EXIT 1
#define INVALID_COMMAND_INPUTTED 2

struct line {
	struct line *prev;
	struct line *next;
	int lineLength;
	int allocatedLength;
	char lineContent[];
};

struct editorState {
	int cursorX;
	int cursorY;
	int mode;
	int condition;
	struct line *currentLine;
};
