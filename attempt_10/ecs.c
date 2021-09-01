#include "vec.c"

typedef struct float3 {
	float x, y, z;
} float3_t;

typedef float3_t pos_t;
typedef float3_t rot_t;

const int CHUNK_SIZE = 4;

typedef struct aspect 
{
	char* type;
	void* data;
} aspect_t;

typedef struct arch
{
	aspect_t* aspects;
	int num;
	int max;
	int cur;
} arch_t;

typedef struct world
{
	arch_t* archetypes;
	int max;
	int cur;
} world_t;

world_t* ecs_new_world()
{
	printf("ecs new world\n");
	world_t* world = malloc(sizeof(world_t));
	world->archetypes = malloc(sizeof(arch_t) * CHUNK_SIZE);
	world->max = CHUNK_SIZE;
	world->cur = 0;

	return world;
}

void ecs_world_add_arch(world_t* world, arch_t arch)
{
	printf("ecs world add arch\n");
	// if array is full
	if (world->cur >= world->max)
	{
		printf("ecs world add arch/vec_grow archetypes array\n");
		// grow array (aka vec)
		vec_grow(world->archetypes, sizeof(arch_t), world->cur, CHUNK_SIZE);
		// increase max (aka, array size) since array has grown
		world->max += CHUNK_SIZE;
	}
	
	// add archetype
	world->archetypes[world->cur] = arch;
	world->cur += 1;

	printf("ecs world add arch/world info: cur = %i, max = %i\n", world->cur, world->max);
}

void ecs_free_world(world_t* world)
{
	printf("ecs free world\n");
	printf("ecs free world/world info: cur = %i, max = %i\n", world->cur, world->max);

	// archetypes array
	arch_t* arch = world->archetypes;
	
	// foreach malloc'd archetype
	for (int arch_i = 0; arch_i < world->cur; arch_i++)
	{	
		printf("ecs free world/current arch: %i\n", arch_i);

		// aspects in archetype
		aspect_t* aspect = arch->aspects;

		// foreach aspect
		for (int asp_i = 0; asp_i < arch->num; asp_i++)
		{
			printf("ecs free world/current aspect: %i\n", asp_i);

			// free the aspects data
			free(aspect->data);

			// next aspect
			++aspect;
		}

		printf("ecs free world/freeing aspects\n");
		// free aspects
		free(arch->aspects);

		// next archetype
		++arch;
	}

	printf("ecs free world/freeing archetypes\n");
	// free archetypes
	free(world->archetypes);

	printf("ecs free world/freeing world\n");
	// free world
	free(world);
}

arch_t ecs_new_arch(int num_types)
{
	printf("ecs new arch\n");
	arch_t arch;
	arch.aspects = malloc(sizeof(aspect_t) * num_types);
	// num types in archetype
	arch.num = num_types;

	// max array size for components
	arch.max = CHUNK_SIZE;
	// current number of components
	arch.cur = 0;

	return arch;
}

aspect_t ecs_new_aspect(char* type, size_t type_size)
{
	printf("ecs new aspect\n");
	aspect_t aspect;
	aspect.data = malloc(type_size * CHUNK_SIZE);
	aspect.type = type;

	return aspect;
}

aspect_t* ecs_get_aspect(arch_t* arch, char* type)
{
	printf("ecs get aspect\n");
	for (int i = 0; i < arch->num; i++)
	{
		if (strcmp(arch->aspects[i].type, type) == 0)
		{
			return &arch->aspects[i];
		}
	}

	printf("aspect not found! returning NULL (void*) aspect\n");
	return NULL;
}

void* ecs_get_components(arch_t* arch, char* type)
{
	printf("ecs get components\n");
	aspect_t* aspect = arch->aspects; // = ecs_get_aspect(arch, type);

	for (int i = 0; i < arch->num; i++)
	{
		if (strcmp(aspect[i].type, type) == 0)
		{
			return aspect[i].data;
		}
	}

	printf("aspect and its components not found! returning NULL (void*) component array\n");
	return NULL;
}

int main(void)
{
	world_t* world = ecs_new_world();
	
	arch_t archetype1 = ecs_new_arch(2);
	archetype1.aspects[0] = ecs_new_aspect("pos", sizeof(pos_t));
	archetype1.aspects[1] = ecs_new_aspect("rot", sizeof(rot_t));

	ecs_world_add_arch(world, archetype1);
	
	pos_t* positions = ecs_get_components(&archetype1, "pos");
	rot_t* rotations = ecs_get_components(&archetype1, "rot");

	// testing the capability's of the "vec_grow" function by adding many archetypes
	printf("testing growable vector capabilitys\n");
	arch_t arch2 = ecs_new_arch(1);
	ecs_world_add_arch(world, arch2);

	arch_t arch3 = ecs_new_arch(1);
	ecs_world_add_arch(world, arch3);
	
	arch_t arch4 = ecs_new_arch(1);
	ecs_world_add_arch(world, arch4);
	
	/*
	arch_t arch5 = ecs_new_arch(1);
	ecs_world_add_arch(world, arch5);

	arch_t arch6 = ecs_new_arch(1);
	ecs_world_add_arch(world, arch6);

	arch_t arch7 = ecs_new_arch(1);
	ecs_world_add_arch(world, arch7);
	*/
	
	ecs_free_world(world);
}
