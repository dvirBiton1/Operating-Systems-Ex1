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

int main()
{
    char cwd[PATH_MAX];
    char input[20] = {0};
    if (getcwd(cwd, sizeof(cwd)) != NULL)
    {
        printf("Current working dir: %s\n", cwd);
    }
    else
    {
        perror("getcwd() error");
        return 1;
    }
    scanf("%[^\n]%*c", input);
    for (int i = 0; i < 10; i++)
    {
        printf("%c", input[i]);
    }
    printf("\n");

    int len = strlen(input);
    while (strcmp(input, "EXIT"))
    {
        if (strncmp(input, "ECHO", 4) == 0)
        {
            printf(">>");
            for (int i = 4; i < len; i++)
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
        else
        {
            printf(">> commmand not found\n");
        }
        bzero(input, 20);
        scanf("%[^\n]%*c", input);
    }
    printf("good bye\n");

    return 0;
}
