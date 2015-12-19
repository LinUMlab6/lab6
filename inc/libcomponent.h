#ifndef LIBCOMPONENT_H
#define LIBCOMPONENT_H

#include <math.h>
#include <memory.h>

// Number of values in the E12 resistor serie
#define E12_VALUES 12

// Max number of E12 replacement resistors calculated 
#define MAX_CALCULATED_E12_RESISTORS 3

// The granularity to use when comparing float numbers
#define GRANULARITY 0.01

#define FLOAT_EQUAL(x,y) \
do { \
 fabs((double)(x) - (y)) <= fabs((double)(GRANULARITY)) \
} while (0)

extern int e_resistance(float orig_resistance, float *res_array);
extern int power_of_ten(float num);
extern float find_nearest_E12(float resistance);

#endif
