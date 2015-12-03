#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <stdlib.h>
#include "../headers/SimplePoly.h"

typedef int ** Poly2;
struct Polyonym2{
	Poly2 matrix;
	int dx;
	int dy;
};

typedef double * Poly;
struct Polyonym{
	Poly matrix;
	char var;
	int d;
};

void testcreate1polyonymanddelete1polyonym(void);
void testcreate1polyonym_oneanddelete1polyonym(void);
void testcreate1polyonym_imaganddelete1polyonym(void);
void testcreate1polyonymanddelete1matrix(void);
void testcopy1polyonym(void);
void testadd1polyonyms(void);
void testmultiply1polyonym(void);
void testmult_polyonym1polyonym(void);
void testprint1polyonym(void);
void testprint1polyonym_double(void);
void testget1Degree(void);
void testget1NumByDegree(void);
void testget1var(void);
void testchange1polyonym(void);
void testget_polyonymvalue(void);

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
	
	if (CU_add_test(pSuite, "test of create1polyonym() and delete1polyonym()", testcreate1polyonymanddelete1polyonym) == NULL) {
		CU_cleanup_registry();
		return CU_get_error();
	}
	if (CU_add_test(pSuite, "test of create1polyonym_one() and delete1polyonym()", testcreate1polyonym_oneanddelete1polyonym) == NULL) {
		CU_cleanup_registry();
		return CU_get_error();
	}
	if (CU_add_test(pSuite, "test of create1polyonym_imag() and delete1polyonym()", testcreate1polyonym_imaganddelete1polyonym) == NULL) {
		CU_cleanup_registry();
		return CU_get_error();
	}
	if (CU_add_test(pSuite, "test of create1polyonym() and delete1matrix()", testcreate1polyonymanddelete1matrix) == NULL) {
		CU_cleanup_registry();
		return CU_get_error();
	}
	if (CU_add_test(pSuite, "test of copy1polyonym()", testcopy1polyonym) == NULL) {
		CU_cleanup_registry();
		return CU_get_error();
	}
	if (CU_add_test(pSuite, "test of add1polyonyms()", testadd1polyonyms) == NULL) {
		CU_cleanup_registry();
		return CU_get_error();
	}
	if (CU_add_test(pSuite, "test of multiply1polyonym()", testmultiply1polyonym) == NULL) {
		CU_cleanup_registry();
		return CU_get_error();
	}
	if (CU_add_test(pSuite, "test of mult_polyonym1polyonym()", testmult_polyonym1polyonym) == NULL) {
		CU_cleanup_registry();
		return CU_get_error();
	}
	if (CU_add_test(pSuite, "test of print1polyonym()", testprint1polyonym) == NULL) {
		CU_cleanup_registry();
		return CU_get_error();
	}
	if (CU_add_test(pSuite, "test of print1polyonym_double()", testprint1polyonym_double) == NULL) {
		CU_cleanup_registry();
		return CU_get_error();
	}
	if (CU_add_test(pSuite, "test of get1Degree()", testget1Degree) == NULL) {
		CU_cleanup_registry();
		return CU_get_error();
	}
	if (CU_add_test(pSuite, "test of get1NumByDegree()", testget1NumByDegree) == NULL) {
		CU_cleanup_registry();
		return CU_get_error();
	}
	if (CU_add_test(pSuite, "test of get1var()", testget1var) == NULL) {
		CU_cleanup_registry();
		return CU_get_error();
	}
	if (CU_add_test(pSuite, "test of change1polyonym()", testchange1polyonym) == NULL) {
		CU_cleanup_registry();
		return CU_get_error();
	}
	if (CU_add_test(pSuite, "test of get_polyonymvalue()", testget_polyonymvalue) == NULL) {
		CU_cleanup_registry();
		return CU_get_error();
	}

	CU_basic_set_mode(CU_BRM_VERBOSE);
	CU_basic_run_tests();
	CU_cleanup_registry();
	return CU_get_error();
}

void testcreate1polyonymanddelete1polyonym(void)
{
	Polyonym2 poly2;
	int ** matrix = NULL;
	matrix=malloc(sizeof(int*)*2);
	matrix[0]=malloc(sizeof(int)*2);
	matrix[1]=malloc(sizeof(int)*2);
	matrix[0][0] = 0;
	matrix[0][1] = 1;
	matrix[1][0] = 2;
	matrix[1][1] = 3;
	poly2.matrix = matrix;
	poly2.dy = 2;
	poly2.dx = 2;
	Polyonym * poly=malloc(sizeof(struct Polyonym));
	char v = 'x';
	int point = 1;

	create1polyonym(&poly2, poly, v, point);

	delete1polyonym(poly);

	free(matrix[0]);
	free(matrix[1]);
	free(matrix);
}

void testcreate1polyonym_oneanddelete1polyonym(void)
{
	Polyonym * poly;
	char v = 'y';

	create1polyonym_one(&poly,  v);
	delete1polyonym(poly);
}

void testcreate1polyonym_imaganddelete1polyonym(void)
{
	Polyonym * poly;
	double real = 2.0;
	double imag = 2.0;

	create1polyonym_imag(&poly,  real, imag);
	delete1polyonym(poly);
}

void testcreate1polyonymanddelete1matrix(void)
{
	Polyonym2 poly2;
	int ** matrix = NULL;
	matrix=malloc(sizeof(int*)*2);
	matrix[0]=malloc(sizeof(int)*2);
	matrix[1]=malloc(sizeof(int)*2);
	matrix[0][0] = 0;
	matrix[0][1] = 1;
	matrix[1][0] = 2;
	matrix[1][1] = 3;
	poly2.matrix = matrix;
	poly2.dy = 2;
	poly2.dx = 2;
	Polyonym * poly=malloc(sizeof(struct Polyonym));
	char v = 'x';
	int point = 1;

	create1polyonym(&poly2, poly, v, point);
	delete1matrix(poly);

	free(matrix[0]);
	free(matrix[1]);
	free(matrix);
}

void testcopy1polyonym(void)
{
	Polyonym source;
	double * matrix = NULL;
	matrix=malloc(sizeof(double)*2);
	matrix[0] = 0.0;
	matrix[1] = 0.0;
	source.matrix=matrix;
	source.var = 'y';
	source.d = 2;
	Polyonym * target=malloc(sizeof(struct Polyonym));

	copy1polyonym(target, &source);

	free(matrix);
}

void testadd1polyonyms(void)
{
	Polyonym poly1;
	double * matrix1 = NULL;
	matrix1=malloc(sizeof(double)*2);
	matrix1[0] = 0.0;
	matrix1[1] = 0.0;
	poly1.matrix=matrix1;
	poly1.var = 'y';
	poly1.d = 2;
	Polyonym poly2;
	double * matrix2 = NULL;
	matrix2=malloc(sizeof(double)*2);
	matrix2[0] = 0.0;
	matrix2[1] = 0.0;
	poly2.matrix=matrix2;
	poly2.var = 'y';
	poly2.d = 2;
	Polyonym * target=malloc(sizeof(struct Polyonym));

	add1polyonyms(target, &poly1, &poly2);

	free(matrix1);
	free(matrix2);
}

void testmultiply1polyonym(void)
{
	Polyonym poly;
	double * matrix = NULL;
	matrix=malloc(sizeof(double)*2);
	matrix[0] = 0.0;
	matrix[1] = 0.0;
	poly.matrix=matrix;
	poly.var = 'y';
	poly.d = 2;
	Polyonym * target=malloc(sizeof(struct Polyonym));
	int m = 3;

	multiply1polyonym(target, &poly, m);

	free(matrix);
}

void testmult_polyonym1polyonym(void)
{
	Polyonym poly1;
	double * matrix1 = NULL;
	matrix1=malloc(sizeof(double)*2);
	matrix1[0] = 0.0;
	matrix1[1] = 0.0;
	poly1.matrix=matrix1;
	poly1.var = 'y';
	poly1.d = 2;
	Polyonym poly2;
	double * matrix2 = NULL;
	matrix2=malloc(sizeof(double)*2);
	matrix2[0] = 0.0;
	matrix2[1] = 0.0;
	poly2.matrix=matrix2;
	poly2.var = 'y';
	poly2.d = 2;
	Polyonym * target=malloc(sizeof(struct Polyonym));
	int m = 3;

	mult_polyonym1polyonym(&target, &poly1, &poly2);

	free(matrix1);
	free(matrix2);
}

void testprint1polyonym(void)
{
	Polyonym poly;
	double * matrix = NULL;
	matrix=malloc(sizeof(double)*2);
	matrix[0] = 0.0;
	matrix[1] = 0.0;
	poly.matrix=matrix;
	poly.var = 'y';
	poly.d = 2;

	print1polyonym(&poly);

	free(matrix);
}

void testprint1polyonym_double(void)
{
	Polyonym poly;
	double * matrix = NULL;
	matrix=malloc(sizeof(double)*2);
	matrix[0] = 0.0;
	matrix[1] = 0.0;
	poly.matrix=matrix;
	poly.var = 'y';
	poly.d = 2;

	print1polyonym_double(&poly);

	free(matrix);
}

void testget1Degree(void)
{
	Polyonym poly;
	double * matrix = NULL;
	matrix=malloc(sizeof(double)*2);
	matrix[0] = 0.0;
	matrix[1] = 0.0;
	poly.matrix=matrix;
	poly.var = 'y';
	poly.d = 2;
	
	CU_ASSERT(get1Degree(&poly)>0);

	free(matrix);
}

void testget1NumByDegree(void)
{
	Polyonym poly;
	double * matrix = NULL;
	matrix=malloc(sizeof(double)*2);
	matrix[0] = 0.0;
	matrix[1] = 0.0;
	poly.matrix=matrix;
	poly.var = 'y';
	poly.d = 2;
	int targetDeg = 1;
	
	CU_ASSERT(get1NumByDegree(&poly, targetDeg)>0);

	free(matrix);
}

void testget1var(void)
{
	Polyonym poly;
	double * matrix = NULL;
	matrix=malloc(sizeof(double)*2);
	matrix[0] = 0.0;
	matrix[1] = 0.0;
	poly.matrix=matrix;
	poly.var = 'y';
	poly.d = 2;
	
	CU_ASSERT(get1var(&poly)=='y');

	free(matrix);
}

void testchange1polyonym(void)
{
	Polyonym poly;
	double * matrix = NULL;
	matrix=malloc(sizeof(double)*2);
	matrix[0] = 0.0;
	matrix[1] = 0.0;
	poly.matrix=matrix;
	poly.var = 'y';
	poly.d = 2;
	int grade = 2;
	double in = 2.0;
	
	change1polyonym(&poly, grade, in);

	free(matrix);
}

void testget_polyonymvalue(void)
{
	Polyonym poly;
	double * matrix = NULL;
	matrix=malloc(sizeof(double)*2);
	matrix[0] = 0.0;
	matrix[1] = 0.0;
	poly.matrix=matrix;
	poly.var = 'y';
	poly.d = 2;
	double v = 1.0;
	
	CU_ASSERT(get_polyonymvalue(&poly, v)>=0.0);

	free(matrix);
}
