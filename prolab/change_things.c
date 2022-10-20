#include "prolab.h"

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
