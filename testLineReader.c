/**
 * Santis
 * @author philipp.gressly@santismail.ch
 * @date   2018-11-13
 */

#include <stdio.h>
#include <stdlib.h>
#include "line.h"

void main(void) {
	// Test: Zähle die Zeilen, starte mit 1.
	int   lineNumber = 0;
	char* line = get_line(stdin);
	while(line != NULL) {
		lineNumber = lineNumber + 1;
		printf("\n%3d. Zeile: [[%s]]", lineNumber, line);
		line = get_line(stdin);
	}
	printf("\n\nZeilen total: %d\n", (lineNumber));
}
