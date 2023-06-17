#ifndef _SHELLV2_
#define _SHELLV2_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>


typedef struct commands 
{
    char *command;
    char *args[13];
    char *redirection_file;
    char *redirection;
    int pipe = 0;
    struct CommandNode *next;
} CommandNode;

char **env;


#endif


