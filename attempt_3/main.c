#include "generic_array.c"
#include <stdio.h>

typedef struct pos {
    float x, y, z;
} pos_t;

const int NUM_ELEMENTS = 10;

int main(void)
{
    size_t type_size = sizeof(pos_t);

    void* generic_array = new_generic_array(type_size, NUM_ELEMENTS);

    pos_t position1 = {0.0, 0.0, 0.0};

    set_item(0, type_size, generic_array, &position1);

    pos_t result = *(pos_t*)get_item(0, type_size, generic_array);

    printf("pos is (%f, %f, %f)", result.x, result.y, result.z);

    // don't forget to free!
    free(generic_array);
}