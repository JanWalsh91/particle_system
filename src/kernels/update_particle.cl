kernel void update_particle(Particle * p, Force * f) {
	size_t i = get_global_id(0);

	p[i].position = f->position;

	// while ( f != NULL ) {
		// p[i].speed += (f->mass / pow(f->position - p[i].position, 2));
		// ++f;
	// }
	// p[i].position += speed;
}