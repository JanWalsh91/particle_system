kernel void update_particle(global Particle * p) {
	size_t i = get_global_id(0) * 8;

	float4 forcePos = (float4)(.0f, .0f, 0.0f, 0.0f);
	float4 relPos = forcePos - p[i].position;

	p[i].speed = p[i].speed + normalize(relPos) * 0.0005f;

	p[i].position += p[i].speed;
}