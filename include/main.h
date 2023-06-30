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

#include "kv_list_t.h"

typedef kv_list_t EnvNode;

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

extern char **env;

CommandNode* parse_input(char *line, CommandNode **head);
char *handle_builtins(char *line, CommandNode **head, EnvNode **top, char **env_array);
int check_pipe(char *token);
void handle_pipe(CommandNode **head, CommandNode *current, char* line);
int print_env(char **env_array);
uid_t get_uid(void);
void change_to_home_directory(EnvNode *top);
void change_to_previous_directory(EnvNode *top);
void change_directory(EnvNode *top, char *path);
CommandNode *create_node(char *command);
void free_command_list(CommandNode **head);
void add_argument(CommandNode *node, char *argument);
void setup_redirection(CommandNode *command);
void setup_pipe(CommandNode *current, int *pipefd, int input_fd);
void execute_command(CommandNode *command, int input_fd, char **env_array);
void cleanup_pipe(CommandNode *current, int *pipefd, int input_fd);
void execute_commands(CommandNode *head, char **env_array);
void setup_output_redirection(CommandNode *command);
void setup_input_redirection(CommandNode *command);
void setup_append_redirection(CommandNode *command);
void setup_heredoc_redirection(CommandNode *command);
void setup_redirection(CommandNode *command);
int check_redirections(char *token);
void handle_redirection(CommandNode *node, char *redirection);
char *pathfinder(char *command, EnvNode **top);
ssize_t getline(char **lineptr, size_t *n, FILE *stream);
int fileno(FILE *stream);
int setenv(const char *name, const char *value, int overwrite);
EnvNode* load_env(char **envp);
EnvNode* create_kv_node(char *key, char *value);
void add_node_to_list(EnvNode **top, EnvNode *node);
void free_env_list(EnvNode **top);
int set_env(EnvNode **top, char *key, char *value);
char* get_env(EnvNode *top, char *key);
int unset_env(EnvNode **top, char *key);
char **linked_list_to_array(EnvNode **top);
void free_array(char** array);

#endif


