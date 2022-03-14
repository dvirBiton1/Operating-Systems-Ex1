#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include "Ex1.h"
void dirFunc()
{
    DIR *dir;
    struct dirent *sd;
    dir = opendir(".");
    if (dir == NULL)
    {
        printf("Error! Unable to open directory.\n");
        exit(1);
    }
    while ((sd = readdir(dir)) != NULL)
    {
        printf(">> %s\n", sd->d_name);
    }
    closedir(dir);
    return;
}
void pathFunc()
{
    char cwd[PATH_MAX];
    if (getcwd(cwd, sizeof(cwd)) != NULL)
    {
        printf("Current working dir: %s\n", cwd);
    }
    else
    {
        perror("getcwd() error");
        exit(1);
    }
}

int main()
{

    char input[50] = {0};
    pathFunc();
    scanf("%[^\n]%*c", input);
    int len = strlen(input);
    for (int i = 0; i < len; i++)
    {
        printf("%c", input[i]);
    }
    printf("\n");
    while (strcmp(input, "EXIT"))
    {
        if (strncmp(input, "ECHO", 4) == 0)
        {
            printf(">>");
            // printf("%d\n", len);
            for (int i = 4; i < 50; i++)
            {
                printf("%c", input[i]);
            }

            printf("\n");
        }
        else if (strncmp(input, "DIR", 3) == 0)
        {
            dirFunc();
        }
        else if (strncmp(input, "TCP PORT", 8) == 0)
        {
            powerClient();
        }
        /*
         chdir() changes the current working directory
         of the calling process to the directory specified in path
         so it is system call.
        */
        else if (strncmp(input, "CD", 2) == 0)
        {
            char path[50];
            bzero(path, 50);
            int j = 0;
            for (int i = 3; i < strlen(input); i++, j++)
            {
                path[j] = input[i];
            }
            chdir(path);
            pathFunc();
        }
        /*
        The  system() library function uses fork(2)
        to create a child process that executes the shell command specified
        in command.
        */
        else
        {
            system(input);
        }
        bzero(input, 50);
        scanf("%[^\n]%*c", input);
    }
    printf("good bye\n");

    return 0;
}
