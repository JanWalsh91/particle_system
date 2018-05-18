
kernel void update_particle(global Particle *p, global float *f, int numForces, float deltaTime) {
	for (int j = 0; j < 2; ++j) {
		size_t i = get_global_id(0) * 2 + j;
		float3 acc = (float3)(.0f, .0f, .0f);

		for (int y = 0; y < numForces; ++y) {
			acc += f[y * 7 + 6] * normalize((float3)(f[y * 7], f[y * 7 + 1], f[y * 7 + 2]) - p[i].position.xyz);
		}
		p[i].speed.xyz = 0.999f * ( p[i].speed.xyz + acc );
		p[i].position.xyz += p[i].speed.xyz * deltaTime;
	}


	// simple version (No speed)
	// int y = 0;
	// float4 gp = (float4)(f[y * 7], f[y * 7 + 1], f[y * 7 + 2], 0.0f);
	// float4 relPos = p[i].position - gp;
	// int i2 = i == 0 ? 1 : i - 1;
	// float4 c = cross(relPos, p[i2].position);
	// p[i].position += normalize(c) * 0.01f - length(relPos) * 0.001f * relPos;
}