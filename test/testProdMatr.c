#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <stdlib.h>
#include "../headers/ProdMatr.h"
#include "../headers/Sylvester.h"
#include "../headers/SimplePoly.h"
#include "../headers/Routines.h"

typedef double * Poly;
struct Polyonym{
	Poly matrix;
	char var;
	int d;
};

struct Sylvester{
	Polyonym ** matrix;
	int dim;
	char hidden;
	int degree;
};

struct ProductMatrices{
	double *** matrix;
	int dim;
	char hidden;
	int degree;
	double k;
};

void testcreateProdMatranddestroyProdMatr(void);
void testprintProdMatr(void);
void testchangeofvar3(void);
void testget_Productdim(void);
void testget_Productk(void);
void testget_Producthidden(void);
void testget_Productdegree(void);

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
	
	if (CU_add_test(pSuite, "test of createProdMatr() and destroyProdMatr()", testcreateProdMatranddestroyProdMatr) == NULL) {
		CU_cleanup_registry();
		return CU_get_error();
	}
	if (CU_add_test(pSuite, "test of printProdMatr()", testprintProdMatr) == NULL) {
		CU_cleanup_registry();
		return CU_get_error();
	}
	if (CU_add_test(pSuite, "test of changeofvar3()", testchangeofvar3) == NULL) {
		CU_cleanup_registry();
		return CU_get_error();
	}
	if (CU_add_test(pSuite, "test of get_Productdim()", testget_Productdim) == NULL) {
		CU_cleanup_registry();
		return CU_get_error();
	}
	if (CU_add_test(pSuite, "test of get_Productk()", testget_Productk) == NULL) {
		CU_cleanup_registry();
		return CU_get_error();
	}
	if (CU_add_test(pSuite, "test of get_Producthidden()", testget_Producthidden) == NULL) {
		CU_cleanup_registry();
		return CU_get_error();
	}
	if (CU_add_test(pSuite, "test of get_Productdegree()", testget_Productdegree) == NULL) {
		CU_cleanup_registry();
		return CU_get_error();
	}
	
	CU_basic_set_mode(CU_BRM_VERBOSE);
	CU_basic_run_tests();
	CU_cleanup_registry();
	return CU_get_error();
}

void testcreateProdMatranddestroyProdMatr(void)
{
	Polyonym source1;
	double * matrix1 = NULL;
	matrix1=malloc(sizeof(double)*2);
	matrix1[0] = 0.0;
	matrix1[1] = 0.0;
	source1.matrix=matrix1;
	source1.var = 'y';
	source1.d = 2;
	Polyonym source2;
	double * matrix2 = NULL;
	matrix2=malloc(sizeof(double)*2);
	matrix2[0] = 0.0;
	matrix2[1] = 0.0;
	source2.matrix=matrix2;
	source2.var = 'y';
	source2.d = 2;
	Sylvester sylvester;
	sylvester.matrix[2];
	sylvester.matrix[0] = &source1;
	sylvester.matrix[1] = &source2;
	sylvester.dim = 2;
	sylvester.hidden = 'y';
	sylvester.degree = 2;
	ProductMatrices * prodMat = NULL;
	
	CU_ASSERT(createProdMatr(&sylvester, &prodMat)==0);
	destroyProdMatr(prodMat);

	free(matrix1);
	free(matrix2);
}

void testprintProdMatr(void)
{
	ProductMatrices prodMat;
	double *** matrix = NULL;
	matrix=malloc(sizeof(double**)*2);
	matrix[0]=malloc(sizeof(double*)*2);
	matrix[0][0]=malloc(sizeof(double)*2);
	matrix[0][1]=malloc(sizeof(double)*2);
	matrix[1]=malloc(sizeof(double*)*2);
	matrix[1][0]=malloc(sizeof(double)*2);
	matrix[1][1]=malloc(sizeof(double)*2);
	matrix[0][0][0] = 2.0;
	matrix[0][0][1] = 2.0;
	matrix[0][1][0] = 2.0;
	matrix[0][1][1] = 2.0;
	matrix[1][0][0] = 2.0;
	matrix[1][0][1] = 2.0;
	matrix[1][1][0] = 2.0;
	matrix[1][1][1] = 2.0;
	prodMat.matrix = matrix;
	prodMat.dim = 2;
	prodMat.hidden = 'y';
	prodMat.degree = 1;
	prodMat.k = 1.0;
	int in = 1;
	
	printProdMatr(&prodMat, in);

	free(matrix[1][1]);
	free(matrix[1][0]);
	free(matrix[1]);
	free(matrix[0][1]);
	free(matrix[0][0]);
	free(matrix[0]);
	free(matrix);
}

void testchangeofvar3(void)
{
	ProductMatrices prodMat;
	double *** matrix = NULL;
	matrix=malloc(sizeof(double**)*2);
	matrix[0]=malloc(sizeof(double*)*2);
	matrix[0][0]=malloc(sizeof(double)*2);
	matrix[0][1]=malloc(sizeof(double)*2);
	matrix[1]=malloc(sizeof(double*)*2);
	matrix[1][0]=malloc(sizeof(double)*2);
	matrix[1][1]=malloc(sizeof(double)*2);
	matrix[0][0][0] = 2.0;
	matrix[0][0][1] = 2.0;
	matrix[0][1][0] = 2.0;
	matrix[0][1][1] = 2.0;
	matrix[1][0][0] = 2.0;
	matrix[1][0][1] = 2.0;
	matrix[1][1][0] = 2.0;
	matrix[1][1][1] = 2.0;
	prodMat.matrix = matrix;
	prodMat.dim = 2;
	prodMat.hidden = 'y';
	prodMat.degree = 1;
	prodMat.k = 1.0;
	ProductMatrices * final = NULL;
	int allow = 1;
	int t[4];
	
	CU_ASSERT(changeofvar3(&final, &prodMat, allow, t)>=0);

	free(matrix[1][1]);
	free(matrix[1][0]);
	free(matrix[1]);
	free(matrix[0][1]);
	free(matrix[0][0]);
	free(matrix[0]);
	free(matrix);
}

void testget_Productdim(void)
{
	ProductMatrices prodMat;
	double *** matrix = NULL;
	matrix=malloc(sizeof(double**)*2);
	matrix[0]=malloc(sizeof(double*)*2);
	matrix[0][0]=malloc(sizeof(double)*2);
	matrix[0][1]=malloc(sizeof(double)*2);
	matrix[1]=malloc(sizeof(double*)*2);
	matrix[1][0]=malloc(sizeof(double)*2);
	matrix[1][1]=malloc(sizeof(double)*2);
	matrix[0][0][0] = 2.0;
	matrix[0][0][1] = 2.0;
	matrix[0][1][0] = 2.0;
	matrix[0][1][1] = 2.0;
	matrix[1][0][0] = 2.0;
	matrix[1][0][1] = 2.0;
	matrix[1][1][0] = 2.0;
	matrix[1][1][1] = 2.0;
	prodMat.matrix = matrix;
	prodMat.dim = 2;
	prodMat.hidden = 'y';
	prodMat.degree = 1;
	prodMat.k = 1.0;
	
	CU_ASSERT(get_Productdim(&prodMat)>=0);

	free(matrix[1][1]);
	free(matrix[1][0]);
	free(matrix[1]);
	free(matrix[0][1]);
	free(matrix[0][0]);
	free(matrix[0]);
	free(matrix);
}

void testget_Productk(void)
{
	ProductMatrices prodMat;
	double *** matrix = NULL;
	matrix=malloc(sizeof(double**)*2);
	matrix[0]=malloc(sizeof(double*)*2);
	matrix[0][0]=malloc(sizeof(double)*2);
	matrix[0][1]=malloc(sizeof(double)*2);
	matrix[1]=malloc(sizeof(double*)*2);
	matrix[1][0]=malloc(sizeof(double)*2);
	matrix[1][1]=malloc(sizeof(double)*2);
	matrix[0][0][0] = 2.0;
	matrix[0][0][1] = 2.0;
	matrix[0][1][0] = 2.0;
	matrix[0][1][1] = 2.0;
	matrix[1][0][0] = 2.0;
	matrix[1][0][1] = 2.0;
	matrix[1][1][0] = 2.0;
	matrix[1][1][1] = 2.0;
	prodMat.matrix = matrix;
	prodMat.dim = 2;
	prodMat.hidden = 'y';
	prodMat.degree = 1;
	prodMat.k = 1.0;
	
	CU_ASSERT(get_Productk(&prodMat)>=0.0);

	free(matrix[1][1]);
	free(matrix[1][0]);
	free(matrix[1]);
	free(matrix[0][1]);
	free(matrix[0][0]);
	free(matrix[0]);
	free(matrix);
}

void testget_Producthidden(void)
{
	ProductMatrices prodMat;
	double *** matrix = NULL;
	matrix=malloc(sizeof(double**)*2);
	matrix[0]=malloc(sizeof(double*)*2);
	matrix[0][0]=malloc(sizeof(double)*2);
	matrix[0][1]=malloc(sizeof(double)*2);
	matrix[1]=malloc(sizeof(double*)*2);
	matrix[1][0]=malloc(sizeof(double)*2);
	matrix[1][1]=malloc(sizeof(double)*2);
	matrix[0][0][0] = 2.0;
	matrix[0][0][1] = 2.0;
	matrix[0][1][0] = 2.0;
	matrix[0][1][1] = 2.0;
	matrix[1][0][0] = 2.0;
	matrix[1][0][1] = 2.0;
	matrix[1][1][0] = 2.0;
	matrix[1][1][1] = 2.0;
	prodMat.matrix = matrix;
	prodMat.dim = 2;
	prodMat.hidden = 'y';
	prodMat.degree = 1;
	prodMat.k = 1.0;
	
	CU_ASSERT(get_Producthidden(&prodMat)=='y');

	free(matrix[1][1]);
	free(matrix[1][0]);
	free(matrix[1]);
	free(matrix[0][1]);
	free(matrix[0][0]);
	free(matrix[0]);
	free(matrix);
}

void testget_Productdegree(void)
{
	ProductMatrices prodMat;
	double *** matrix = NULL;
	matrix=malloc(sizeof(double**)*2);
	matrix[0]=malloc(sizeof(double*)*2);
	matrix[0][0]=malloc(sizeof(double)*2);
	matrix[0][1]=malloc(sizeof(double)*2);
	matrix[1]=malloc(sizeof(double*)*2);
	matrix[1][0]=malloc(sizeof(double)*2);
	matrix[1][1]=malloc(sizeof(double)*2);
	matrix[0][0][0] = 2.0;
	matrix[0][0][1] = 2.0;
	matrix[0][1][0] = 2.0;
	matrix[0][1][1] = 2.0;
	matrix[1][0][0] = 2.0;
	matrix[1][0][1] = 2.0;
	matrix[1][1][0] = 2.0;
	matrix[1][1][1] = 2.0;
	prodMat.matrix = matrix;
	prodMat.dim = 2;
	prodMat.hidden = 'y';
	prodMat.degree = 1;
	prodMat.k = 1.0;
	
	CU_ASSERT(get_Productdegree(&prodMat)>=0);

	free(matrix[1][1]);
	free(matrix[1][0]);
	free(matrix[1]);
	free(matrix[0][1]);
	free(matrix[0][0]);
	free(matrix[0]);
	free(matrix);
}
