#include "prolab.h"

void	print(FILE *fd, int line, int flag, char *str)
{
	fprintf(fd, "\n\n-----UPDATE-----\n");
	fprintf(fd, "Etiket Listesi   -   Tekrar sayisi\n");
	if(flag == 1)
	{
		fprintf(fd, "--%s--          -1-", str);
	}
	else if(flag == 0)
	{
		fprintf(fd, "Yetim etiketler\n--%s--", str);
	}
}

int main()
{
	char *str = malloc(sizeof(char *));
	int num = 0;
	printf("Merhaba lutfen yapmak istediginiz islemi secin:\n");
	printf("1-)---kelime arama----\n2-)---etiket arama----\n3-)-etiket guncelleme-\n4-)---dosyaya yazma---\n");
	scanf("%d", &num);
	if(num == 1) //kelime arama kismi
	{
		scanf(" %[^\n]s", str);
		find_word(str);
		//fopen("files.txt", "w"); //dosyayi yeniden acarak temizlenmesini sagliyor
	}
	else if(num == 2) // tag arama kismi
	{
		find_txt();
		scanf(" %[^\n]s", str);
		find_ticket(str);
	}
	else if(num == 3) //etiket guncelleme
	{
		char *new_word = malloc(sizeof(char *));
		printf("you need the enter ticket that you wanna change\n");
		scanf(" %[^\n]s", str);
		printf("enter the new ticket\n");
		scanf(" %[^\n]s", new_word);
		char *path = malloc(sizeof(char *));
		char *new_path= malloc(sizeof(char *));
		strcpy(path, str);
		strcpy(new_path, new_word);
		change_things(str, new_word, strcat(path, ".txt"), strcat(new_path, ".txt"));
		printf("--> islem basariyla gerceklestirildi <--");
	}
	else if(num == 4)
	{
	}
	else
		write(1, "hatali tuslama yaptiniz\n", 25);
}
