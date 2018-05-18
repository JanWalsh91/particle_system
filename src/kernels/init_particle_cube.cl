kernel void init_particle_cube(global Particle *P, uint N, uint n) {
	size_t i = get_global_id(0);


	float4 init = (float4)(-0.5f, -0.5f, -0.5f, .0f);
	float4 add;
	add.x = (i % (n * n)) % n;
	add.y = (i % (n * n)) / n;
	add.z = i / (n * n);
	add.w = 1;
	add = add / ((float)n - 1);
	P[i].position = init + add;
	P[i].speed = (float4)(.0f, .0f, .0f, .0f);
	if (i == 20) {
		printf("P[i].position: {%.2f, %.2f, %.2f}\nN: %u\nn: %u\n", P[i].position.x, P[i].position.y, P[i].position.z, N, n);
	}
}
