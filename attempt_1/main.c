#include <stdlib.h>
#include <stdio.h>

const int MAX_COMP = 120;

typedef struct pos {
    float x, y, z;
} pos_t;

typedef struct aspect {
    size_t size;
    void* components;
} aspect_t;

aspect_t* new_aspect(size_t size)
{
    aspect_t* aspect = malloc(sizeof(aspect_t));

    aspect->components = malloc(size * MAX_COMP);
    aspect->size = size;

    return aspect;
}

int main(void)
{
    // without generic function
    aspect_t* aspect = malloc(sizeof(aspect_t));

    aspect->components = malloc(sizeof(pos_t) * MAX_COMP);
    aspect->size = sizeof(pos_t);

    pos_t position = {4, 0, 2};

    pos_t* comp_array = aspect->components;
    comp_array[0] = position;

    printf("position is (%f, %f, %f)\n", comp_array[0].x, comp_array[0].y, comp_array[0].z);

    free(aspect->components);
    free(aspect);

    // with generic function
    aspect_t* aspect_1 = new_aspect(sizeof(pos_t));

    // aspect_1->components[0, size_to_iterate] = position;

    // pos_t typed_pos = typed_components[0];

    // printf("positon is (%f, %f, %f)\n", typed_pos.x, typed_pos.y, typed_pos.z);

    free(aspect_1->components);
    free(aspect_1);

    // origianl testing, no functions
    void* components = malloc(sizeof(pos_t) * MAX_COMP);

    int index = 0;

    pos_t pos = {0, 0, 0};

    pos_t* components1 = components;

    components1[index] = pos;

    printf("pos is (%f, %f, %f)", components1[index].x, components1[index].y, components1[index].z);

    // (pos_t*)components[index] = pos;

    free(components);
}