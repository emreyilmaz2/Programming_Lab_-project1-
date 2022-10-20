NAME = prolab.a
CC = gcc
SRC = $(wildcard ./*.c)
CFLAGS = -Wall -Werror -Wextra
OBJ = (SRC:.c=.o)

all: SRC OBJ

SRC:
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) -I prolab.h
clean:
	rm -rf $(OBJ) $(NAME)
re : clean all
.PHONY: all clean
