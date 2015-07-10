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

    return 0;
}
