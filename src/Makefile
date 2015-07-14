CFLAGS="-g"

all: exed

exed: main.c buffers.o plugins.o
	${CC} $^ -o $@ ${CFLAGS}

buffers.o: buffers.c buffers.h
	${CC} -c $< -o $@ ${CFLAGS}

plugins.o: plugins.c plugins.h
	${CC} -c $< -o $@ ${CFLAGS}

clean:
	${RM} *\.o
	${RM} exed

.PHONY: all clean
