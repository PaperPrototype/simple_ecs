Finally I managed to make a simple way of representing archetypes. I managed to make the system a bit more concise. Previously to make an archetype was a ton of work.

(previously)
```c
int component_column_depth = 2;

// archetype is a combination of aspects (component types)
aspect_t* archetype = malloc(sizeof(aspect_t) * 2);

archetype[0].components = new_generic_array(sizeof(pos_t), component_column_depth);
archetype[0].type = "pos";

set_item(0, sizeof(pos_t), archetype[0].components, &(pos_t){2.231f, 0.0f, 1.0f});
set_item(1, sizeof(pos_t), archetype[0].components, &(pos_t){1.0f, 9.4f, 1.0f});

archetype[1].components = new_generic_array(sizeof(int), component_column_depth);
archetype[1].type = "int";

int tmp1 = 12;
int tmp2 = 13;
set_item(0, sizeof(int), archetype[1].components, &tmp1);
set_item(1, sizeof(int), archetype[1].components, &tmp2);
```

But now this code has been simplified to this

```c
archetype_t* archetype = new_archetype(3);
archetype->aspects[0] = set_aspect(sizeof(pos_t), "pos", MAX_COMPONENTS);
archetype->aspects[1] = set_aspect(sizeof(int), "int", MAX_COMPONENTS);
archetype->aspects[2] = set_aspect(sizeof(vel_t), "vel", MAX_COMPONENTS);

// set component data.
for (int i = 0; i < MAX_COMPONENTS; i++)
{
	// set positions
	pos_t* positions = archetype->aspects[0].data;
	positions[i] = (pos_t){0.1, 3.4, 1};

	// set velocities
	vel_t* velocities = archetype->aspects[2].data;
	velocities[i] = (vel_t){2.3, 1.5, 0.9};

	// set ints
	int* ints = archetype->aspects[2].data;
	ints[i] = (int)1;
}
```

Which isn't a whole lot less code, but it looks much nicer. Next I want to store different types of archetypes in an array of archetypes (which I will use as the central point for accessing all the data in the world).

I will also need to figure out a "query" system that gives me all the matching archetypes and their components. Then I will have a working ECS!