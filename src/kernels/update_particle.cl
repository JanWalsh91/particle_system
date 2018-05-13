kernel void update_particle(global Particle *p/*, global Force *f, size_t forceCount*/) {
	size_t i = get_global_id(0);

	float3 forcePos = (float3)(.0f, .0f, 0.0f);
	float3 relPos = forcePos - p[i].position.xyz;

	p[i].speed.xyz = p[i].speed.xyz + normalize(relPos) * 0.00005f;

	p[i].position.xyz += p[i].speed.xyz;
}