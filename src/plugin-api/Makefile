CFLAGS := -fPIC

all: exed-plugins.so

exed-plugins.so: plugins.o
	${CC} -shared $^ -o $@

plugins.o: plugins.c plugins.h
	${CC} -c $< -o $@ ${CFLAGS}

clean:
	${RM} *\.o
	${RM} *\.so

.PHONY: all clean
