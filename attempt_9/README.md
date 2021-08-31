So before I continued any further I needed a simple method for a growable array.

I did this quite simply by extending what I had done previously with my "generic array". All I had to do was add one extra function for "growing" the generic array.

```c
void vec_grow(void* vec, size_t type_size, int current_amount, int grow_amount)
{
	void* new = malloc(type_size * current_amount * grow_amount);

	memcpy(new, vec, type_size * current_amount);

	free(vec);

	vec = new;
}
```

I also renamed all the functions and variables to be consistent with the word "vec" rather than "generic_array".

```c
void* vec_new(size_t type_size, int count)
{
    return malloc(type_size * count);
}

// get address of element in array
void* vec_get(int index, size_t type_size, void* vec)
{
    // return &vec[index * type_size];
    return (char*)vec + (index * type_size);
}
```

I also discovered why one of my previous ECS's was giving me a segfault. The below function was to blame!

```c
void vec_set(int index, size_t type_size, void* vec, void* data)
{
    // get the component
    void* unknown = vec_get(index, type_size, vec);

    // copy data into vec type address
    memcpy(unknown, data, type_size);
}
```

After realizeing this I thought about my previous ECS's. The ones that were working (and didn't give a segfault) were NOT using the `vec_set` (previously called "set_item")! Now I can forge ahead with this neew tool and continue on my journey!