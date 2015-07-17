CFLAGS := -fPIC -std=c99

all: libexed-plugins.so

libexed-plugins.so: plugins.o
	${CC} -shared $^ -o $@

plugins.o: plugins.c plugins.h
	${CC} -c $< -o $@ ${CFLAGS}

clean:
	${RM} *\.o
	${RM} *\.so

.PHONY: all clean
