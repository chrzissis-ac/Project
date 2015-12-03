#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <stdlib.h>
#include <lapacke.h>
#include "../headers/Routines.h"
#include "../headers/Vector.h"
#include "../headers/Sylvester.h"
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

struct Vector{
	Polyonym * matrix;
	int dim;
};

struct Sylvester{
	Polyonym ** matrix;
	int dim;
	char hidden;
	int degree;
};

void testcreatesylvesteranddestroysylvester(void);
void testprintsylvester(void);
void testSvmult(void);
void testSylvesterDeterminant(void);

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
	
	if (CU_add_test(pSuite, "test of createsylvester() and destroysylvester()", testcreatesylvesteranddestroysylvester) == NULL) {
		CU_cleanup_registry();
		return CU_get_error();
	}
	if (CU_add_test(pSuite, "test of printsylvester()", testprintsylvester) == NULL) {
		CU_cleanup_registry();
		return CU_get_error();
	}
	if (CU_add_test(pSuite, "test of Svmult()", testSvmult) == NULL) {
		CU_cleanup_registry();
		return CU_get_error();
	}
	if (CU_add_test(pSuite, "test of SylvesterDeterminant()", testSylvesterDeterminant) == NULL) {
		CU_cleanup_registry();
		return CU_get_error();
	}
	
	CU_basic_set_mode(CU_BRM_VERBOSE);
	CU_basic_run_tests();
	CU_cleanup_registry();
	return CU_get_error();
}

void testcreatesylvesteranddestroysylvester(void)
{
	Polyonym2 poly1;
	int ** matrix1 = NULL;
	matrix1=malloc(sizeof(int *) * 2);
	matrix1[0]=malloc(sizeof(int)*2);
	matrix1[1]=malloc(sizeof(int)*2);
	matrix1[0][0] = 0;
	matrix1[0][1] = 1;
	matrix1[1][0] = 2;
	matrix1[1][1] = 3;
	poly1.matrix = matrix1;
	poly1.dy = 1;
	poly1.dx = 1;
	Polyonym2 poly2;
	int ** matrix2 = NULL;
	matrix2=malloc(sizeof(int *) * 2);
	matrix2[0]=malloc(sizeof(int)*2);
	matrix2[1]=malloc(sizeof(int)*2);
	matrix2[0][0] = 0;
	matrix2[0][1] = 1;
	matrix2[1][0] = 2;
	matrix2[1][1] = 3;
	poly2.matrix = matrix2;
	poly2.dy = 1;
	poly2.dx = 1;
	Sylvester * sylv;
	
	createsylvester(&sylv, &poly1, &poly2);
	destroysylvester(&sylv);

	free(matrix1[1]);
	free(matrix1[0]);
	free(matrix1);
	free(matrix2[1]);
	free(matrix2[0]);
	free(matrix2);
}

void testprintsylvester(void)
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
	sylvester.matrix=malloc(sizeof(struct Polyonym)*2);
	sylvester.matrix[0] = &source1;
	sylvester.matrix[1] = &source2;
	sylvester.dim = 2;
	sylvester.hidden = 'y';
	sylvester.degree = 2;

	printsylvester(&sylvester);

	free(matrix1);
	free(matrix2);
	free(sylvester.matrix);
}

void testSvmult(void)
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
	sylvester.matrix=malloc(sizeof(struct Polyonym)*2);
	sylvester.matrix[0] = &source1;
	sylvester.matrix[1] = &source2;
	sylvester.dim = 2;
	sylvester.hidden = 'y';
	sylvester.degree = 1;
	Polyonym * poly=malloc(sizeof(struct Polyonym));
	double * matrix = NULL;
	matrix=malloc(sizeof(double)*1);
	matrix[0] = 0.0;
	poly->matrix=matrix;
	poly->var = 'y';
	poly->d = 1;
	Vector * vector = malloc(sizeof(struct Vector));
	vector->matrix = poly;
	vector->dim = 0;
	Vector * final;
	
	Svmult(&sylvester, vector, &final);

	free(matrix1);
	free(matrix2);
	free(matrix);
	free(sylvester.matrix);
}

void testSylvesterDeterminant(void)
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
	sylvester.matrix=malloc(sizeof(struct Polyonym)*2);
	sylvester.matrix[0] = &source1;
	sylvester.matrix[1] = &source2;
	sylvester.dim = 2;
	sylvester.hidden = 'y';
	sylvester.degree = 1;
	double value = 1.0;
	int print = 1;
	
	CU_ASSERT(SylvesterDeterminant(&sylvester, value, print)>0.0);

	free(matrix1);
	free(matrix2);
	free(sylvester.matrix);
}
