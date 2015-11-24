
/*
Oskar Hällbom
19881224-1936
Grupp 116
2015-11-24
linum labb 6
*/


#include <stdio.h>
 

float calc_resistance(int count, char conn, float *arrayIn)
{
	double sumResistance = 0;
	
	/*Checks the inparameters, count greater than 0, conn must be S or P.
	  Checks that the array is not a nullpointer*/
	if(count > 0 & conn != 'S' & conn!='P' & arrayIn != 0)
	{
		return -1;
	}
	
	/*Calculates resistance if the components are in parallel.*/
	if(conn == 'P')
	{
		
		int x;
		for (x = 0; x< count; x++)
		{
			if(arrayIn[x] == 0)
			{
				return 0;	
			}
			sumResistance += (1/arrayIn[x]);
		}
		return sumResistance;
	}

	/*Calculates resistance if the components are in a series*/
	else if(conn == 'S'){
		int x;
		for (x = 0; x< count; x++){
			sumResistance += arrayIn[x];
		}
		return sumResistance;
	}
	
	
	return -1;
}

int main()
{
	float my_array[] = {1, 23};
	

	char s;
	s = 'S';
		
	calc_resistance(2, s, my_array);	

	printf("Hello world\n");
	return 0;
}
