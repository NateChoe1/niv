#include "os.h"
#include <stdlib.h>

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

struct line getHead(char path[]) {
	FILE *file;
	file = fopen(path, "r");

	struct line head;
	struct line *lineiter = &head;
	lineiter->beginning = malloc(sizeof(struct linechar));
	struct linechar *chariter= lineiter->beginning;

	int c = fgetc(file);
	while (c != EOF) {
		if (c == '\n') {
			lineiter->next = malloc(sizeof(struct line));
			lineiter->next->prev = lineiter;
			lineiter = lineiter->next;
			lineiter->beginning = malloc(sizeof(struct linechar));
			chariter = lineiter->beginning;
		}
		else {
			chariter->value = c;
			chariter->next = malloc(sizeof(struct linechar));
			chariter->next->prev = chariter;
			chariter = chariter->next;
		}
		
		c = fgetc(file);
	}

	lineiter= lineiter->prev;
	free(lineiter->next);//I don't know why, but there's always a newline at the end of every file.
	lineiter->next = NULL;

	return head;
}
