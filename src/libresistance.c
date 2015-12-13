
/*
Oskar Hällbom
19881224-1936
Grupp 116
2015-11-24
linum labb 6
*/


#include <stdio.h>
 

float calc_resistance(int count, char conn, float *array)
{
	double sumResistance = 0;
	/*Checks that count is greater than 0.
	  Checks that the array is not a nullpointer*/
	if((count < 0) | (array == 0))
	{
		return -1;
	}
	/*Calculates resistance if the components are in parallel.*/
	if(conn == 'P')
	{
		int x;
		for (x = 0; x< count; x++)
		{
			if(array[x] == 0)
			{
				return 0;	
			}
			
	/*Checks if any of the components in the array are negative*/
			if(1/array[x] < 0){
				return -1;
			}
			sumResistance += (1/array[x]);

		}
		return sumResistance;
	}

	/*Calculates resistance if the components are in a series*/
	else if(conn == 'S'){
		int x;
		for (x = 0; x< count; x++){
			
			/*Checks if any of the components in the array are negative*/
			if(1/array[x] < 0){
				return -1;
			}

			sumResistance += array[x];
		}
		return sumResistance;
	}
	else{
	return -1;
	}

}
