#include <stdlib.h>
#include <string.h>

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