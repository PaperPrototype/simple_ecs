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
	aspect.data = new_generic_array(size, MAX_COMPONENTS);

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