This code is not working and is giving back a component that is not correct. I don't know why, since the code is mostly identical to attempt 4.

EDIT: I had forgotten to check if the `strcmp` function == 0

Ok so I got the searching functions working.

```c
void* get_components(aspect_t* archetype, char* type, int archetype_length)
{
    for (int i = 0; i < archetype_length; i++)
    {
        if (strcmp(archetype[i].type, type) == 0)
        {
            return archetype[i].components;
        }
    }
    
    return NULL;
}
```

get_components gives back the array of components from an aspect. If finds the component array based on if the aspects "type" (aka `char*`) is named what the user wanted. Here is an example of this funciton in actions.

```c
pos_t* positions = (pos_t*)get_components(archetype, "pos", 2);
int* integers = (int*)get_components(archetype, "int", 2);
increase_y_system(positions, integers, 2);
```

Now with that fixed I made a simple function that iterates over each component and adds to the y value.

```c
void increase_y_system(pos_t* positions, int* integers, int num_elements)
{
    for (int i = 0; i < num_elements; i++)
    {
        positions[i].y += integers[i];
    }
}
```

We pass in the component arrays to the `increase_y_system` manually 

```c
pos_t* positions = (pos_t*)get_components(archetype, "pos", 2);
int* integers = (int*)get_components(archetype, "int", 2);

// simple funciton that iterates over components
increase_y_system(positions, integers, 2);
```