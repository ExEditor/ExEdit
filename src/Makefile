CFLAGS="-g"
PLUGIN_API_DIR="./plugin-api/"

all: exed plugin-api

plugin-api:
	make -C ${PLUGIN_API_DIR}

exed: main.c buffers.o
	${CC} $^ -o $@ ${CFLAGS}

buffers.o: buffers.c buffers.h
	${CC} -c $< -o $@ ${CFLAGS}

clean:
	${RM} *\.o
	${RM} exed

.PHONY: all clean plugin-api
