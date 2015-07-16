PLUGIN_API_DIR = ../../plugin-api
CFLAGS := -fPIC -I ${PLUGIN_API_DIR}

all: test1.so

%.so: %.o
	${CC} -shared $^ -o $@

%.o: %.c %.h
	${CC} -c $< -o $@ ${CFLAGS}

clean:
	${RM} *\.o
	${RM} *\.so

.PHONY: all clean
