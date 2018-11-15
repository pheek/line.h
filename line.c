/**
 * Line-Reader (for any line length in the input file)
 * @author phi@gress.ly
 * @date   2018-11-15
 * @host   https://github.com/pheek/line.h
 */

// Don't include twice
#ifndef  LINE_H
// line.h contains the function header and constants.
#include "line.h"

/**
 * The following buffer contains enough space to hold a
 * line of the file.
 * If the BUFFER should be too small, it will be enlarged
 * automatically, like a Java-ArrayList.
 */
char* BUFFER; // holds linesize + 1 // null terminator


/**
 * Size of the buffer in bytes.
 */
int BUFFSIZE = 0; // if "0", this means, the buffer is not yet allocated


/**
 * You don't have to call this, because it is done automatically,
 * if the BUFFSIZE is still 0.
 * But you should call "freeBuffer()" at the end of your program,
 * to give the allocated memory back to the heap.
 */
void initBuffer() {
	BUFFSIZE = INITIAL_LINE_SIZE+1     ; // space for 0-terminator 
	BUFFER   = (char*) malloc((sizeof(char)) * BUFFSIZE); 
}


/**
 * Calculates a new size.
 * This is called, when the actual buffer is too small.
 * This does NOT allocate a new Buffer.
 */
size_t calcNewSize() {
	size_t newSize = BUFFSIZE * (100 + ENLARGE_PERCENTAGE) / 100;
	if(newSize <= BUFFSIZE) {
		newSize = BUFFSIZE + 1;
	}
	//printf("DEBUG: new size calculated: %ld\n", (long) newSize);
	return newSize;
}


/**
 * Copy the old buffer to the new.
 * This old Kernighan/Ritche Trick stayed in my
 * brain since about 35 years. I have not 
 * forgotten, what these clever guys did!
 * I didn't even open my book, which I still have!
 */
void copyBuffer(char* from, char* to) {
	from[BUFFSIZE-1]=0; // ensure buffer end; so the while will terminate.
	while(*to++ = *from++) {}
}


/**
 * As an ArrayList in Java, this enlages the buffer
 * and copies the content to the new buffer.
 */
void enlargeBuffer() {
	size_t newBuffSize = calcNewSize()      ;
	char * newBuffer   = malloc((sizeof(char)) * newBuffSize);

	copyBuffer(BUFFER, newBuffer);
	BUFFSIZE = newBuffSize;
	free(BUFFER);
	BUFFER = newBuffer;
}


/**
 * Check, if the buffer has a requested length.
 * If not, enlarge the buffer.
 * @requestedLineLength the length of a line (not the lenght of the 
 *                      buffer, which must be one character larger).
 */
void ensureCapacity(size_t requestedLineLength) {
	size_t requestedBufferSize = requestedLineLength + 1;
	if(BUFFSIZE < requestedBufferSize) {
		enlargeBuffer();
	}
}


// see line.h
char* get_line(FILE *filePointer) {
	if(0 == BUFFSIZE) { // not initialized yet
		initBuffer();
	}
	int pos = 0;
	int getcResult = getc(filePointer);
	while((EOF != getcResult) && ('\n' != getcResult)) {
		ensureCapacity(pos+1);
		BUFFER[pos++] = (char) getcResult;
		getcResult = getc(filePointer);
	}
	if(EOF == getcResult && 0 == pos) {
		return NULL;
	}
	BUFFER[pos] = 0;
	return BUFFER;
}


// see line.h
void freeBuffer() {
	free(BUFFER);
}


#endif
