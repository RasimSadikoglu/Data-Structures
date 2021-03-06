#include "node.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* parse_input(char **line) {

    char *start = *line;
    
    int i;
    for (i = 0; start[i] != ',' && start[i] != '\0' && start[i] != '\n'; i++);
    start[i] = '\0';

    *line = *line + i + 1;

    return start;
}

node* node_create(int index, char *key, int freq) {
    node *n = malloc(sizeof(node));

    strncpy(n->key, key, CHAR_LENGTH);
    n->freq = freq;
    n->index = index;

    return n;
}

node** node_read_file(char *file_path) {

    size_t current_index = 0;

    node** nodes = malloc(sizeof(node*));
    nodes[current_index] = NULL;

    FILE *input_file = fopen(file_path, "r");

    char *buffer_memory = malloc(CHAR_LENGTH);
    while (fgets(buffer_memory, CHAR_LENGTH, input_file) != NULL) {
        char *buffer = buffer_memory;
        
        int index = atoi(parse_input(&buffer));
        char *key = parse_input(&buffer);
        int freq = atoi(parse_input(&buffer));

        nodes[current_index++] = node_create(index, key, freq);

        nodes = realloc(nodes, sizeof(node*) * (current_index + 1));
        nodes[current_index] = NULL;
    }
    free(buffer_memory);

    fclose(input_file);

    return nodes;

}