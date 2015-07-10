CFLAGS="-g"

all: exed

exed: main.c buffers.o
	${CC} $^ -o $@ ${CFLAGS}

buffers.o: buffers.c buffers.h
	${CC} -c $< -o $@ ${CFLAGS}

clean:
	${RM} *\.o
	${RM} exed

.PHONY: all clean
