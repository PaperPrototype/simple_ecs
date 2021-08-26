#include "generic_array.c"
#include <stdlib.h>
#include <stdio.h>

const int MAX_COMPONENTS = 3;

typedef struct aspect
{
	void* data;
	char* type;
} aspect_t;

typedef struct archetype 
{
	aspect_t* aspects;
	int count;
} archetype_t;

typedef struct world
{
	archetype_t* archetypes;
	int count;
} world_t;

typedef struct float3
{
	float x, y, z;
} float3_t;

typedef float3_t pos_t;
typedef float3_t vel_t;

aspect_t set_aspect(size_t size, char* type, int num_components)
{
	// create new stack aspect_t
	aspect_t aspect;

	// set the type char*
	aspect.type = type;
	// set the data to heap array
	aspect.data = new_generic_array(sizeof(pos_t), MAX_COMPONENTS);

	// give back aspect
	return aspect;
}

archetype_t* new_archetype(int count)
{
	archetype_t* archetype = malloc(sizeof(archetype_t));

	archetype->count = count;
	archetype->aspects = malloc(sizeof(aspect_t) * count);

	return archetype;
}

void free_archetype(archetype_t* archetype)
{
	// foreach apsect in the archetype
	for (int i = 0; i < archetype->count; i++)
	{
		// free components array (aka "data")
		free(archetype->aspects[i].data);
	}
	
	// free the archetype
	free(archetype);
}

float3_t float3_add(float3_t a, float3_t b)
{
	float3_t result;

	result.x = a.x + b.x;
	result.y = a.y + b.y;
	result.z = a.z + b.z;

	return result;
}

void add_velocities_system(pos_t* positions, vel_t* velocities, int num_components)
{
	for (int i = 0; i < num_components; i++)
	{
		positions[i] = float3_add(positions[i], velocities[i]);
	}
}

void print_positions_system(pos_t* positions, int num_components)
{
	for (int i = 0; i < num_components; i++)
	{
		printf("pos_t (%f, %f, %f) \n", positions[i].x, positions[i].y, positions[i].z);
	}

	printf("\n");
}

int main(void)
{
	archetype_t* archetype = new_archetype(3);
	archetype->aspects[0] = set_aspect(sizeof(pos_t), "pos", MAX_COMPONENTS);
	archetype->aspects[1] = set_aspect(sizeof(int), "int", MAX_COMPONENTS);
	archetype->aspects[2] = set_aspect(sizeof(vel_t), "vel", MAX_COMPONENTS);

	// TODO set component data.
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

	// debug
	print_positions_system(archetype->aspects[0].data, MAX_COMPONENTS);

	// increase by velocities
	add_velocities_system(archetype->aspects[0].data, archetype->aspects[2].data, MAX_COMPONENTS);

	// debug
	print_positions_system(archetype->aspects[0].data, MAX_COMPONENTS);
	
	free_archetype(archetype);
}