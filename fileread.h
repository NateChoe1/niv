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
	int length;
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
			if (chariter->prev != NULL) {
				chariter->prev->next = NULL;
				free(chariter);
			}
			else {
				lineiter->beginning=NULL;
			}
			// There is a null char at the end of every line, so I have to remove that.
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
			lineiter->length++;
		}
		
		c = fgetc(file);
	}

	lineiter = lineiter->prev;
	free(lineiter->next);//I don't know why, but there's always a newline at the end of every file.
	lineiter->next = NULL;

	return head;
}
