#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <stdio.h>

int EndsWithtxt(char *string)
{
    string = strrchr(string, '.');
    if (string != NULL)
        return (strcmp(string, ".txt"));
    return (-1);
}

void searchf1(const char *dir1, char *word2)
{
    DIR *dir2 = opendir(dir1);
    if (dir2 == NULL)
        return;
    struct dirent *search;
    search = readdir(dir2);
    while (search != NULL)
    {
        char path[100] = {0};
        if (EndsWithtxt(search->d_name) == 0 && strcmp(search->d_name,"output.txt") != 0)
        {
			printf("%s\n", search->d_name);
			printf("%s\n", dir1);
            //texsfinderZ(search->d_name, word,dir1);
        }
        if (search->d_type == DT_DIR && strcmp(search->d_name, ".") != 0 && strcmp(search->d_name, "..") != 0)
        {
            strcat(path, dir1);
            strcat(path, "/");
            strcat(path, search->d_name);
            searchf1(path,word2);
        }
        search = readdir(dir2);
    }
    closedir(dir2);
}

int main()
{
	searchf1(".", "erme");
}
