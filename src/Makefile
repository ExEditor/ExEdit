all: exed

exed: main.c buffers.o
	${CC} $^ -o $@

buffers.o: buffers.c buffers.h
	${CC} -c $< -o $@
