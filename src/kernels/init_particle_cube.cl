kernel void init_particle_cube(global Particle *P, size_t N, size_t n) {
	size_t i = get_global_id(0) * 8;

	// if (i >= N) {
	// 	return ;
	// }
	float4 init = (float4)(-0.5f, -0.5f, -0.5f, 1.0f);
	// float3 add;
	// add.x = (i % (n * n)) % n;
	// add.y = (i % (n * n)) / n;
	// add.z = i % (n * n);
	// add = add / (float)n;
	// P[i].position = init + add;
	P[i].position = init;
	// P[i].speed = (float3)(0.0f, 0.0f, 0.0f);
	// P[i].speed = (float3)(i * 0.0005f, .0f, .0f);
	// P[i].position[0] = 0;
	// P[i].position[1] = i * 0.01f;
	// P[i].position[2] = 0;
}