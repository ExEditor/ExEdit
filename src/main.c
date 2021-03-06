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

#include <plugins.h>
#include <stdio.h>


int main(int argc, char *argv[])
{
    if (argc < 2) {
        printf("usage: %s <filename>\n", argv[0]);
        return -1;
    }

    ExEd_Plugin plugin = load_plugin("./plugins/tests/test1.so");

    plugin_display(&plugin);
    plugin.commands[0].callback(NULL);
    
    Buffer buff = load_buffer(argv[1]);

    display_buffer(&buff);
    insert_char(&buff, 0, 'f');
    display_buffer(&buff);

    char current_char;
    for (current_char = '0'; current_char <= '9'; ++current_char) {
        insert_char(&buff, 2, current_char);
        display_buffer(&buff);
    }

    save_buffer(&buff);
    return 0;
}
