

kernel void update_particle_optimized(global Particle_optimized *p, global float *f, int numForces, float deltaTime, float4 camUp, float4 camPos) {
	for (int j = 0; j < 2; ++j) {
		size_t i = get_global_id(0) * 2 + j;
		int y = 0;

		float4 forcePos = (float4)(f[y * 7 + 0], f[y * 7 + 1], f[y * 7 + 1], 1.0f);
		float4 pos = p[i].position;
		float4 relPos = pos - forcePos;
		float dist = length(relPos);
		float4 rotAxis = (float4)(0.0f, 100.0f, 0.0f, 0.0f);
		rotAxis.x = (i % 90);
		rotAxis.y = (i % 80);
		rotAxis.z = (i % 70);
		rotAxis = normalize(rotAxis);
		float angle = 0.1f / dist;
		float cosA = cos(angle);
		float sinA = sin(angle);

		float4 newPos;

		newPos.x =
			relPos.x * (cosA + rotAxis.x * rotAxis.x * (1 - cosA)) +
			relPos.y * (rotAxis.x * rotAxis.y * (1 - cosA) - rotAxis.z * sinA) +
			relPos.z * (rotAxis.x * rotAxis.z * (1 - cosA) + rotAxis.y * sinA);

		newPos.y = 
			relPos.x * (rotAxis.y * rotAxis.x * (1 - cosA) + rotAxis.z * sinA) +
			relPos.y * (cosA + rotAxis.y * rotAxis.y * (1 - cosA)) +
			relPos.z * (rotAxis.y * rotAxis.z * (1 - cosA) - rotAxis.x * sinA);

		newPos.z = 
			relPos.x * (rotAxis.z * rotAxis.x * (1 - cosA) - rotAxis.y * sinA) +
			relPos.y * (rotAxis.z * rotAxis.y * (1 - cosA) + rotAxis.x * sinA) +
			relPos.z * (cosA + rotAxis.z * rotAxis.z * (1 - cosA));
		
		newPos.w = 0.0f;

		float4 dir = (forcePos - pos) * 0.001f;

		p[i].position = newPos + forcePos + dir;
	}
}
