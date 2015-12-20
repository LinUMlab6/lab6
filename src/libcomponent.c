#include "libcomponent.h"


static float nominell_E12[E12_VALUES] = {1.00, 1.20, 1.50, 1.80, 2.20, 2.70,
                                         3.30, 3.90, 4.70, 5.60, 6.80, 8.20};

int e_resistance(float orig_resistance, float *res_array)
{
  int count = 0;
  float resistance_left = orig_resistance;
  float E12_value;
  int decade = power_of_ten(orig_resistance);

  while ((count < MAX_CALCULATED_E12_RESISTORS) && (resistance_left > 1.0))
  {
    E12_value = find_nearest_E12(resistance_left, &decade);
    if (res_array != NULL)
      res_array[count] = E12_value;

    resistance_left -= E12_value;
    count++;
  }

  return count;
}

float find_nearest_E12(float resistance, int *decade)
{
  // Assume minimum resistant value given is 1.0 Ohm
  if (resistance < 1.0)
    return 0;
  
  float E12_value;
  if ((int)log10(resistance) < *decade)
    (*decade)--;

  // Loop through E12 values, starting with the highest
  for (int i = E12_VALUES - 1; i >= 0; i--)
  {
    // Calulcate corresponding E12 value for this decade
    E12_value = nominell_E12[i] * pow(10, (double)*decade);
    if ((fabs((double)(E12_value) - (resistance)) <= fabs((double)(GRANULARITY)))
        || (E12_value < resistance))
    {
      break;
    }
  }
  return E12_value;
}

int power_of_ten(float num)
{
  int power_of_ten = 0;
  if (num > 1.0)
  {
    double log_num = log10(num);
    power_of_ten = (int)log_num;
    // According to the given tests in lab12 it's preferable to use E12 values from a lower decade
    // if the given resistance is 10, 100, 1000 etc.
    if (fabs((double)(log_num - (double)power_of_ten)) <= fabs((double)(GRANULARITY)))
      power_of_ten--;
  }
  return power_of_ten;
}
