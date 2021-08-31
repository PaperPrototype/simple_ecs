#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// allocate memory with malloc based on count * type_size
void* vec_new(size_t type_size, int count)
{
    return malloc(type_size * count);
}

// get address of element in array
void* vec_get(void* vec, int index, size_t type_size)
{
    // return &vec[index * type_size];
    return (char*)vec + (index * type_size);
}

// allocate new array, memcpy previous contents into new array, free old array, set old pointer to new array
void vec_grow(void* vec, size_t type_size, int current_amount, int grow_amount)
{
	// allocate new array
	void* new = malloc(type_size * current_amount * grow_amount);

	// memcpy previous contents into new array
	memcpy(new, vec, type_size * current_amount);

	// free old array
	free(vec);

	// set old pointer to new array
	vec = new;
}

int main(void)
{
	int* integers = vec_new(sizeof(int), 2);

	integers[0] = 1;
	integers[1] = 3;

	printf("%i\n", integers[0]);
	printf("%i\n", integers[1]);

	vec_grow(integers, sizeof(int), 2, 2);

	integers[2] = 4;
	integers[3] = 5;

	printf("%i\n", integers[0]);
	printf("%i\n", integers[1]);
	printf("%i\n", integers[2]);
	printf("%i\n", integers[3]);
}