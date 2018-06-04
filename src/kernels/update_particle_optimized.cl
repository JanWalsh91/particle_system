
kernel void update_particle_optimized(global float4 *p, global float *f, int numForces, float deltaTime, float4 camUp, float4 camPos, float4 camDir) {
	size_t i = get_global_id(0);

	for (int y = 0; y < numForces; ++y) {
		float4 forcePos = (float4)(f[y * 7 + 0], f[y * 7 + 1], f[y * 7 + 2], 1.0f);
		float4 pos = p[i];
		float4 relPos = pos - forcePos;
		float dist = length(relPos);

		float4 rotAxis;
		rotAxis.x = (i % 1600);
		rotAxis.y = (i % -2300) * rotAxis.x;
		rotAxis.z = (int)(-(rotAxis.x * relPos.x + rotAxis.y * relPos.y) / relPos.z);
		rotAxis.w = 0.0f;

		rotAxis = normalize(rotAxis);
		float angle = 0.01f / (dist * dist);
		angle = min(1.0f, angle);
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

		float4 dir = (forcePos - pos) * 0.01f;
		if (distance(forcePos, pos) < 0.005f * (i % 100)) {
			dir *= -1;
		} 

		p[i] = newPos + forcePos + dir;
	}
}
