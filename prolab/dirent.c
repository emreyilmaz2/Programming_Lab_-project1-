#include "prolab.h"

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
	fd = fopen("files.txt", "a+");
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
