CC=gcc
CFLAGS=-g -W -Wall -Werror -Wextra -DDEBUG
LDFLAGS=
SOURCES=
BINARY=

${BINARY}: ${SOURCES}
	${CC} ${SOURCES} ${CFLAGS} ${LDFLAGS} -o ${BINARY}

clean:
	rm -f ${BINARY}
