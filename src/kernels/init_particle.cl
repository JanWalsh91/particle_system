kernel void init_particle(global Particle *P) {
	size_t i = get_global_id(0);

	// position
	P[i].position = (float3) (0.5f, 0.5f, 0.0f);
	// speed
	P[i].speed = (float3) (0.01f, 0.0f, 0.0f);
}