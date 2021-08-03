#ifndef MODULO
#define MODULO


const float EPSILON_MODULO = 1e-10;

float modulo(float input, float min, float max)
{
	float denom = max - min;
	if (fabs(denom) < EPSILON_MODULO) {denom = EPSILON_MODULO;}
	
	double out = input - (max-min) * floor((input-min) / denom);
	if (out < min || out >= max) {out = min;}
	return out;
};

int modulo(int input, int min, int max)
{
	double out = min + (input-min) % (max-min);
	return out;
};


#endif

