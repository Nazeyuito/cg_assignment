#pragma once
#include <math.h>

//float mySqrt(float x,int ac);//return sqrt(x) (ac = accurate)
float myfPow(float px, int py);//return px^py (px=float)
float dintancePoints(float *p1, float *p2,int elm);//return distans point1 to point2 (elm = number of elements)
float flatPhi(float *p1, float *p2);//return arctan(p1,p2)  (2 dimension)
void changeFlatAxis(float *before, float *after, float axisPhi);//change axis (2 dimention)