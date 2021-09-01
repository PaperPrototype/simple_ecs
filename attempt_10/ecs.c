#include "vec.c"

typedef struct float3 {
	float a, b, c;
} float3_t;

typedef float3_t pos3_t;
typedef float3_t vec3_t;
typedef float3_t rot3_t;
typedef float3_t vel3_t;

typedef struct float2
{
	float a, b;
} float2_t;

typedef float2_t pos2_t;
typedef float2_t rot2_t;
typedef float2_t vec2_t;
typedef float2_t uv_t;

typedef struct mesh
{
	pos3_t vertices;
	vec3_t normals;
	uv_t uvs;
} mesh_t;

const int CHUNK_SIZE = 32;

typedef struct aspect 
{
	char* type;
	void* data;
} aspect_t;

typedef struct arch
{
	aspect_t* aspects;
	int num;
	int cur;
} arch_t;

typedef struct world
{
	arch_t* archetypes;
	int cur;
} world_t;

world_t* ecs_new_world()
{
	printf("ecs new world\n");
	world_t* world = malloc(sizeof(world_t));
	world->archetypes = malloc(sizeof(arch_t) * CHUNK_SIZE);
	world->cur = 0;

	return world;
}

void ecs_world_add_arch(world_t* world, arch_t arch)
{
	printf("ecs world add arch\n");
	// if array is full
	if (world->cur >= CHUNK_SIZE)
	{
		printf("==== maximum archetypes reached! segfaults to follow! ====");
		/*
		printf("ecs world add arch/vec_grow archetypes array\n");
		// grow array (aka vec)
		vec_grow(world->archetypes, sizeof(arch_t), world->cur, CHUNK_SIZE);
		// increase max (aka, array size) since array has grown
		world->max += CHUNK_SIZE;
		*/
	}
	
	// add archetype
	world->archetypes[world->cur] = arch;
	world->cur += 1;

	printf("ecs world add arch/world info: cur = %i, max = %i\n", world->cur, CHUNK_SIZE);
}

void ecs_free_world(world_t* world)
{
	printf("ecs free world\n");
	printf("ecs free world/world info: cur = %i, max = %i\n", world->cur, CHUNK_SIZE);

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

	printf("aspect not found! returning NULL (void*)\n");
	return NULL;
}

void* ecs_get_components(arch_t* arch, char* type)
{
	printf("ecs get components\n");
	aspect_t* aspect = arch->aspects; // = ecs_get_aspect(arch, type);

	// foreach aspect in the archetype
	for (int i = 0; i < arch->num; i++)
	{
		// if aspect.type == wanted type
		if (strcmp(aspect[i].type, type) == 0)
		{
			// give back component array
			return aspect[i].data;
		}
	}

	printf("aspect and its components not found! returning NULL (void*)\n");
	return NULL;
}

int main(void)
{
	world_t* world = ecs_new_world();
	
	// Initializing new archetypes
	arch_t arch1 = ecs_new_arch(2);
	ecs_world_add_arch(world, arch1);
	arch1.aspects[0] = ecs_new_aspect("pos3", sizeof(pos3_t));
	arch1.aspects[1] = ecs_new_aspect("rot3", sizeof(rot3_t));
	
	arch_t arch2 = ecs_new_arch(3);
	ecs_world_add_arch(world, arch2);
	arch2.aspects[0] = ecs_new_aspect("pos3", sizeof(pos3_t));
	arch2.aspects[1] = ecs_new_aspect("mesh", sizeof(mesh_t));
	arch2.aspects[2] = ecs_new_aspect("rot3", sizeof(rot3_t));

	// TODO initialize specific entity component
	// ecs_set_entity_component(entity, "pos3", &(pos3_t){0.2, 3.3, 4.5});
		// archetype = entity.world->archetypes[entity.archetype_id]
		// aspect = get_aspect(archetype, "pos3");
		// aspect->data[entity.index_id] = &(pos3_t){0.2, 3.3, 4.5}

	// TODO add components to an entity
	// ecs_entity_add_component(&entity_id, new="pos3", &(pos3_t){0.2, 3.3, 4.5});
		// entity.world (pointer to its world so we don't have to pass world as paramter)
		// if NO archetype for entity type
			// make new archetype
		// foreach component at entity.archetype at entity.index
			// copy component data into new archetype or existing matching archetype

	// TODO get array of archetypes that match query
	// foreach archetype in world
		// if archetype matches query
			// add archetype to the array

	// TODO iterate over specific component in matching_archetypes_array
	// foreach archetype
		// positions = get_components(archetype, "pos3", iterator_index)
		// rotations = get_components(archetype, "rot3", iterator_index)
		// for int i = 0 to archetype.cur:
			// positions[i]
			// rotations[i]
	
	ecs_free_world(world);
}
