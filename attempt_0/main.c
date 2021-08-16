#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const size_t MAX_COMP = 120;

typedef struct pos {
    float x, y, z;
} pos_t;

// linked list node (with component array)
typedef struct node {
    char* type;
    void** components;
    int current_index;
    struct node* next;
} node_t;

// create a new component type node (with component array)
node_t* new_component_type(size_t size, char* type)
{
    node_t* temp = malloc(sizeof(node_t));

    temp->type = type;

    temp->components = malloc(MAX_COMP * size);

    temp->current_index = 0;

    temp->next = NULL;

    return temp;
}

node_t* get_component_type(node_t* node_head, char* type)
{
    node_t* current_node = node_head;
    
    while (current_node != NULL)
    {
        if (strcmp(current_node->type, type) == 0)
        {
            return current_node;
        }
        else
        {
            current_node = current_node->next;
        }
    }

    return NULL;
}

void* get_component(node_t* node_head, char* type, size_t size, int index)
{
    // TODO get component at index in component array
    node_t* components_node = get_component_type(node_head, type);

    return &components_node->components[index * size];
}

void add_component(node_t* node_head, char* type, void* data, size_t size)
{
    node_t* components_node = get_component_type(node_head, type);

    memcpy(&components_node->components[components_node->current_index * size], data, size);
}

void free_components(node_t* current_node)
{
    if (current_node->next == NULL)
    {
        return;
    }

    free_components(current_node->next);

    free(current_node->type);
    free(current_node->components);
    free(current_node);
}

int main()
{
    char* name_1 = malloc(sizeof(4));
    name_1 = "pos";
    node_t* head = new_component_type(sizeof(pos_t), name_1);
    char* name_2 = malloc(sizeof(4));
    name_2 = "int";
    head->next = new_component_type(sizeof(int), name_2);

    int* num_temp = malloc(sizeof(int));
    *num_temp = 120;

    add_component(head, "int", num_temp, sizeof(int));

    int* num_result = get_component(head, "int", sizeof(int), 0);

    printf("num is %i", *num_result);

    // free everything
    free_components(head->next);
    free_components(head);
}