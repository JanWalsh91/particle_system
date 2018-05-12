kernel void init_particle_cube(global Particle *P, size_t N, size_t n) {
	size_t i = get_global_id(0);

	// float3 position = (float3)P[i];
	// if (i >= N) {
	// 	return ;
	// }
	float4 init = (float4)(-0.5f, -0.5f, -0.5f, .0f);
	float4 add;
	add.x = (i % (n * n)) % n;
	add.y = (i % (n * n)) / n;
	add.z = i / (n * n);
	add.w = 1;
	// printf("init_particle_cube (i = %d)\nSet add to (%.2f, %.2f, %.2f)\n", i, add.x, add.y, add.z);
	add = add / (float)n;
	P[i].position = init + add;
	P[i].speed = (float4)(0.0f, 0.0f, 0.0f, 0.0f);
	P[i].speed = (float4)(i * 0.00001f, .0f, .0f, .0f);
	// if (i == 0) {
	// 	P[i].position.xyz = (float3)(0.0f, 0.0f, .0f);
	// }
	printf("init_particle_cube (i = %d)\nSet pos to (%.2f, %.2f, %.2f)\n", i, P[i].position.x, P[i].position.y, P[i].position.z);
	// printf("init_particle_cube (i = %d)\nSet pos to (%.2f, %.2f, %.2f)\n", i, add.x, add.y, add.z);
	// printf("size of particle: %lu\n", sizeof(*P));
}
