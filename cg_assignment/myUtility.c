#include "myUtility.h"

float myfPow(float px, int py) {
	float p = 1;
	for (int i = 0; i < py; i++)
		p *= px;
	return p;
}

float dintancePoints(float *p1, float *p2, int elm) {
	float distance = 0;
	for (int i = 0; i < elm; i++)
		distance += myfPow((p1[i] - p2[i]), 2);
	return sqrtf(distance);
}

float flatPhi(float *p1, float *p2) {
	return atan2f((p2[0] - p1[0]), (p2[1] - p1[1]));
}

void changeFlatAxis(float *before, float *after, float axisPhi) {
	after[0] = before[0] * cos(axisPhi) + before[1] * sin(axisPhi);
	after[1] = before[0] * sin(axisPhi) + before[1] * cos(axisPhi);
	return;
}