kernel void init_particles(global float *P) {
	size_t i = get_global_id(0);

	P[i] = 0.5f;
	P[i + 1] = 0.5f;
	P[i + 2] = 0.5f;
}