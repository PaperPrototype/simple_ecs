#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// aspect = component type
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

// TODO
void* get_aspect(aspect_t* archetype, char* type)
{
    return NULL;
}

int main(void)
{
    int num_components = 2;

    // archetype is a combination of aspects (component types)
    aspect_t* archetype = malloc(sizeof(aspect_t) * 2);

    archetype[0].components = new_generic_array(sizeof(pos_t), num_components);
    archetype[0].type = "pos";

    set_item(0, sizeof(pos_t), archetype[0].components, &(pos_t){0.0f, 0.0f, 1.0f});
    set_item(1, sizeof(pos_t), archetype[0].components, &(pos_t){1.0f, 9.4f, 1.0f});

    archetype[1].components = new_generic_array(sizeof(int), num_components);
    archetype[1].type = "int";

    int tmp1 = 12;
    int tmp2 = 13;
    set_item(0, sizeof(int), archetype[1].components, &tmp1);
    set_item(1, sizeof(int), archetype[1].components, &tmp2);

    for (int i = 0; i < num_components; i++)
    {
        printf("entity %i ", i);

        //                                      aspect 0 = pos
        pos_t* pos = get_item(i, sizeof(pos_t), archetype[0].components);
        printf("pos (%f, %f, %f) ", pos->x, pos->y, pos->z);

        //                                        aspect 1 = int 
        int* integer = get_item(i, sizeof(int), archetype[1].components);
        printf("int %i ", *integer);

        printf("\n");
    }

    // free memory
    free(archetype[0].components);
    free(archetype[1].components);
    free(archetype);
}