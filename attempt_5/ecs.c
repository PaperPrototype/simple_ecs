
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// aspect = block (component) type
typedef struct aspect {
    char* type;
    void* components;
} aspect_t;

typedef struct pos {
    float x, y, z;
} pos_t;

void* new_generic_array(size_t type_size, int num_elements)
{
    return malloc(type_size * num_elements);
}

void* get_item(int index, size_t size, void* unknown_type_array)
{
    // return &unknown_type_array[index * size];
    return (char*)unknown_type_array + (index * size);
}

void set_item(int index, size_t size, void* unkown_type_array, void* data)
{
    // get the component
    void* unknown_type = get_item(index, size, unkown_type_array);

    // set the component data
    memcpy(unknown_type, data, size);
}

// gets an aspect (component type) based on its type name
void* get_aspect_type(aspect_t* archetype, char* type, int archetype_length)
{
    for (int i = 0; i < archetype_length; i++)
    {
        if (strcmp(archetype[i].type, type))
        {
            return &archetype[i];
        }
    }
    
    return NULL;
}

void* search_archetype(int component_index, char* type, size_t type_size, aspect_t* archetype, int num_aspects_in_archetype)
{
    // loop through array of aspects 
    for (int i = 0; i < num_aspects_in_archetype; i++)
    {
        // check if current aspect is correct
        if (strcmp(archetype[i].type, type) == 0)
        {
            // if current aspect is correct, then, search through generic array and get component at index
            return get_item(component_index, type_size, archetype[i].components);
        }
    }

    return NULL;
}

int main(void)
{
    int component_column_depth = 2;

    // archetype is a combination of aspects (component types)
    aspect_t* archetype = malloc(sizeof(aspect_t) * 2);

    archetype[0].components = new_generic_array(sizeof(pos_t), component_column_depth);
    archetype[0].type = "pos";

    set_item(0, sizeof(pos_t), archetype[0].components, &(pos_t){2.231f, 0.0f, 1.0f});
    set_item(1, sizeof(pos_t), archetype[0].components, &(pos_t){1.0f, 9.4f, 1.0f});

    archetype[1].components = new_generic_array(sizeof(int), component_column_depth);
    archetype[1].type = "int";

    int tmp1 = 12;
    int tmp2 = 13;
    set_item(0, sizeof(int), archetype[1].components, &tmp1);
    set_item(1, sizeof(int), archetype[1].components, &tmp2);

    // for each entity in archetype
    for (int entity_index = 0; entity_index < component_column_depth; entity_index++)
    {
        pos_t* position = search_archetype(entity_index, "pos", sizeof(pos_t), archetype, 2);
        int* integer = search_archetype(entity_index, "int", sizeof(int), archetype, 2);
        
        printf("pos (%f, %f, %f)\n", position->x, position->y, position->z);
    }
    
    // free memory
    free(archetype[0].components);
    free(archetype[1].components);
    free(archetype);
}
