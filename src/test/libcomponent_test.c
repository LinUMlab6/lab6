#include "CUnit/CUnit.h"
#include "CUnit/Basic.h"

#include "libcomponent.h"

#include <stdio.h>  // for printf

void find_nearest_E12_test(float resistance_value, float expected_value)
{
  float actual_value = find_nearest_E12(resistance_value);

  printf("\nfind_nearest_E12_test::resistance: %.3f, actual value: %.3f, expected value: %.3f\n", resistance_value, actual_value, expected_value);
  //CU_ASSERT_STRING_EQUAL(actual_s, expected_s);
  CU_ASSERT_DOUBLE_EQUAL(actual_value, expected_value, GRANULARITY);
}

void libcomponent_test(float resistance, float *expected_E12_values, int expected_count)
{
  float actual_E12_values[MAX_CALCULATED_E12_RESISTORS];
  float actual_value, expected_value;

  printf("\nlibcomponent_test::resistance: %.3f\n", resistance);

  int actual_count = e_resistance(resistance, actual_E12_values);
  printf("\tactual_count: %d, expected_count: %d\n", actual_count, expected_count);
  CU_ASSERT_EQUAL(actual_count, expected_count);

  for (int i = 0; i < expected_count; i++)
  {
    expected_value = expected_E12_values[i];
    actual_value = actual_E12_values[i];
    printf("\tindex: %d, actual value: %.3f, expected value: %.3f\n", i, actual_value, expected_value);
    CU_ASSERT_DOUBLE_EQUAL(actual_value, expected_value, GRANULARITY);
  }
}


/* Test Suite setup and cleanup functions: */

int init_suite(void) { return 0; }
int clean_suite(void) { return 0; }

/************* Test case functions ****************/

void libcomponent_tests(void) {
  CU_ASSERT_EQUAL(e_resistance(0, NULL), 0);
  CU_ASSERT_EQUAL(e_resistance(1398, NULL), 3);

  float E12_values_test1[MAX_CALCULATED_E12_RESISTORS] = {1200.0, 180.0, 18.0};
  libcomponent_test(1398.0, E12_values_test1, 3);
  
  float E12_values_test2[MAX_CALCULATED_E12_RESISTORS] = {1200.0, 0, 0};
  libcomponent_test(1200.0, E12_values_test2, 1);
  
  float E12_values_test3[MAX_CALCULATED_E12_RESISTORS] = {1000.0, 0, 0};
  libcomponent_test(1000.0, E12_values_test3, 1);
  
  float E12_values_test4[MAX_CALCULATED_E12_RESISTORS] = {120.0, 18.0, 1.8};
  libcomponent_test(139.80, E12_values_test4, 3);
  
  float E12_values_test5[MAX_CALCULATED_E12_RESISTORS] = {12.0, 1.80, 0};
  libcomponent_test(13.980, E12_values_test5, 2);
  
  float E12_values_test6[MAX_CALCULATED_E12_RESISTORS] = {1200.0, 270.0, 27.0};
  libcomponent_test(1498.0, E12_values_test6, 3);
}

void power_of_ten_tests(void) {
  CU_ASSERT_EQUAL(power_of_ten(1398), 3);
  CU_ASSERT_EQUAL(power_of_ten(139.8), 2);
  CU_ASSERT_EQUAL(power_of_ten(13.98), 1);
  CU_ASSERT_EQUAL(power_of_ten(1.398), 0);
}

void find_nearest_E12_tests(void) {
  float expected_value;
  float resistance;

  resistance = 1398;
  expected_value = 1200;
  find_nearest_E12_test(resistance, expected_value);

  resistance = 139.8;
  expected_value = 120.0;
  find_nearest_E12_test(resistance, expected_value);

  resistance = 13.98;
  expected_value = 12.00;
  find_nearest_E12_test(resistance, expected_value);

  resistance = 1.398;
  expected_value = 1.20;
  find_nearest_E12_test(resistance, expected_value);
  
  resistance = 1000.0;
  expected_value = 1000.0;
  find_nearest_E12_test(resistance, expected_value);
  
  resistance = 10.0;
  expected_value = 10.0;
  find_nearest_E12_test(resistance, expected_value);
  
  resistance = 1.0;
  expected_value = 1.0;
  find_nearest_E12_test(resistance, expected_value);

  resistance = 1200.0;
  expected_value = 1200.0;
  find_nearest_E12_test(resistance, expected_value);
  
  resistance = 0.0;
  expected_value = 0.0;
  find_nearest_E12_test(resistance, expected_value);
  
  resistance = 1.8;
  expected_value = 1.8;
  find_nearest_E12_test(resistance, expected_value);

}

/************* Test Runner Code goes here **************/

int main ( void )
{
   CU_pSuite pSuite = NULL;

   /* initialize the CUnit test registry */
   if ( CUE_SUCCESS != CU_initialize_registry() )
      return CU_get_error();

   /* add a suite to the registry */
   pSuite = CU_add_suite( "libcomponent_test_suite", init_suite, clean_suite );
   if ( NULL == pSuite ) {
      CU_cleanup_registry();
      return CU_get_error();
   }

   /* add the tests to the suite */
   if ((NULL == CU_add_test(pSuite, "libcomponent_tests", libcomponent_tests))
        || (NULL == CU_add_test(pSuite, "power_of_ten_tests", power_of_ten_tests))
        || (NULL == CU_add_test(pSuite, "find_nearest_E12_tests", find_nearest_E12_tests))) 
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // Run all tests using the basic interface
   CU_basic_set_mode(CU_BRM_VERBOSE);
   CU_basic_run_tests();
   printf("\n");
   CU_basic_show_failures(CU_get_failure_list());
   printf("\n\n");
   
   /* Clean up registry and return */
   CU_cleanup_registry();
   return CU_get_error();
}
