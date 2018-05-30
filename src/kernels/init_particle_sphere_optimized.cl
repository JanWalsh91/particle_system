kernel void init_particle_sphere_optimized(global Particle_optimized *P, uint N) {
	size_t i = get_global_id(0);

    float inc = M_PI_F * (3 - sqrt(5.0f));
    float off = 2.0f / N;
	float x, y, z, r, phi;
   
	y = i * off - 1 + (off /2);
	r = sqrt(1 - y * y);
	phi = i * inc;
	x = cos(phi) * r;
	z = sin(phi) * r;

	P[i].position = (float4)(x, y, z, 0.0f);

	float scale = 0.7f;
	P[i].position = normalize(P[i].position) * float4(scale, scale, scale, 1);
}