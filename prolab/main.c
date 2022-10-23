#include "prolab.h"

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
        if (EndsWithtxt(search->d_name) == 0)//&& strcmp(search->d_name,"output.txt") != 0
		{
			if(flag==1)
				find_ticket(dir1, word ,search->d_name);
			else if(flag == 0)
				find_word(dir1, word, search->d_name);
			else if(flag == 2)
				find_all_ticket(dir1 , search->d_name);
		}
        if (search->d_type == DT_DIR && strcmp(search->d_name, ".") != 0 && strcmp(search->d_name, "..") != 0)
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
		remove("files.txt");
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
		print(f, tag);
	}
	else
		write(1, "hatali tuslama yaptiniz\n", 25);
}
