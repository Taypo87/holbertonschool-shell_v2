#include "header.h"

int main(int argc, char **argv, char **envp)
{
    //check for pipes and redirections
    //First things first. get the user input with _getline
    //handle builtins
    //parse user input, this is tricky because of the pipes and redirects
    // must parse it in a manner that breaks it up into seperate commands
    // if operator is found
    char *line;
    char *buffer;
    CommandNode *head;

    env = envp;

    while (1)
    {
        if (isatty(STDIN_FILENO))
			printf("($) ");
        line = malloc(sizeof(char *) * 256);
        fflush(stdin);
        if (getline(&line, 0, stdin) == EOF)
        {
            if (isatty(STDIN_FILENO) != 0)
			    printf("\n");
            printf("I shouldnt see this message\n");
            //break;
        }
        handle_builtins(line); //check for builtins exit cd env
        head = parse_input(line, &head);

        execute_commands(&(*head));
        free(line);
    
    }
    exit(0);
}