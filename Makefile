CC = gcc
SRC = main.c directoryfuncs.c execute_funcs.c file_redirections.c helpers.c list_functions.c strings.c tokenize.c
OBJ = ${SRC:.c=.o}
NAME = hsh
CFLAGS = -Wall -Werror -Wextra -pedantic -g -std=c11

all: ${NAME}

${NAME}: ${OBJ}
	${CC} $(CFLAGS) ${OBJ} -o ${NAME}

%.o: %.c ${HEAD}
	${CC} ${CFLAGS} -c $< -o $@

clean:
	${RM} -f ${OBJ} ${NAME}

.PHONY: all clean