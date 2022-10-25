#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <dirent.h>
#include <glob.h>
typedef struct ticket
{
	char *str;
	int counter;
} ticket_s;

#define BUFFER_SIZE 1000
#define i_tag 0

void replace(char *str, const char *oldWord, const char *newWord)
{
    char *pos, temp[BUFFER_SIZE];
    int index = 0;
    int owlen;

    owlen = strlen(oldWord);
    if (!strcmp(oldWord, newWord)) {
        return;
    }
    while ((pos = strstr(str, oldWord)) != NULL)
    {
        strcpy(temp, str);
        index = pos - str;
        str[index] = '\0';
        strcat(str, newWord);
        strcat(str, temp + index + owlen);
    }
}

char *get_next_line(int fd)
{
    int 	i = 0;
    int 	rd = 0;
    char	character;
    char 	*buffer = malloc(10000);
    while ((rd = read(fd, &character, 1)) > 0)
    {
        buffer[i++] = character;
        if (character == '\n')
            break;
    }
    if ((!buffer[i - 1] && !rd) || rd == -1)
    {
        free(buffer);
        return (NULL);
    }
    return(buffer);
}

int	is_orphan(char *word)
{
	int fd0;
	char *wow;
	chdir("..");
	chdir("..");
	fd0 = open("./files.txt", O_RDONLY);
	wow = get_next_line(fd0);
	while(wow)
	{
		printf("%s ---- %s\n", word, wow);
		if(strstr(wow, word))
			return(1);
		wow = get_next_line(fd0);
	}
	close(fd0);
	return(0);
}

int ft_strnstr(const char *haystack, const char *needle, int flag)
{
    size_t    i;
    size_t    c;
    size_t    n_len;
    char    *hay;
    i = 0;
    hay = (char *)haystack;
    n_len = strlen(needle);
    if (n_len == 0 || haystack == needle)
        return (0);
    while (hay[i] != '\0')
    {
        c = 0;
        while (hay[i + c] != '\0' && needle[c] != '\0'
            && hay[i + c] == needle[c])
            c++;
        if (c == n_len && flag == 0)
        {
			if(haystack[i-2] == '[' && haystack[i-1] == '[')
			{
				if(haystack[i+n_len] == ']' && haystack[i+n_len+1] == ']')
					return(1);
			}
			else
				return(0);
        }
        else if(c == n_len && flag ==1)
            return(1);
        i++;
    }
    return (0);
}

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
				//printf("%d\n", is_orphan(word));
				//if(!is_orphan(word))
				//	printf(" * %s isimli YETIM etiket '%s' adli dosyada --> %d. satirda bulundu\n", word,path,line);
				//else if(is_orphan(word))
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

void	print(FILE *fd, ticket_s *ticket)
{
	int i=0;
	fprintf(fd, "\n\n-----UPDATE-----\n");
	fprintf(fd, "Etiket Listesi   -   Tekrar sayisi\n");
	for(int a=0; ticket[a].str[0]; a++){
		fprintf(fd, "%s                       %d\n", ticket[a].str, ticket[a].counter);
	}
}

int EndsWithtxt(char *string)
{
    string = strrchr(string, '.');
    if (string != NULL)
        return (strcmp(string, ".txt"));
    return (-1);
}

void searchf1(const char *dir1, char *word, int flag)
{
	DIR *dir2 = opendir(dir1);
    if (dir2 == NULL)
		return;
    struct dirent *search;
    search = readdir(dir2);
	if(search == NULL)
		return;
    while (search != NULL)
    {
        char path[100] = {0};
        if ((EndsWithtxt(search->d_name) == 0) && strcmp(search->d_name,"output.txt") != 0 && strcmp(search->d_name,"files.txt") != 0)
		{
			if(flag==1)
				find_ticket(dir1, word ,search->d_name);
			else if(flag == 0)
				find_word(dir1, word, search->d_name);
			else if(flag == 2)
				find_all_ticket(dir1 , search->d_name);
		}
        if (search->d_type == DT_DIR && strcmp(search->d_name, ".") != 0 && strcmp(search->d_name, "..") != 0 && strcmp(search->d_name, "output.txt") != 0 && strcmp(search->d_name,"files.txt") != 0)
        {
            strcat(path, dir1);
            strcat(path, "/");
            strcat(path, search->d_name);
            searchf1(path, word, flag);
        }
        search = readdir(dir2);
    }
    closedir(dir2);
}

void    change_things(char *word, char *new_word, char *path, char *new_path)
{

    FILE * fPtr;
    FILE * fTemp;
    char buffer[BUFFER_SIZE];
    fPtr  = fopen(path, "r");
    fTemp = fopen("replace.tmp", "w");
    if (fPtr == NULL || fTemp == NULL)
    {
        printf("\nUnable to open file.\n");
        printf("Please check whether file exists and you have read/write privilege.\n");
        exit(EXIT_SUCCESS);
    }
    while ((fgets(buffer, BUFFER_SIZE, fPtr)) != NULL)
    {
        replace(buffer, word, new_word);
        fputs(buffer, fTemp);
    }
    fclose(fPtr);
    fclose(fTemp);
    remove(path);
    rename("replace.tmp", new_path);
}

static	char **dirent(char *src) {
	DIR *d;
	struct dirent *dir;
	int i = 0;
	char **directs = malloc(sizeof(char **));
	d = opendir(src);
	if (d)
	{
		while ((dir = readdir(d)) != NULL)
		{
			if(dir->d_name[0] != '.')
			{
				directs[i] = malloc(1000);
				strcpy(directs[i], dir->d_name);
				i++;
			}
		}
		closedir(d);
	}
	return (directs);
}

static	void	find_txt2(char *path)
{
	FILE *fd;
	int o=0;
	fd = fopen("files.txt", "at+");
	const char *pattern = strcat(path, "/*.txt");
	glob_t pglob;
	glob(pattern, GLOB_ERR, NULL, &pglob);
	if(pglob.gl_pathc == 0)
		return;
	while(o < pglob.gl_pathc)
	{
		fprintf(fd, "%s\n", pglob.gl_pathv[o]);
		o++;
	}
	fclose(fd);
}

void	find_txt(void)
{
	char **Res = malloc (100);
	char *str = malloc(100);
	strcpy(str, "./universite");
	Res = dirent(str);
	int x = 0;
	char *temp;
	while(x < 2)
	{
		temp = malloc(sizeof(char)*100);
		strcpy(temp, str);
		strcat(temp, "/");
		strcat(temp, Res[x]);
		find_txt2(temp);
		free(temp);
		x++;
	}
	free(Res);
}

int main()
{
	char *string = malloc(sizeof(char *));
	int num = 0;
	printf("Merhaba lutfen yapmak istediginiz islemi secin:\n");
	printf("1-)---kelime arama----\n2-)---etiket arama----\n3-)-etiket guncelleme-\n4-)---dosyaya yazma---\n");
	scanf("%d", &num);
	if(num == 1) //kelime arama kismi
	{
		scanf(" %[^\n]s", string);
		searchf1(".", string, 0);
	}
	else if(num == 2) // tag arama kismi
	{
		find_txt();
		scanf(" %[^\n]s", string);
		searchf1(".", string, 1);
	}
	else if(num == 3) //etiket guncelleme
	{
		char *new_word = malloc(sizeof(char *));
		printf("you need the enter ticket that you wanna change\n");
		scanf(" %[^\n]s", string);
		printf("enter the new ticket\n");
		scanf(" %[^\n]s", new_word);
		char *path = malloc(sizeof(char *));
		char *new_path= malloc(sizeof(char *));
		strcpy(path, string);
		strcpy(new_path, new_word);
		change_things(string, new_word, strcat(path, ".txt"), strcat(new_path, ".txt"));
		printf("--> islem basariyla gerceklestirildi <--");
	}
	else if(num == 4)
	{
		FILE *f;
		ticket_s *tag;
		searchf1(".", "", 2);
		//tag = find_all_ticket(pat);
		f = fopen("output.txt", "a");
		//print(f, tag);
	}
	else
		write(1, "hatali tuslama yaptiniz\n", 25);
}
