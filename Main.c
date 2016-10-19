#include "earth2sunVector.h"
#include "Mathematics.h"
#include "FaceDiv.h"
#include <stdio.h>

int main()
{
	time_t T = time(NULL);
	matrix1x3 e2sun = earth2sunVector(T);
	printf("e2sun: %f %f %f", e2sun.m_data[0], e2sun.m_data[1], e2sun.m_data[2]);
	return 0;
}