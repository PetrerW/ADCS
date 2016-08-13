#pragma once

#include "Mathematics.h"
#include <math.h>

struct faceTag {
	double v[3][6], cp[3][6];
	double s[6], diffuse[6], spec[6], absorpt[6];
}face;
