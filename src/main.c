#include <stdio.h>

#include "buffers.h"

int main(int argc, char *argv[])
{
    if (argc < 2) {
        printf("usage: %s <filename>\n", argv[0]);
        return -1;
    }
    
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
