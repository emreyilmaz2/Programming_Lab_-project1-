#include "prolab.h"

void	find_ticket(const char *dir, char *word, char *path)
{
	chdir(dir);
	int fd0;
	char *wow;
	int line=1;
	fd0 = open(path, O_RDONLY);
	wow = get_next_line(fd0);
	while(wow)
	{
		if(strstr(wow, word))
		{
			if(ft_strnstr(wow, word, 0))
			{
				printf(" * %s '%s' adli dosyada --> %d. satirda bulunan bir etikettir\n", word,path,line);
			}
		}
		wow = get_next_line(fd0);
		line++;
	}
	close(fd0);
	chdir("..");
}


void	find_word(const char *dir, char *str, char *filename)
{
	chdir(dir);
	int fd0;
	char *wow;
	int line=1, control=0;
	fd0 = open(filename, O_RDONLY);
	wow = get_next_line(fd0);
	while(wow)
	{
		if(strstr(wow, str))
			printf("aranan kelime '%s' --> '%s' isimli dosyanin %d. satirinda bulundu\n", str,filename, line);
		wow = get_next_line(fd0);
		line++;
	}
	close(fd0);
	chdir("..");
}



int	find_index(ticket_s *tag, char *str)
{
	int i = 0;
	while(tag[i].str)
	{
		if(strcmp(tag[i].str, str) == 0)
			return(i);
		i++;
	}
	return(-1);
}

ticket_s *find_all_ticket(const char *dir1 , char *filename)
{
	chdir(dir1);
	char t;
	int fd, index=0, flag=0;
	ticket_s *ticket = malloc(sizeof(ticket_s));
	int read_byte = 1;
	fd = open(filename, O_RDONLY);
	while(read_byte > 0)
	{
		char *temp = malloc(sizeof(char *));
		read_byte = read(fd, &t, 1);
		if(t == '[')
		{
			read_byte = read(fd, &t, 1);
			if(t == '[')
			{
				int a = 0;
				while(1)
				{
					read_byte = read(fd, &t, 1);
					if(t == ']')
					{
						read_byte = read(fd, &t, 1);
						if(t != ']')
							break;
						else if(t == ']')
						{
							temp[a] = '\0';
							ticket[index].str = malloc(sizeof(char *));
							ticket[index].counter = 1;
							int lo = 0;
							flag = 0;
							while(ticket[lo].str)
							{
								if(strcmp(ticket[lo].str, temp) == 0)
								{
									int toto = find_index(ticket, temp);
									if(toto != -1)
										ticket[toto].counter++;
									flag = 1;
								}
								lo++;
							}
							if(flag == 0)
							{
								strcpy(ticket[index].str, temp);
								index++;
							}
							break;
						}
					}
					temp[a] = t;
					a++;
				}
			}
		}
	}
	chdir("..");
	return(ticket);
}
