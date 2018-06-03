

// kernel void update_particle_optimized(global float4 *p) {
kernel void update_particle_optimized(global float4 *p, global float *f, int numForces, float deltaTime, float4 camUp, float4 camPos, float4 camDir) {
	size_t i = get_global_id(0);
	int y = 0;

	float4 forcePos = (float4)(f[y * 7 + 0], f[y * 7 + 1], f[y * 7 + 2], 1.0f);
	float4 pos = p[i];
	float4 relPos = pos - forcePos;
	float dist = length(relPos);

	float4 rotAxis = (float4)(0.0f, 100.0f, 0.0f, 0.0f);
	rotAxis.x = ((i + 1) % 2) + 1;
	rotAxis.y = ((i + 2) % 3) + 1;
	rotAxis.z = ((i + 3) % 4) + 1;
	
	// float4 camPos = (0.0f, 1.0f, 0.0f, 0.0f);
	// if (dot(camDir, relPos) < 0.1f && dot(camDir, relPos) > -0.1f) {
	// 	camDir = cross(camDir, (float4)(1.0f, 0.0f, 0.0f, 0.0f));
	// }
	rotAxis = camUp;

	
	// if (dot(rotAxis, relPos) > 0.8f || dot(rotAxis, relPos) < -0.8f) {
	// 	rotAxis = cross(rotAxis, relPos);
	// }
	rotAxis = normalize(rotAxis);
	float angle = 0.1f / dist;
	float cosA = cos(angle);
	float sinA = sin(angle);

	float4 newPos;
	// if (i == 0) {
	// 	printf("relPos: [%.2f, %.2f, %.2f]\n", relPos.x, relPos.y, relPos.z);
	// }
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

	// float4 dir = (forcePos - pos) * 0.001f;
	// if (length(dir) < 0.5) {
	// 	dir *= 0;
	// } 
	float4 dir = 0;

	p[i] = newPos + forcePos + dir;
	// p[i] = p[i] *  0.999f;
}
