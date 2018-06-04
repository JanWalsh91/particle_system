kernel void update_particle(global Particle *p, global float *f, int numForces, float deltaTime) {
	for (int j = 0; j < 2; ++j) {
		size_t i = get_global_id(0) * 2 + j;

		float4 acc = (float4)(.0f, .0f, .0f, .0f);
		
		for (int y = 0; y < numForces; ++y) {
			acc += f[y * 7 + 6] * normalize((float4)(f[y * 7], f[y * 7 + 1], f[y * 7 + 2], 0.0f) - p[i].position);
		}

		p[i].speed = 0.999f * ( p[i].speed + acc * deltaTime * 60 );
		p[i].position += p[i].speed * deltaTime;
	}
}