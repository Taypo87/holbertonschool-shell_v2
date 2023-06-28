CC = gcc
SRC = $(wildcard *.c)
OBJ = ${SRC:.c=.o}
NAME = hsh

CFLAGS = -Wall -Werror -Wextra -pedantic -g -std=c99

all: ${NAME} clean

${NAME}: ${OBJ}
	${CC} $(CFLAGS) ${OBJ} -o ${NAME}

%.o: %.c ${HEAD}
	${CC} ${CFLAGS} -c $< -o $@

clean:
	${RM} -f ${OBJ}

.PHONY: all clean
