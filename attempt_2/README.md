The goal was to make an array of elements, each element is the same type / size, but the array can't know its type (because I want to be able to store anything I want in this array, like a generic array in C++), so I had to figure out how to offset in the array using the iterator `[]`. I initalize the array using malloc based on the type size.

```c
void* unknown_type_array = malloc(type_size * MAX_COMPONENTS);
```

The problem arises later when using the iterator `[]` was that it offsets in memory based on the type size to access sequential elements, but I am using an address that was per byte (aka `void*`) which has no type, and its size is 1 byte. I had to manually offset in the array based on size of the desired type when trying to access an element.

```c
void* get_component(int index, size_t size, void* unknown_type_array)
{
    return &unknown_type_array[index * size];
}
```

This worked, but there is also another way of offsetting in memory without using the iterator `[]`.

```c
void* get_component(int index, size_t size, void* unknown_type_array)
{
    // return &unknown_type_array[index * size];
    return (char*)unknown_type_array + (index * size);
}
```

Tada! access elements in an array, without knowing the type of the array! (We use the sizeof the type for offsetting, because you cannot pass type's info around using a variable, so you have to manuallly know its size using a number).

I got that working! and it compiled!

Now when I call the function I cast the recieving type correctly.

```c
pos_t* wanted_component = get_component(wanted_index, sizeof(pos_t), unknown_type_array);
```

obviously I have to cast to the type if I want a usable variable. Don't worry in this case I knew the type in the array.

I then needed to be able to set data in the array. First I did this non generically.

```c
// method using type
pos_t* temp_known_type = unknown_type_array;
temp_known_type[wanted_index] = (pos_t){0.0, 0.0, 0.0};
````

I casted the array to its type. then I could set the info in the array using the default iterator `[]`... but this wasnt going to work since later I will have to access each element without knowing the type of the array.

In the end this is what I figured out (with help form @phyrolizer on Discord). I get a pointer to a spot in the components array using the "get_component" function. I then use memcpy, to paste in the data into the pointer to the element in the array, and memcpy takes a size <- memcpy which solved all my problems!

```c
void set_component(int index, size_t size, void* unkown_type_array, void* data)
{

    // -- ORIGINAL METHOD using type
    /*

    pos_t* temp_pointer_known_type = unknown_type_array;
    temp_pointer_known_type[wanted_index] = (pos_t){0.0, 0.0, 0.0};

    */

    // -- GENERIC METHOD without type info

    // get the component
    void* unknown_type = get_component(index, size, unkown_type_array);

    // set the component data
    memcpy(unknown_type, data, size);
}
```

You can compile my code an run it uisng whatever C compiler you use. It will print out

```
pos is (0.000000, 0.000000, 0.000000)
```

