#include "header.h"

int set_env(EnvNode **top, char *key, char *value)
{
    EnvNode *current = *top, *node;
    while (current != NULL)
    {
        if (string_compare(current->key, key) == 0)
        {
            free(current->value);
            current->value = copy_string(value);
            return (1);
        }
        current = current->next;
    }
    node = create_kv_node(key, value);
    add_node_to_list(top, node);
    return (1);
}

char* get_env(EnvNode *top, char *key)
{
    EnvNode *current = top;
    while (current != NULL)
    {
        if (string_compare(current->key, key) == 0)
        {
            return (current->value);
        }
        current = current->next;
    }
    return (NULL);
}

int unset_env(EnvNode **top, char *key)
{
    EnvNode *current = *top;
    EnvNode *prev = NULL;

    while (current != NULL)
    {
        if (string_compare(current->key, key) == 0) {
            if (prev == NULL) {
                *top = current->next;
            } else {
                prev->next = current->next;
            }
            free(current->key);
            free(current->value);
            free(current);
            return (1);
        }
        prev = current;
        current = current->next;
    }
    return (1);
}
char **linked_list_to_array(EnvNode **top)
{
    int count = 0, length, i = 0;
    char **array;
    EnvNode *current = *top;

    while (current != NULL) {
        count++;
        current = current->next;
    }

    array = (char**)malloc((count + 1)* sizeof(char*));
    if (array == NULL)
    {
        printf("Memory allocation failed!");
        exit(1);
    }

    current = *top;
    while (current != NULL)
    {
        length = (string_length(current->key) + string_length(current->value) + 2);
        array[i] = (char*)malloc((length) * sizeof(char));
        if (array[i] == NULL)
        {
            printf("Memory allocation failed!");
            exit(1);
        }
        sprintf(array[i], "%s=%s", current->key, current->value);
        //printf("%s\n", array[i]);

        current = current->next;
        i++;
    }
    array[i] = NULL;
    return (array);
}

void free_array(char** array)
{
    int i;

    for (i = 0; array[i] != NULL; i++)
    {
        free(array[i]);
    }
    free(array);
}

