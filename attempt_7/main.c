#include "ecs.c"

int main(void)
{
	// player archetype
	archetype_t* archetype = new_archetype(3);
	archetype->aspects[0] = set_aspect(sizeof(pos_t), "pos", MAX_COMPONENTS);
	archetype->aspects[1] = set_aspect(sizeof(int), "int", MAX_COMPONENTS);
	archetype->aspects[2] = set_aspect(sizeof(vel_t), "vel", MAX_COMPONENTS);

	// SET COMPONENT DATA
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

	// enemies archetype
	archetype_t* archetype1 = new_archetype(2);
	archetype1->aspects[0] = set_aspect(sizeof(pos_t), "pos", MAX_COMPONENTS);
	archetype1->aspects[1] = set_aspect(sizeof(vel_t), "vel", MAX_COMPONENTS);

	// set component data.
	for (int i = 0; i < MAX_COMPONENTS; i++)
	{
		// set positions
		pos_t* positions = archetype1->aspects[0].data;
		positions[i] = (pos_t){2.4, 14, 0.21};

		// set velocities
		vel_t* velocities = archetype1->aspects[1].data;
		velocities[i] = (vel_t){4, 4, 4};
	}

	// debug
	print_positions_system(archetype1->aspects[0].data, MAX_COMPONENTS);

	// increase by velocities
	add_velocities_system(archetype1->aspects[0].data, archetype1->aspects[1].data, MAX_COMPONENTS);

	// debug
	print_positions_system(archetype1->aspects[0].data, MAX_COMPONENTS);

	// THESE ARE REDUNDANT and we need a way to query for archetypes and get back desired component arrays
	// debug
	print_positions_system(archetype->aspects[0].data, MAX_COMPONENTS);

	// increase by velocities
	add_velocities_system(archetype->aspects[0].data, archetype->aspects[2].data, MAX_COMPONENTS);

	// debug
	print_positions_system(archetype->aspects[0].data, MAX_COMPONENTS);
	

	free_archetype(archetype);
	free_archetype(archetype1);
}