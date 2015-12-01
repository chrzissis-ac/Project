#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <stdlib.h>
#include "../headers/ProdMatr.h"
#include "../headers/CompanionMatrix.h"
#include "../headers/Solution.h"

struct ProductMatrices{
	double *** matrix;
	int dim;
	char hidden;
	int degree;
	double k;
};

struct CompanionMatrix{
	double ** matrix;
	int dim;
};

struct CMatrix{
	double ** matrixY;
	double ** matrix;
	int dim;
};

void testcreateCompanionMatrixanddeleteCompanionMatrix(void);
void testprintCompanionMatrix(void);
void testcreateCMatrixanddeleteCMatrix(void);
void testprintCMatrix(void);
void testget_Companiondim(void);
void testget_Companionmatrix(void);
void testget_Cdim(void);
void testget_CmatrixY(void);
void testget_Cmatrix(void);

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
	
	if (CU_add_test(pSuite, "test of createCompanionMatrix() and deleteCompanionMatrix()", testcreateCompanionMatrixanddeleteCompanionMatrix) == NULL) {
		CU_cleanup_registry();
		return CU_get_error();
	}
	if (CU_add_test(pSuite, "test of printCompanionMatrix()", testprintCompanionMatrix) == NULL) {
		CU_cleanup_registry();
		return CU_get_error();
	}
	if (CU_add_test(pSuite, "test of createCMatrix() and deleteCMatrix()", testcreateCMatrixanddeleteCMatrix) == NULL) {
		CU_cleanup_registry();
		return CU_get_error();
	}
	if (CU_add_test(pSuite, "test of printCMatrix()", testprintCMatrix) == NULL) {
		CU_cleanup_registry();
		return CU_get_error();
	}
	if (CU_add_test(pSuite, "test of get_Companiondim()", testget_Companiondim) == NULL) {
		CU_cleanup_registry();
		return CU_get_error();
	}
	if (CU_add_test(pSuite, "test of get_Companionmatrix()", testget_Companionmatrix) == NULL) {
		CU_cleanup_registry();
		return CU_get_error();
	}
	if (CU_add_test(pSuite, "test of get_Cdim()", testget_Cdim) == NULL) {
		CU_cleanup_registry();
		return CU_get_error();
	}
	if (CU_add_test(pSuite, "test of get_CmatrixY()", testget_CmatrixY) == NULL) {
		CU_cleanup_registry();
		return CU_get_error();
	}
	if (CU_add_test(pSuite, "test of get_Cmatrix()", testget_Cmatrix) == NULL) {
		CU_cleanup_registry();
		return CU_get_error();
	}
	
	CU_basic_set_mode(CU_BRM_VERBOSE);
	CU_basic_run_tests();
	CU_cleanup_registry();
	return CU_get_error();
}

void testcreateCompanionMatrixanddeleteCompanionMatrix(void)
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
	matrix[2][2][2];
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
	CompanionMatrix * compMatr = NULL;
	
	createCompanionMatrix(&prodMat, &compMatr);
	deleteCompanionMatrix(&compMatr);

	free(matrix[1][1]);
	free(matrix[1][0]);
	free(matrix[1]);
	free(matrix[0][1]);
	free(matrix[0][0]);
	free(matrix[0]);
	free(matrix);
}

void testprintCompanionMatrix(void)
{
	CompanionMatrix compMatr;
	double ** matrix = NULL;
	matrix=malloc(sizeof(double*)*2);
	matrix[0]=malloc(sizeof(double)*2);
	matrix[1]=malloc(sizeof(double)*2);
	matrix[2][2];
	matrix[0][0] = 1.0;
	matrix[0][1] = 2.0;
	matrix[1][0] = 3.0;
	matrix[1][1] = 4.0;	
	compMatr.matrix=matrix;
	compMatr.dim = 2;

	printCompanionMatrix(&compMatr);

	free(matrix[0]);
	free(matrix[1]);
	free(matrix);
}

void testcreateCMatrixanddeleteCMatrix(void)
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
	CMatrix * cMatr = NULL;
	
	createCMatrix(&prodMat, &cMatr);
	deleteCMatrix(&cMatr);

	free(matrix[1][1]);
	free(matrix[1][0]);
	free(matrix[1]);
	free(matrix[0][1]);
	free(matrix[0][0]);
	free(matrix[0]);
	free(matrix);
}

void testprintCMatrix(void)
{
	CMatrix cMatr;
	double ** matrixY = NULL;
	matrixY=malloc(sizeof(double*)*2);
	matrixY[0]=malloc(sizeof(double)*2);
	matrixY[1]=malloc(sizeof(double)*2);
	matrixY[0][0] = 1.0;
	matrixY[0][1] = 2.0;
	matrixY[1][0] = 3.0;
	matrixY[1][1] = 4.0;	
	cMatr.matrixY=matrixY;
	double ** matrix = NULL;
	matrix=malloc(sizeof(double*)*2);
	matrix[0]=malloc(sizeof(double)*2);
	matrix[1]=malloc(sizeof(double)*2);
	matrix[0][0] = 1.0;
	matrix[0][1] = 2.0;
	matrix[1][0] = 3.0;
	matrix[1][1] = 4.0;	
	cMatr.matrix=matrix;	
	cMatr.dim = 2;

	printCMatrix(&cMatr);

	free(matrix[1]);
	free(matrix[0]);
	free(matrix);
	free(matrixY[1]);
	free(matrixY[0]);
	free(matrixY);
}

void testget_Companiondim(void)
{
	CompanionMatrix compMatr;
	double ** matrix = NULL;
	matrix=malloc(sizeof(double*)*2);
	matrix[0]=malloc(sizeof(double)*2);
	matrix[1]=malloc(sizeof(double)*2);
	matrix[0][0] = 1.0;
	matrix[0][1] = 2.0;
	matrix[1][0] = 3.0;
	matrix[1][1] = 4.0;	
	compMatr.dim = 2;
	
	CU_ASSERT(get_Companiondim(&compMatr)>0);

	free(matrix[0]);
	free(matrix[1]);
	free(matrix);
}

void testget_Companionmatrix(void)
{
	CompanionMatrix compMatr;
	double ** matrix = NULL;
	matrix=malloc(sizeof(double*)*2);
	matrix[0]=malloc(sizeof(double)*2);
	matrix[1]=malloc(sizeof(double)*2);
	matrix[0][0] = 1.0;
	matrix[0][1] = 2.0;
	matrix[1][0] = 3.0;
	matrix[1][1] = 4.0;	
	compMatr.dim = 2;
	
	CU_ASSERT(get_Companionmatrix(&compMatr)!=NULL);

	free(matrix[0]);
	free(matrix[1]);
	free(matrix);
}

void testget_Cdim(void)
{
	CMatrix cMatr;
	double ** matrixY = NULL;
	matrixY=malloc(sizeof(double*)*2);
	matrixY[0]=malloc(sizeof(double)*2);
	matrixY[1]=malloc(sizeof(double)*2);
	matrixY[0][0] = 1.0;
	matrixY[0][1] = 2.0;
	matrixY[1][0] = 3.0;
	matrixY[1][1] = 4.0;	
	cMatr.matrixY=matrixY;
	double ** matrix = NULL;
	matrix=malloc(sizeof(double*)*2);
	matrix[0]=malloc(sizeof(double)*2);
	matrix[1]=malloc(sizeof(double)*2);
	matrix[0][0] = 1.0;
	matrix[0][1] = 2.0;
	matrix[1][0] = 3.0;
	matrix[1][1] = 4.0;	
	cMatr.matrix=matrix;	
	cMatr.dim = 2;
	
	CU_ASSERT(get_Cdim(&cMatr)>0);

	free(matrix[1]);
	free(matrix[0]);
	free(matrix);
	free(matrixY[1]);
	free(matrixY[0]);
	free(matrixY);
}

void testget_CmatrixY(void)
{
	CMatrix cMatr;
	double ** matrixY = NULL;
	matrixY=malloc(sizeof(double*)*2);
	matrixY[0]=malloc(sizeof(double)*2);
	matrixY[1]=malloc(sizeof(double)*2);
	matrixY[0][0] = 1.0;
	matrixY[0][1] = 2.0;
	matrixY[1][0] = 3.0;
	matrixY[1][1] = 4.0;	
	cMatr.matrixY=matrixY;
	double ** matrix = NULL;
	matrix=malloc(sizeof(double*)*2);
	matrix[0]=malloc(sizeof(double)*2);
	matrix[1]=malloc(sizeof(double)*2);
	matrix[0][0] = 1.0;
	matrix[0][1] = 2.0;
	matrix[1][0] = 3.0;
	matrix[1][1] = 4.0;	
	cMatr.matrix=matrix;	
	cMatr.dim = 2;
	
	CU_ASSERT(get_CmatrixY(&cMatr)!=NULL);

	free(matrix[1]);
	free(matrix[0]);
	free(matrix);
	free(matrixY[1]);
	free(matrixY[0]);
	free(matrixY);
}

void testget_Cmatrix(void)
{
	CMatrix cMatr;
	double ** matrixY = NULL;
	matrixY=malloc(sizeof(double*)*2);
	matrixY[0]=malloc(sizeof(double)*2);
	matrixY[1]=malloc(sizeof(double)*2);
	matrixY[0][0] = 1.0;
	matrixY[0][1] = 2.0;
	matrixY[1][0] = 3.0;
	matrixY[1][1] = 4.0;	
	cMatr.matrixY=matrixY;
	double ** matrix = NULL;
	matrix=malloc(sizeof(double*)*2);
	matrix[0]=malloc(sizeof(double)*2);
	matrix[1]=malloc(sizeof(double)*2);
	matrix[0][0] = 1.0;
	matrix[0][1] = 2.0;
	matrix[1][0] = 3.0;
	matrix[1][1] = 4.0;	
	cMatr.matrix=matrix;	
	cMatr.dim = 2;
	
	CU_ASSERT(get_Cmatrix(&cMatr)!=NULL);

	free(matrix[1]);
	free(matrix[0]);
	free(matrix);
	free(matrixY[1]);
	free(matrixY[0]);
	free(matrixY);
}
