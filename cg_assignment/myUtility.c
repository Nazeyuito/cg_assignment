#include "myUtility.h"

float myfPow(float x, int y) {
	float p = 1;
	for (int i = 0; i < y; i++)
		p *= x;
	return p;
}

float dintancePoints(float *p1, float *p2, int elm) {
	float distance = 0;
	for (int i = 0; i < elm; i++)
		distance += myfPow((p1[i] - p2[i]), 2);
	return sqrtf(distance);
}