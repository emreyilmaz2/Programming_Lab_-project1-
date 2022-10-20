#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int main()
{
int fd;
mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
char *filename = "./universite/bolumler/bilgisayar.txt";
fd = open(filename, O_WRONLY);
printf("%d\n", fd);
}
