#include "header.h"

Hashtable env_table; // Global hashtable for environmental variables

int main(int argc, char **argv, char **envp)
{
    // ...

    // Create and initialize the hashtable for environmental variables
    initialize_hashtable(&env_table);
    load_environment_variables(envp, &env_table);

    // ...

    return 0;
}

void initialize_hashtable(Hashtable *hashtable)
{
    for (int i = 0; i < TABLE_SIZE; i++) {
        hashtable->table[i] = NULL;
    }
}

void load_environment_variables(char **envp, Hashtable *hashtable)
{
    for (int i = 0; envp[i] != NULL; i++) {
        char *env_var = envp[i];
        char *key = strtok(env_var, "=");
        char *value = strtok(NULL, "=");

        insert(hashtable, key, value);
    }
}

void insert(Hashtable *hashtable, const char *key, const char *value)
{
    unsigned int index = hash(key);
    Node *new_node = create_node(key, value);
    if (new_node == NULL) {
        return;
    }
    Node *head = hashtable->table[index];
    if (head == NULL) {
        hashtable->table[index] = new_node;
    } else {
        Node *current = head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }
}

char *lookup(Hashtable *hashtable, const char *key)
{
    unsigned int index = hash(key);
    Node *current = hashtable->table[index];
    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            return current->value;
        }
        current = current->next;
    }
    return NULL;
}
