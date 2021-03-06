#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <stdlib.h>
#include "../headers/ComplexPoly.h"
#include "../headers/SimplePoly.h"

typedef int ** Poly2;
struct Polyonym2{
	Poly2 matrix;
	int dx;
	int dy;
};

void testpolyonymtryvalue(void);
void testcreatepolyonym2anddeletepoly2(void);
void testprintpolymatrix(void);
void testprintpoly(void);
void testprintpoly_byvar(void);
void testgetDegree2(void);
void testget_polymatrix2(void);
void testpolyonymtry_imag_value(void);

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

	if (CU_add_test(pSuite, "test of polyonymtryvalue()", testpolyonymtryvalue) == NULL) {
		CU_cleanup_registry();
		return CU_get_error();
	}
	if (CU_add_test(pSuite, "test of createpolyonym2() and deletepoly2()", testcreatepolyonym2anddeletepoly2) == NULL) {
		CU_cleanup_registry();
		return CU_get_error();
	}
	if (CU_add_test(pSuite, "test of printpolymatrix()", testprintpolymatrix) == NULL) {
		CU_cleanup_registry();
		return CU_get_error();
	}
	if (CU_add_test(pSuite, "test of printpoly()", testprintpoly) == NULL) {
		CU_cleanup_registry();
		return CU_get_error();
	}
	if (CU_add_test(pSuite, "test of printpoly_byvar()", testprintpoly_byvar) == NULL) {
		CU_cleanup_registry();
		return CU_get_error();
	}
	if (CU_add_test(pSuite, "test of getDegree2()", testgetDegree2) == NULL) {
		CU_cleanup_registry();
		return CU_get_error();
	}
	if (CU_add_test(pSuite, "test of get_polymatrix2()", testget_polymatrix2) == NULL) {
		CU_cleanup_registry();
		return CU_get_error();
	}
	if (CU_add_test(pSuite, "test of polyonymtry_imag_value()", testpolyonymtry_imag_value) == NULL) {
		CU_cleanup_registry();
		return CU_get_error();
	}

	CU_basic_set_mode(CU_BRM_VERBOSE);
	CU_basic_run_tests();
	CU_cleanup_registry();
	return CU_get_error();
}

void testpolyonymtryvalue(void)
{
	Polyonym2 poly;
	int ** matrix = NULL;
	matrix=malloc(sizeof(int *) * 2);
	matrix[0]=malloc(sizeof(int)*2);
	matrix[1]=malloc(sizeof(int)*2);
	matrix[0][0] = 0;
	matrix[0][1] = 1;
	matrix[1][0] = 2;
	matrix[1][1] = 3;
	poly.matrix = matrix;
	poly.dy = 1;
	poly.dx = 1;
	double dx = 2.0;
	double dy = 2.0;

	CU_ASSERT(polyonymtryvalue(&poly, dx, dy)>0.0);

	free(matrix[0]);
	free(matrix[1]);
	free(matrix);
}

void testcreatepolyonym2anddeletepoly2(void)
{
	char * function = "x^3-3yx+5";
	Polyonym2 * poly = NULL;
	int d = 3;

	createpolyonym2(function, &poly, d);
	deletepoly2(poly);
}

void testprintpolymatrix(void)
{
	Polyonym2 poly;
	int ** matrix = NULL;
	matrix=malloc(sizeof(int *) * 2);
	matrix[0]=malloc(sizeof(int)*2);
	matrix[1]=malloc(sizeof(int)*2);
	matrix[0][0] = 0;
	matrix[0][1] = 1;
	matrix[1][0] = 2;
	matrix[1][1] = 3;
	poly.matrix = matrix;
	poly.dy = 1;
	poly.dx = 1;

	printpolymatrix(&poly);

	free(matrix[0]);
	free(matrix[1]);
	free(matrix);
}

void testprintpoly(void)
{
	Polyonym2 poly;
	int ** matrix = NULL;
	matrix=malloc(sizeof(int *) * 2);
	matrix[0]=malloc(sizeof(int)*2);
	matrix[1]=malloc(sizeof(int)*2);
	matrix[0][0] = 0;
	matrix[0][1] = 1;
	matrix[1][0] = 2;
	matrix[1][1] = 3;
	poly.matrix = matrix;
	poly.dy = 1;
	poly.dx = 1;

	printpoly(&poly);

	free(matrix[0]);
	free(matrix[1]);
	free(matrix);
}

void testprintpoly_byvar(void)
{
	Polyonym2 poly;
	int ** matrix = NULL;
	matrix=malloc(sizeof(int *) * 2);
	matrix[0]=malloc(sizeof(int)*2);
	matrix[1]=malloc(sizeof(int)*2);
	matrix[0][0] = 0;
	matrix[0][1] = 1;
	matrix[1][0] = 2;
	matrix[1][1] = 3;
	poly.matrix = matrix;
	poly.dy = 1;
	poly.dx = 1;
	char v = 'y';

	printpoly_byvar(&poly, v);

	free(matrix[0]);
	free(matrix[1]);
	free(matrix);
}

void testgetDegree2(void)
{
	Polyonym2 poly;
	int ** matrix = NULL;
	matrix=malloc(sizeof(int *) * 2);
	matrix[0]=malloc(sizeof(int)*2);
	matrix[1]=malloc(sizeof(int)*2);
	matrix[0][0] = 0;
	matrix[0][1] = 1;
	matrix[1][0] = 2;
	matrix[1][1] = 3;
	poly.matrix = matrix;
	poly.dy = 1;
	poly.dx = 1;
	char v = 'x';
	
	CU_ASSERT(getDegree2(&poly, v)>0);

	free(matrix[0]);
	free(matrix[1]);
	free(matrix);
}


void testget_polymatrix2(void)
{
	Polyonym2 poly;
	int ** matrix = NULL;
	matrix=malloc(sizeof(int *) * 2);
	matrix[0]=malloc(sizeof(int)*2);
	matrix[1]=malloc(sizeof(int)*2);
	matrix[0][0] = 0;
	matrix[0][1] = 1;
	matrix[1][0] = 2;
	matrix[1][1] = 3;
	poly.matrix = matrix;
	poly.dy = 1;
	poly.dx = 1;
	int i = 1;
	int j = 1;
	
	CU_ASSERT(get_polymatrix2(&poly, i, j)>0);

	free(matrix[0]);
	free(matrix[1]);
	free(matrix);
}

void testpolyonymtry_imag_value(void)
{
	Polyonym2 poly;
	int ** matrix = NULL;
	matrix=malloc(sizeof(int *) * 2);
	matrix[0]=malloc(sizeof(int)*2);
	matrix[1]=malloc(sizeof(int)*2);
	matrix[0][0] = 0;
	matrix[0][1] = 1;
	matrix[1][0] = 2;
	matrix[1][1] = 3;
	poly.matrix = matrix;
	poly.dy = 1;
	poly.dx = 1;
	double realx = 2.0;
	double imagx = 2.0;
	double realy = 2.0;
	double imagy = 2.0;
	double R;
	double im;
	
	polyonymtry_imag_value(&poly, realx, imagx, realy, imagy, &R, &im);

	free(matrix[0]);
	free(matrix[1]);
	free(matrix);
}
