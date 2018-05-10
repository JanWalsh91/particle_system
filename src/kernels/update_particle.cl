kernel void update_particle(global Particle * p) {
	size_t i = get_global_id(0);

	float3 forcePos = (float3)(0.0f, 0.0f, 0.0f);
	float3 relPos = forcePos - p[i].position;

	p[i].speed = p[i].speed + normalize(relPos) * 0.005f;

	p[i].position += p[i].speed;
}