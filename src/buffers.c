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

#include "buffers.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>


Buffer load_buffer(char *filename)
{
    Buffer buff;
    buff.filename = filename;
    buff.content_size = 0;
    buff.max_size = 1;
    
    FILE *fp = fopen(filename, "rb");

    if (NULL == fp) {
        fprintf(stderr, "Error: cannot open file \"%s\"\n", filename);
        exit(EXIT_FAILURE);
    }
    
    int fd = fileno(fp);

    struct stat status;
    fstat(fd, &status);

    buff.content_size = status.st_size;
    while (buff.max_size < buff.content_size + 1) {
        buff.max_size *= 2;
    }

    buff.contents = calloc(buff.max_size, sizeof(char));
    size_t num_read = fread(buff.contents, sizeof(char), buff.content_size, fp);

    fclose(fp);
    return buff;
}


void display_buffer(Buffer *buff)
{
    printf("%s\n", buff->contents);
}


/* Increase the size of the contents of the buffer. Make sure that the
   contents fit in the new size if shrunk.
 */
void content_resize(Buffer *buffer, ssize_t amount)
{
    if (0 == amount) {
        return;
    }

    /* Determine new content size. */
    size_t new_content_size = 0;
    if (amount < 0) {
        if (buffer->content_size > amount) {
            new_content_size = buffer->content_size + amount;
        }
    }
    else {
        new_content_size = buffer->content_size + amount;
    }

    /* Grow or shrink the buffer if necessary */
    if (new_content_size > buffer->max_size) {
        while (new_content_size > buffer->max_size) {
            buffer->max_size *= 2;
        }
        
        buffer->contents = realloc(buffer->contents, buffer->max_size);

        if (NULL == buffer->contents) {
            fprintf(stderr, "Error: can not resize buffer \"%s\"\n", buffer->filename);
            exit(EXIT_FAILURE);
        }

        memset(buffer->contents + buffer->content_size, 0, buffer->max_size - buffer->content_size);
    }
    else if (new_content_size < buffer->max_size / 4) {
        while (new_content_size < buffer->max_size / 4) {
            buffer->max_size /= 2;
        }

        buffer->contents = realloc(buffer->contents, buffer->max_size);

        if (NULL == buffer->contents) {
            fprintf(stderr, "Error: can not resize buffer \"%s\"\n", buffer->filename);
            exit(EXIT_FAILURE);
        }
    }

    buffer->content_size = new_content_size;
}


void buffer_shift(Buffer *buffer, size_t pos, ssize_t offset)
{
    if (pos > buffer->content_size) {
        /* Doesn't make sense to shift outside of content. */
        return;
    }

    if (offset < 0) {
        /* Have to deal with negative indices, ugh... */
        
        /* After the shift we might want to resize */
        content_resize(buffer, offset);
    }
    else if (offset > 0) {
        /* Copy portion of the buffer that we want to shift */
        size_t chunk_size = buffer->content_size - pos;
        char *chunk = calloc(chunk_size, sizeof(char));

        strncpy(chunk, buffer->contents + pos, chunk_size);
        
        /* Need to resize, because we're shifting right */
        content_resize(buffer, offset);

        /* Fill in between bit with SOMETHING */
        memset(buffer->contents + pos, '?', offset);

        /* Copy shifted portion in */
        strncpy(buffer->contents + pos + offset, chunk, chunk_size);
    }
}


void insert_char(Buffer *buffer, size_t pos, char c)
{
    if (pos > buffer->content_size) {
        return;
    }

    buffer_shift(buffer, pos, 1);
    buffer->contents[pos] = c;
}


void remove_char(Buffer *buffer, size_t pos)
{
    buffer_shift(buffer, pos + 1, -1);
}

