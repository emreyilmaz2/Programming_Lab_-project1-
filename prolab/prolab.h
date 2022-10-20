#ifndef PROLAB_H
#define PROLAB_H

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <dirent.h>
#include <glob.h>

#define BUFFER_SIZE 1000

typedef struct ticket
{
	char *str;
	int counter;
} ticket_s;

// functions
char *get_next_line(int fd);

void *ft_calloc(size_t count, size_t size);
void find_ticket(char *str);
void find_word(char *str);
void print(FILE *fd, int line, int flag, char *str);
void replace(char *str, const char *oldWord, const char *newWord);
void change_things(char *path, char *name_old, char *name_new, char *new_path);
void	find_txt(void);

int ft_strnstr(const char *haystack, const char *needle, int flag);

ticket_s *find_all_ticket(char *path);

#endif
