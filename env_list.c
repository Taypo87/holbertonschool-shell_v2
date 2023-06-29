#include "header.h"

EnvNode* load_env(char **envp)
{
	EnvNode *top = NULL, *node;
	char *key, *value;
	int i = 0;
	while (envp[i] != NULL)
	{
		key = strtok(envp[i], "=");
		value = strtok(NULL, "\n");
		node = create_kv_node(key, value);
		add_node_to_list(&top, node);
		i++;
	}
	return (top);
}


