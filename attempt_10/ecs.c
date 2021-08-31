#include "vec.c"

typedef struct float3 {
	float x, y, z;
} float3_t;

typedef float3_t pos_t;
typedef float3_t rot_t;

const int CHUNK_SIZE = 16;

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
	world_t* world = malloc(sizeof(world_t));
	world->archetypes = malloc(sizeof(arch_t) * CHUNK_SIZE);
	world->max = CHUNK_SIZE;
	world->cur = 0;

	return world;
}

void ecs_world_add_arch(world_t* world, arch_t arch)
{
	// if array is full
	if (world->cur >= world->max)
	{
		// grow array (aka vec)
		vec_grow(world->archetypes, sizeof(arch_t), world->cur, CHUNK_SIZE);
		// increase max (aka, array size) since array has grown
		world->max += CHUNK_SIZE;
	}

	// add archetype
	world->archetypes[world->cur] = arch;
	world->cur += 1;
}

void ecs_free_world(world_t* world)
{
	// arhcetypes array
	arch_t* arch = world->archetypes;
	// foreach malloc'd archetype
	for (int arch_i = 0; arch_i < world->cur; arch_i++)
	{	
		// aspects in archetype
		aspect_t* aspect = arch->aspects;
		// foreach aspect
		for (int asp_i = 0; asp_i < arch->num; asp_i++)
		{
			// free the aspects data
			free(aspect->data);

			// next aspect
			++aspect;
		}

		// free aspects
		free(arch->aspects);

		// next archetype
		++arch;
	}

	// free archetypes
	free(world->archetypes);

	free(world);
}

arch_t ecs_new_arch(int num_types)
{
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
	aspect_t aspect;
	aspect.data = malloc(type_size * CHUNK_SIZE);
	aspect.type = type;

	return aspect;
}

aspect_t* ecs_get_aspect(arch_t* arch, char* type)
{
	for (int i = 0; i < arch->num; i++)
	{
		if (strcmp(arch->aspects[i].type, type) == 0)
		{
			return &arch->aspects[i];
		}
	}

	printf("aspect not found! returning NULL (void*) aspect");
	return NULL;
}

void* ecs_get_components(arch_t* arch, char* type)
{
	aspect_t* aspect = arch->aspects; // = ecs_get_aspect(arch, type);

	for (int i = 0; i < arch->num; i++)
	{
		if (strcmp(aspect[i].type, type) == 0)
		{
			return aspect[i].data;
		}
	}

	printf("aspect and its components not found! returning NULL (void*) component array ");
	return NULL;
}

int main(void)
{
	printf("new world\n");
	world_t* world = ecs_new_world();
	
	printf("new archetype\n");
	arch_t archetype1 = ecs_new_arch(2);
	printf("set aspects\n");
	archetype1.aspects[0] = ecs_new_aspect("pos", sizeof(pos_t));
	archetype1.aspects[1] = ecs_new_aspect("rot", sizeof(rot_t));

	printf("add archetype to world\n");
	ecs_world_add_arch(world, archetype1);
	
	printf("get component arrays\n");
	pos_t* positions = ecs_get_components(&archetype1, "pos");
	rot_t* rotations = ecs_get_components(&archetype1, "rot");
	
	printf("freed world");
	ecs_free_world(world);
}
