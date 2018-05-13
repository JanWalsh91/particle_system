kernel void init_particle_sphere(global Particle *P, size_t N) {
	size_t i = get_global_id(0);
	// float4 pt;
	// size_t seed = i;
	// seed = (seed * 0x5DEECE66DL + 0xBL) / seed;
	// pt.x = seed >> 16;
	// pt.y = seed >> 6;
	// pt.z = seed >> 8;
	// pt.w = 1;
	// pt = normalize(pt);
	float scale = 0.7;
	P[i].position = P[i].position * float4(4.0, 4.0, 4.0, 1);
	P[i].position = normalize(P[i].position) * float4(scale, scale, scale, 1);
	// printf("rand num: (%.2f, %.2f, %.2f)\n", pt.x, pt.y, pt.z);
}