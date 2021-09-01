#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct pos {
    float x, y, z;
};

typedef struct pos pos_t;

const int MAX_COMPONENTS = 3;

void* get_component(int index, size_t size, void* unknown_type_array)
{
    // return &unknown_type_array[index * size];
    return (char*)unknown_type_array + (index * size);
}

void set_component(int index, size_t size, void* unkown_type_array, void* data)
{

    /* original method using type (working)

    pos_t* temp_pointer_known_type = unknown_type_array;
    temp_pointer_known_type[wanted_index] = (pos_t){0.0, 0.0, 0.0};

    */

    // get the component
    void* unknown_type = get_component(index, size, unkown_type_array);

    // set the component data
    memcpy(unknown_type, data, size);
}

int main(void)
{
    int wanted_index = 2;

    void* unknown_type_array = malloc(sizeof(pos_t) * MAX_COMPONENTS);

    // pos_t* temp_known_type = unknown_type_array;
    // temp_known_type[wanted_index] = (pos_t){0.0, 0.0, 0.0};

    // set the component
    set_component(wanted_index, sizeof(pos_t), unknown_type_array, &(pos_t){0.0, 0.0, 0.0});
    
    pos_t* wanted_component = get_component(wanted_index, sizeof(pos_t), unknown_type_array);

    printf("pos is (%f, %f, %f)", wanted_component->x, wanted_component->y, wanted_component->z);

    free(unknown_type_array);
}