#include "prolab.h"

void	find_ticket(char *str)
{
	FILE *fd, *fd2;
	int fd0;
	int fd_txt;
	char *wow;
	char *ram;
	int line=1, control=0;
	fd_txt = open("files.txt", O_RDONLY);

	strcpy(ram, "\"");
	strcat(ram, get_next_line(fd_txt));
	ram[strlen(ram)-1] = '"';
	printf("%s\n", ram);
	fd = fopen(ram, "r");
	if(fd == NULL)
		printf("acamiyoz aq");
	//fd2 = fopen("output.txt", "a+");
	////fd = fopen("./universite/bolumler/mekatronik.txt", "r");
	while(ram)
	{
		fd0 = open(ram, O_RDONLY);
		if(fd0 < 0)
		{
			printf("\n\nerror -- > %d\n\n", fd0);
			exit(1);
		}
		wow = get_next_line(fd0);
		while(wow)
		{
			if(strstr(wow, str))
			{
				if(ft_strnstr(wow, str, 0))
				{
					printf("%s --> %d. satirda bulunan bir etikettir\n", str, line);
					print(fd2,line,1, str);
				}
				else
				{
					printf("%s --> %d. satirdaki YETIM etikettir\n", str, line);
					print(fd2, line , 0, str);
				}
			}
			wow = get_next_line(fd0);
			line++;
		}
		close(fd0);
		ram = get_next_line(fd_txt);
	}
	fclose(fd2);
}

void	find_word(char *str)
{
	FILE *fd, *fd2;
	int fd0, flag =1;
	char *wow;
	int line=1, control=0;
	fd2 = fopen("output.txt", "a+");
	//fd = fopen("./universite/bolumler/mekatronik.txt", "r");
	fd0 = open("./universite/bolumler/mekatronik.txt", O_RDONLY);
	wow = get_next_line(fd0);
	while(wow)
	{
		if(strstr(wow, str))
		{
			flag = 0;
			printf("aranan kelime '%s' %d. satirda bulundu\n", str, line);
		}
		wow = get_next_line(fd0);
		line++;
	}
	if(flag==1)
		printf("aradiginiz kelimeyi bulamadik ://\n");
	close(fd0);
	fclose(fd2);
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

ticket_s	*find_all_ticket(char *path)
{
	char t;
	int fd, tc=0, flag=0;
	ticket_s *ticket = malloc(sizeof(ticket_s));
	int read_byte = 1;
	fd = open(path, O_RDONLY);
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
							ticket[tc].str = malloc(strlen(temp));
							ticket[tc].counter = 1;
							int lo = 0;
							flag = 0;
							while(ticket[lo].str[0] != 0)
							{
								if(strcmp(ticket[lo].str, temp) == 0)
								{
									int toto = find_index(ticket, temp);
									ticket[toto].counter++;
									flag = 1;
								}
								lo++;
							}
							if(flag == 0)
							{
								strcpy(ticket[tc].str, temp);
							}
							tc++;
							break;
						}
					}
					temp[a] = t;
					a++;
				}
			}
		}
	}
	return(ticket);
}
