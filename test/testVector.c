#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <stdlib.h>
#include "../headers/Vector.h"
#include "../headers/SimplePoly.h"
#include "../headers/ComplexPoly.h"

typedef double * Poly;
struct Polyonym{
	Poly matrix;
	char var;
	int d;
};

struct Vector{
	Polyonym * matrix;
	int dim;
};

void testcreateInputVectoranddeleteVector(void);
void testcreateInputVectoranddeleteVector_static(void);
void testcreateZeroVector(void);
void testcreateStableVector(void);
void testprintVector(void);
void testgetVectordim(void);

static FILE* temp_file = NULL;

int init_suite1(void)
{
   if (NULL == (temp_file = fopen("temp.txt", "w+"))) {
      return -1;
   }
   else {
      return 0;
   }
}

int clean_suite1(void)
{
   if (0 != fclose(temp_file)) {
      return -1;
   }
   else {
      temp_file = NULL;
      return 0;
   }
}

int main()
{
	CU_pSuite pSuite = NULL;
	if (CU_initialize_registry() != CUE_SUCCESS) {
		return CU_get_error();
	}
	pSuite = CU_add_suite("Suite_1", init_suite1, clean_suite1);
	if (pSuite == NULL) {
		CU_cleanup_registry();
		return CU_get_error();
	}
	
	if (CU_add_test(pSuite, "test of createInputVector() and deleteVector()", testcreateInputVectoranddeleteVector) == NULL) {
		CU_cleanup_registry();
		return CU_get_error();
	}
	if (CU_add_test(pSuite, "test of createInputVector() and deleteVector_static()", testcreateInputVectoranddeleteVector_static) == NULL) {
		CU_cleanup_registry();
		return CU_get_error();
	}
	if (CU_add_test(pSuite, "test of createZeroVector()", testcreateZeroVector) == NULL) {
		CU_cleanup_registry();
		return CU_get_error();
	}
	if (CU_add_test(pSuite, "test of createStableVector()", testcreateStableVector) == NULL) {
		CU_cleanup_registry();
		return CU_get_error();
	}
	if (CU_add_test(pSuite, "test of printVector()", testprintVector) == NULL) {
		CU_cleanup_registry();
		return CU_get_error();
	}
	if (CU_add_test(pSuite, "test of getVectordim()", testgetVectordim) == NULL) {
		CU_cleanup_registry();
		return CU_get_error();
	}

	CU_basic_set_mode(CU_BRM_VERBOSE);
	CU_basic_run_tests();
	CU_cleanup_registry();
	return CU_get_error();
}

void testcreateInputVectoranddeleteVector(void)
{
	Vector * s = NULL;
	
	createInputVector(&s);
	deleteVector(s);
}

void testcreateInputVectoranddeleteVector_static(void)
{
	Vector * s = NULL;
	
	createInputVector(&s);
	deleteVector_static(s);
}

void testcreateZeroVector(void)
{
	Vector * s = NULL;
	int dim = 1;
	char v = 'y';
	
	createZeroVector(&s, dim, v);
}

void testcreateStableVector(void)
{
	Vector * s = NULL;
	double * input = NULL;
	input=malloc(sizeof(double)*2);
	input[0] = 1.0;
	input[1] = 2.0;
	int dim = 0;
	char c = 'y';
	
	createStableVector(s, input, dim, c);
}

void testprintVector(void)
{
	Polyonym poly;
	double * matrix = NULL;
	matrix=malloc(sizeof(double)*1);
	matrix[0] = 0.0;
	poly.matrix=matrix;
	poly.var = 'y';
	poly.d = 1;
	Vector vector;
	vector.matrix = &poly;
	vector.dim = 1;

	printVector(&vector);

	free(matrix);
}

void testgetVectordim(void)
{
	Polyonym poly;
	double * matrix = NULL;
	matrix=malloc(sizeof(double)*1);
	matrix[0] = 0.0;
	poly.matrix=matrix;
	poly.var = 'y';
	poly.d = 1;
	Vector vector;
	vector.matrix = &poly;
	vector.dim = 1;
	
	CU_ASSERT(getVectordim(&vector)>=0);

	free(matrix);
}
