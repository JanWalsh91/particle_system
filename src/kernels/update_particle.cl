
kernel void update_particle(global Particle *p, global float *f, int f_num) {
	float G = 6.67f * pow(10.0f, -11); 
	size_t i = get_global_id(0);
	size_t y = 0;
	float3 forcePos;
	float forceMass;
	float3 forceDir;
	float3 acc = (float3)(.0f, .0f, .0f);
	float3 dist;

	for (int y = 0; y < f_num; ++y) {
		forcePos = (float3)(f[y * 7], f[y * 7 + 1], f[y * 7 + 2]);
		forceMass = f[y * 7 + 6];
		forceDir = normalize(forcePos - p[i].position.xyz);
		dist = max(0.9f, length(forcePos - p[i].position.xyz));
		dist = min(dist, 5.5f);
		// acc = acc + forceDir * G * (forceMass / (pow(dist, 2)));
		
		// acc += acc + G * forceMass * forceDir / dist;
		
		// acc += acc + G * forceMass * forceDir;

		acc += acc + G * forceMass * forceDir;
	}
	// forcePos = (float3)(.0f, .0f, .0f);
	// float3 relPos = forcePos - p[i].position.xyz;

	p[i].speed.xyz = p[i].speed.xyz + acc;
	p[i].speed.xyz = 0.999f * p[i].speed.xyz;

	p[i].position.xyz += p[i].speed.xyz;
}