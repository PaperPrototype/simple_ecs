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
	world_t* world = malloc(sizeof(world));
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
		// increase max since array has grown
		world->max += CHUNK_SIZE;
	}

	// add archetype
	world->archetypes[world->cur] = arch;
	world->cur += 1;
}

void ecs_free_world(world_t* world);

arch_t ecs_new_arch(int num_types)
{
	arch_t arch;
	arch.aspects = malloc(sizeof(arch_t) * num_types);
	arch.num = num_types;
	arch.max = CHUNK_SIZE;
	arch.cur = 0;
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
	for (int i = 0; i < arch->cur; i++)
	{
		if (strcmp(arch->aspects[i].type, type) == 0)
		{
			return &arch->aspects[i];
		}
	}

	return NULL;
}

void* ecs_get_components(arch_t* arch, char* type, size_t type_size)
{
	aspect_t* aspect = ecs_get_aspect(arch, type);

	return aspect->data;
}

int main(void)
{
	world_t* world = ecs_new_world();

	arch_t archetype1 = ecs_new_arch(2);

	archetype1.aspects[0] = ecs_new_aspect("pos", sizeof(pos_t));
	archetype1.aspects[1] = ecs_new_aspect("rot", sizeof(rot_t));

	ecs_world_add_arch(world, archetype1);

	pos_t* positions = ecs_get_components(&archetype1, "pos", sizeof(pos_t));
	rot_t* rotations = ecs_get_components(&archetype1, "rot", sizeof(rot_t));
	
}
