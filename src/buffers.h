/*
  The MIT License (MIT)

  Copyright (c) 2015 Calvin Beck

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.

 */

#ifndef BUFFERS_H
#define BUFFERS_H

#include <stdlib.h>


typedef struct Buffer {
    char *filename;
    char *contents; /* NULL if not loaded */
    size_t content_size; /* Current size of actual contents */
    size_t max_size; /* Maximum size of contents */
} Buffer;


/*
  Load a file into a new buffer.

  Preconditions: None.
  Postconditions: May exit if file can not be opened.

  Returns a buffer with the file's contents if successful.
 */

Buffer load_buffer(char *filename);


/*
  Attempt to save the contents of the buffer to its corresponding file.

  Preconditions: Valid buffer from a file.
  Postconditions: Overwrites file's data. May exit if the file can not be opened.
 */

void save_buffer(Buffer *buff);


/*
  Print the buffer's contents to stdout.

  Preconditions: Buffer should contain valid data.
  Postconditions: Information displayed on stdout.
 */

void display_buffer(Buffer *buff);


/*
  Insert a single character into a buffer.

  Preconditions: Valid buffer data. Position within buffer.
  Postconditions: If the position is inside of the buffer the contents
  of the buffer will be shifted from that position onwords, and the
  new character will be inserted here. The buffer may be resized. If
  the position is outside of the buffer, then nothing will happen.
 */
void insert_char(Buffer *buffer, size_t pos, char c);


/*
  Removes a single character from the buffer.

  Preconditions: Valid buffer data. Position within buffer.
  Postconditions: If the position is in the buffer we will remove the
  character at this position, and shift the rest of the buffer
  down. The buffer may be resized. If the position is outside of the
  buffer, then nothing will happen.
 */
void remove_char(Buffer *buffer, size_t pos);

#endif
