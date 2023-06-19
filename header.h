#ifndef _SHELLV2_
#define _SHELLV2_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <pwd.h>



typedef struct commands CommandNode;
struct commands
{
    char *command;
    char *args[13];
    char *redirection_file;
    char *redirection;
    int pipeflag;
    CommandNode *next;
};

char **env;


int string_compare(char *str1, char *str2);
int string_length(char *str);
void copy_string(char *string, char *dest);
CommandNode* parse_input(char *line, CommandNode **head);
void handle_builtins(char *line);
int check_pipe(char *token);
void handle_pipe(CommandNode **head, CommandNode *current, char* line);
int print_env();
uid_t get_uid(void);
void change_to_home_directory();
void change_to_previous_directory();
void change_directory(char *path);
CommandNode *create_node(char *command);
void free_command_list(CommandNode *head);
void add_argument(CommandNode *node, char *argument);
void setup_redirection(CommandNode *command);
void setup_pipe(CommandNode *current, int *pipefd, int input_fd);
void execute_command(CommandNode *command, int input_fd);
void cleanup_pipe(CommandNode *current, int *pipefd, int input_fd);
void execute_commands(CommandNode *head);
void setup_output_redirection(CommandNode *command);
void setup_input_redirection(CommandNode *command);
void setup_append_redirection(CommandNode *command);
void setup_heredoc_redirection(CommandNode *command);
void setup_redirection(CommandNode *command);
int check_redirections(char *token);
void handle_redirection(CommandNode *node, char *redirection);

#endif


