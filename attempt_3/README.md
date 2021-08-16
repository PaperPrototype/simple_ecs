The goal here was to make a generic usable library for generic arrays.

When I recieve a data from `get_item` I could have done this

```c
pos_t* result = get_item(0, type_size, generic_array);
```

But... when I want to access the x y and z values I would have to dereference...

```c
pos_t* result = get_item(0, type_size, generic_array);

printf("pos is (%f, %f, %f)", result->x, result->y, result->z);
```

So I tried to dereference what get_item gave back...

```c
pos_t result = *get_item(0, type_size, generic_array);

printf("pos is (%f, %f, %f)", result.x, result.y, result.z);
```

But, when I dereference a `void*` (which is what "get_item" gives back) I have to cast the dereference.

```c
pos_t result = *(pos_t*)get_item(0, type_size, generic_array);

printf("pos is (%f, %f, %f)", result.x, result.y, result.z);
```

tada!

Now with this I can start working on an ECS entity component system in C!