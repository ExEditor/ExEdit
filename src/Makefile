PLUGIN_API_DIR="./plugin-api/"
CFLAGS := -fPIC -I ${PLUGIN_API_DIR}
LDFLAGS := -L ${PLUGIN_API_DIR} -l"exed-plugins" -ldl

all: exed plugin-api

plugin-api:
	make -C ${PLUGIN_API_DIR}

exed: main.o buffers.o
	${CC} $^ -o $@ ${LDFLAGS}

%.o: %.c %.h
	${CC} -c $< -o $@ ${CFLAGS}

clean:
	${RM} *\.o
	${RM} exed

.PHONY: all clean plugin-api
