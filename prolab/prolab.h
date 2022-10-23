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
void	find_ticket(const char *dir, char *word, char *path);
void	find_word(const char *dir, char *str, char *filename);
void print(FILE *fd, ticket_s *ticket);
void replace(char *str, const char *oldWord, const char *newWord);
void change_things(char *path, char *name_old, char *name_new, char *new_path);
void	find_txt(void);
int EndsWithtxt(char *string);

void searchf1(const char *dir1, char *word2, int flag);
int ft_strnstr(const char *haystack, const char *needle, int flag);

ticket_s *find_all_ticket(const char *dir1 , char *filename);
#endif
