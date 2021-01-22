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

#define INITIAL_LINE_LENGTH 5

#include "os.h"
#include <stdlib.h>
#include <stdio.h>

struct line {
	struct line *prev;
	struct line *next;
	int lineLength;
	int allocatedLength;
	char lineContent[];
};

struct line *initializeLine() {
	struct line *returnValue = malloc(sizeof(struct line) + (sizeof(char) * INITIAL_LINE_LENGTH));
	returnValue->lineLength = 1;
	returnValue->allocatedLength = INITIAL_LINE_LENGTH;
	return returnValue;
}

struct line *addToLine(struct line *addLine, char addChar) {
	struct line *returnLine = addLine;
	if (addLine->lineLength >= addLine->allocatedLength) {
		returnLine = malloc(sizeof(struct line) + (addLine->allocatedLength * 2));
		if (addLine->prev != NULL)
			addLine->prev->next = returnLine;
		if (addLine->next != NULL)
			addLine->next->prev = returnLine;
		returnLine->prev = addLine->prev;
		returnLine->lineLength = addLine->lineLength;
		returnLine->allocatedLength = addLine->allocatedLength * 2;
		for (int i = 0; i < addLine->lineLength; i++)
			returnLine->lineContent[i] = addLine->lineContent[i];
	}
	returnLine->lineContent[returnLine->lineLength - 1] = addChar;
	returnLine->lineLength++;
}

struct line *getHead(char path[]) {
	FILE *file;
	file = fopen(path, "r");

	struct line *lineiter = initializeLine();

	int c = fgetc(file);
	while (c != EOF) {
		if (c == '\n') {
			lineiter->next = initializeLine();
			lineiter->next->prev = lineiter;
			lineiter = lineiter->next;
		}
		else {
			lineiter = addToLine(lineiter, c);
		}
		
		c = fgetc(file);
	}

	while (lineiter->prev != NULL)
		lineiter = lineiter->prev;

	return lineiter;
}
