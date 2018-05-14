
kernel void update_particle(global Particle *p, global float *f, int f_num) {
	float G = 6.67f * pow(10.0f, -11); 
	size_t i = get_global_id(0);
	size_t y = 0;
	float3 forcePos;
	float forceMass;
	float3 forceDir;
	float3 acc = (float3)(.0f, .0f, .0f);

	for (int y = 0; y < f_num; ++y) {
		forcePos = (float3)(f[y * 7], f[y * 7 + 1], f[y * 7 + 2]);
		forceMass = f[y * 7 + 6];
		forceDir = normalize(forcePos - p[i].position.xyz);
		// acc = acc + G * 1000 *  forceDir * forceMass / length(forcePos - p[i].position.xyz);
		acc = acc + forceDir * G * (forceMass / (pow(length(forcePos - p[i].position.xyz), 2)));
		// acc = acc + length(forcePos - p[i].position.xyz), 2)));
	}
	// forcePos = (float3)(.0f, .0f, .0f);
	// float3 relPos = forcePos - p[i].position.xyz;

	p[i].speed.xyz = p[i].speed.xyz + acc;

	p[i].position.xyz += p[i].speed.xyz;
}