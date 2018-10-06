#ifndef LIM
#define LIM


template <typename T>
T lim(T x, T min, T max)
{
	if (x < min)
		return min;
	else if (x > max)
		return max;
	else
		return x;
};


#endif

