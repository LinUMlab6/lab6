/*
Filip Wallin, Oskar Hallbom, Anders Ruberg
Grupp 116
linUM lab 6 
*/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "libpower.h"
#include "libcomponent.h"
#include "libresistance.h"

int main()
{
	float volt;
	int component_count;
	char conn[2];

	printf("Ange spänningskälla i V: ");
	scanf("%f", &volt);
  //printf("Du angav %.2f\n", volt);
	printf("Ange koppling[S | P]: ");
	scanf("%s", conn);
  //printf("Du angav %c\n", conn[0]);
	printf("Antal komponenter: ");
	scanf("%d", &component_count);
  //printf("Du angav %d\n", component_count);

  float *resistors = malloc(component_count * sizeof(float));
 
	for (int i = 0; i < component_count; i++)
	{
		printf("Ange värdet för komponent nr %d i ohm: ", i + 1);
    		scanf("%f", &resistors[i]);
	}
  //printf("Du angav");
  //for (int i = 0; i < component_count; i++)
  //{
  //  printf(" %.2f", resistors[i]);
  //}

  float res = calc_resistance(component_count, conn[0], resistors);


//Checks that the inputs are correct by looking if the returned resistance and input voltage are greater than 0;
	
  	if(volt >= 0 && res > 0){
		printf("\nErsättningsresistans: %.0f", res);


		printf("\nEffekt: %.2f", calc_power_r(volt, res));
 
	  float *E12_resistors = malloc(MAX_CALCULATED_E12_RESISTORS * sizeof(float));
	  const int num_E12_resistors = e_resistance(res, E12_resistors);
		printf("\nErsättningsresistanser i E12-serien kopplade i serie: ");
	  for (int i = 0; i < num_E12_resistors; i++)
	  {
	    printf(" %.0f", E12_resistors[i]);
	  }
	  printf("\n");

	  free(resistors);
	  free(E12_resistors);
	}
	
	else if(res == 0){
		printf("\nDen resulterande resistansen av inmatade komponenter är 0.\n");
		printf("Ersättningsresistanser kan därmed ej räknas ut.\n\n");
		return 0;
	}

	else{
		printf("Du har angivit ogiltiga värden, programmet avslutas.\n");
		return 0;
	}
}
