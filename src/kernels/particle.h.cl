# pragma OPENCL EXTENSION cl_khr_fp16 : enable
typedef	struct	fp16_4_ {
	half x;
	half y;
	half z;
	half w;
}				fp16_4;

typedef struct	Particle2_ {
	fp16_4 position;
	fp16_4 speed;
}				Particle2;

typedef struct	Particle_ {
	float4 position;
	float4 speed;
}				Particle;