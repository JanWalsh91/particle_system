kernel void init_particle_cube_optimized(global float4 *P, uint n) {
	size_t i = get_global_id(0);

	float4 init = (float4)(-0.5f, -0.5f, -0.5f, .0f);
	float4 add;
	add.x = (i % (n * n)) % n;
	add.y = (i % (n * n)) / n;
	add.z = i / (n * n);
	add.w = 1;
	add = add / ((float)n - 1);
	P[i] = init + add;
}
