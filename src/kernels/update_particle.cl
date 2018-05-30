

kernel void update_particle(global Particle *p, global float *f, int numForces, float deltaTime) {
	for (int j = 0; j < 2; ++j) {
		size_t i = get_global_id(0) * 2 + j;
		float4 acc = (float4)(.0f, .0f, .0f, .0f);

		for (int y = 0; y < numForces; ++y) {
			acc += f[y * 7 + 6] * normalize((float4)(f[y * 7], f[y * 7 + 1], f[y * 7 + 2], 0.0f) - p[i].position);
		}
		p[i].speed = 0.999f * ( p[i].speed + acc * deltaTime * 60 );
		p[i].position += p[i].speed * deltaTime;
		// if (i == 50) {
		// 	printf("position: %.2f, %.2f, %.2f\n", p[i].position.x, p[i].position.y, p[i].position.z);
		// 	printf("force: %.2f, %.2f, %.2f\n", f[0], f[7 + 1], f[7 + 2]);
		// }
		// p[i].speed = 0.999f * ( p[i].speed + acc * deltaTime );
		// p[i].position += (p[i].speed) * deltaTime / 0.016f;
	}


	// for (int j = 0; j < 2; ++j) {
	// 	size_t i = get_global_id(0) * 2 + j;
	// 	// simple version (No speed)

	// 	// get rotation axe based on particle position, or index
	// 	int y = 0;
	// 	float4 gp = (float4)(f[y * 7], f[y * 7 + 1], f[y * 7 + 2], 0.0f);
	// 	float4 relPos = p[i].position - gp;
	// 	int i2 = i == 0 ? 1 : i - 1;
	// 	float4 c = cross(relPos, gp + (float4)(0.1f, 0.0f, 0.0f, 0.0f));
	// 	p[i].position += normalize(c) * 0.01f - length(relPos) * 0.001f * relPos;
	// }


	// printf("udpating");
	// for (int j = 0; j < 2; ++j) {
	// 	size_t i = (get_global_id(0) * 2 + j) * 3;
	// 	float3 acc = (float3)(.0f, .0f, .0f);

	// 	for (int y = 0; y < numForces; ++y) {
	// 		acc += f[y * 7 + 6] * normalize( (float3)(f[y * 7], f[y * 7 + 1], f[y * 7 + 2]) - p[i]);
	// 	}
	// 	p[i] = 0.999f * ( p[i + 1] + acc * deltaTime * 60.0f );
	// 	p[i + 1] += p[i + 1] * deltaTime;
	// 	// p[i].speed = 0.999f * ( p[i].speed + acc * deltaTime );
	// 	// p[i].position += (p[i].speed) * deltaTime / 0.016f;
	// }
}