
kernel void init_particle_cube2(global float *P) {
	size_t i = get_global_id(0) * 6;

	P[i] = 0.1f * (float)i;
	P[i + 1] = 0.0f;
	P[i + 2] = 0.0f;

	printf("init_particle_cube2 with i = %d\nSet pos to (%p, %p, %p) spd (%p, %p, %p)\n", i, &P[i], &P[i + 1], &P[i + 2], &P[i + 3], &P[i + 4], &P[i + 5]);
}