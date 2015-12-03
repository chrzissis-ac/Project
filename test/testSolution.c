#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <stdlib.h>
#include "../headers/Solution.h"
#include "../headers/Vector.h"

typedef int ** Poly2;
struct Polyonym2{
	Poly2 matrix;
	int dx;
	int dy;
};

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

struct Eigenstruct{
	CompanionMatrix * Comp;
	CMatrix * C;
	char eigenvar;
	int grade;
	int problemisGen;
};

struct Gen_eigensol{
	eigensol * solution;
	int dim;
};

struct Vector{
	Polyonym * matrix;
	int dim;
};

struct eigensol{
	Vector eigenvector;
	double eigenvalue;
	double eigenvalue_imaginary;
	int inf;
};

typedef double * Poly;
struct Polyonym{
	Poly matrix;
	char var;
	int d;
};

struct Gen_sol{
	sol * solution;
	int p;
	int dim;
};

struct sol{
	double value[2];
	double value_imaginary[2];
	int multiplicity;
	int inf;
};

void testdeleteEigenstruct(void);
void testprintEigenstruct(void);
void testsolver(void);
void testdestroyGen_eigensol(void);
void testprintGen_eigensol(void);
void testchooseMatrix(void);
void testdeleteGen_sol(void);
void testprintGen_sol(void);
void testchangevarback(void);

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

	if (CU_add_test(pSuite, "test of deleteEigenstruct()", testdeleteEigenstruct) == NULL) {
		CU_cleanup_registry();
		return CU_get_error();
	}
	if (CU_add_test(pSuite, "test of printEigenstruct()", testprintEigenstruct) == NULL) {
		CU_cleanup_registry();
		return CU_get_error();
	}
	if (CU_add_test(pSuite, "test of solver()", testsolver) == NULL) {
		CU_cleanup_registry();
		return CU_get_error();
	}
	if (CU_add_test(pSuite, "test of destroyGen_eigensol()", testdestroyGen_eigensol) == NULL) {
		CU_cleanup_registry();
		return CU_get_error();
	}
	if (CU_add_test(pSuite, "test of printGen_eigensol()", testprintGen_eigensol) == NULL) {
		CU_cleanup_registry();
		return CU_get_error();
	}
	if (CU_add_test(pSuite, "test of chooseMatrix()", testchooseMatrix) == NULL) {
		CU_cleanup_registry();
		return CU_get_error();
	}
	if (CU_add_test(pSuite, "test of printGen_sol()", testprintGen_sol) == NULL) {
		CU_cleanup_registry();
		return CU_get_error();
	}
	if (CU_add_test(pSuite, "test of deleteGen_sol()", testdeleteGen_sol) == NULL) {
		CU_cleanup_registry();
		return CU_get_error();
	}
	if (CU_add_test(pSuite, "test of changevarback()", testchangevarback) == NULL) {
		CU_cleanup_registry();
		return CU_get_error();
	}

	CU_basic_set_mode(CU_BRM_VERBOSE);
	CU_basic_run_tests();
	CU_cleanup_registry();
	return CU_get_error();
}

void testdeleteEigenstruct(void)
{
	CompanionMatrix * compMatr=malloc(sizeof(struct CompanionMatrix));
	double ** matrix1 = NULL;
	matrix1=malloc(sizeof(double*)*2);
	matrix1[0]=malloc(sizeof(double)*2);
	matrix1[1]=malloc(sizeof(double)*2);
	matrix1[0][0] = 1.0;
	matrix1[0][1] = 2.0;
	matrix1[1][0] = 3.0;
	matrix1[1][1] = 4.0;
	compMatr->matrix=matrix1;
	compMatr->dim = 2;
	CMatrix * cMatr=malloc(sizeof(struct CMatrix));
	double ** matrixY = NULL;
	matrixY=malloc(sizeof(double*)*2);
	matrixY[0]=malloc(sizeof(double)*2);
	matrixY[1]=malloc(sizeof(double)*2);
	matrixY[0][0] = 1.0;
	matrixY[0][1] = 2.0;
	matrixY[1][0] = 3.0;
	matrixY[1][1] = 4.0;
	cMatr->matrixY=matrixY;
	double ** matrix2 = NULL;
	matrix2=malloc(sizeof(double*)*2);
	matrix2[0]=malloc(sizeof(double)*2);
	matrix2[1]=malloc(sizeof(double)*2);
	matrix2[0][0] = 1.0;
	matrix2[0][1] = 2.0;
	matrix2[1][0] = 3.0;
	matrix2[1][1] = 4.0;
	cMatr->matrix=matrix2;
	cMatr->dim = 2;
	Eigenstruct * Eigen=malloc(sizeof(Eigenstruct));
	Eigen->Comp = compMatr;
	Eigen->C = cMatr;
	Eigen->eigenvar = 'v';
	Eigen->grade = 2;
	Eigen->problemisGen = 0;

	deleteEigenstruct(&Eigen);
}

void testprintEigenstruct(void)
{
	CompanionMatrix compMatr;
	double ** matrix1 = NULL;
	matrix1=malloc(sizeof(double*)*2);
	matrix1[0]=malloc(sizeof(double)*2);
	matrix1[1]=malloc(sizeof(double)*2);
	matrix1[0][0] = 1.0;
	matrix1[0][1] = 2.0;
	matrix1[1][0] = 3.0;
	matrix1[1][1] = 4.0;
	compMatr.matrix=matrix1;
	compMatr.dim = 2;
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
	double ** matrix2 = NULL;
	matrix2=malloc(sizeof(double*)*2);
	matrix2[0]=malloc(sizeof(double)*2);
	matrix2[1]=malloc(sizeof(double)*2);
	matrix2[0][0] = 1.0;
	matrix2[0][1] = 2.0;
	matrix2[1][0] = 3.0;
	matrix2[1][1] = 4.0;
	cMatr.matrix=matrix2;
	cMatr.dim = 2;
	Eigenstruct Eigen;
	Eigen.Comp = &compMatr;
	Eigen.C = &cMatr;
	Eigen.eigenvar = 'v';
	Eigen.grade = 2;
	Eigen.problemisGen = 0;

	printEigenstruct(&Eigen);

	free(matrix2[0]);
	free(matrix2[1]);
	free(matrix2);
	free(matrixY[0]);
	free(matrixY[1]);
	free(matrixY);
	free(matrix1[0]);
	free(matrix1[1]);
	free(matrix1);
}

void testsolver(void)
{
	CompanionMatrix * compMatr=malloc(sizeof(struct CompanionMatrix));
	double ** matrix1 = NULL;
	matrix1=malloc(sizeof(double*)*2);
	matrix1[0]=malloc(sizeof(double)*2);
	matrix1[1]=malloc(sizeof(double)*2);
	matrix1[0][0] = 1.0;
	matrix1[0][1] = 2.0;
	matrix1[1][0] = 3.0;
	matrix1[1][1] = 4.0;
	compMatr->matrix=matrix1;
	compMatr->dim = 2;
	CMatrix * cMatr=malloc(sizeof(struct CMatrix));
	double ** matrixY = NULL;
	matrixY=malloc(sizeof(double*)*2);
	matrixY[0]=malloc(sizeof(double)*2);
	matrixY[1]=malloc(sizeof(double)*2);
	matrixY[0][0] = 1.0;
	matrixY[0][1] = 2.0;
	matrixY[1][0] = 3.0;
	matrixY[1][1] = 4.0;
	cMatr->matrixY=matrixY;
	double ** matrix2 = NULL;
	matrix2=malloc(sizeof(double*)*2);
	matrix2[0]=malloc(sizeof(double)*2);
	matrix2[1]=malloc(sizeof(double)*2);
	matrix2[0][0] = 1.0;
	matrix2[0][1] = 2.0;
	matrix2[1][0] = 3.0;
	matrix2[1][1] = 4.0;
	cMatr->matrix=matrix2;
	cMatr->dim = 2;
	Eigenstruct * Eigen=malloc(sizeof(Eigenstruct));
	Eigen->Comp = compMatr;
	Eigen->C = cMatr;
	Eigen->eigenvar = 'y';
	Eigen->grade = 1;
	Eigen->problemisGen = 0;
	Gen_eigensol * solution = NULL;
	Gen_sol * GSol = NULL;

	solver(Eigen, &solution, &GSol);

	free(matrix2[0]);
	free(matrix2[1]);
	free(matrix2);
	free(matrixY[0]);
	free(matrixY[1]);
	free(matrixY);
	free(matrix1[0]);
	free(matrix1[1]);
	free(matrix1);
}

void testdestroyGen_eigensol(void)
{
	Polyonym * poly=malloc(sizeof(struct Polyonym));
	double * matrix = NULL;
	matrix=malloc(sizeof(double)*1);
	matrix[0] = 0.0;
	poly->matrix = matrix;
	poly->var = 'y';
	poly->d = 1;
	Vector vector;
	vector.matrix = poly;
	vector.dim = 1;
	eigensol * eigen=malloc(sizeof(struct eigensol));
	eigen->eigenvector = vector;
	eigen->eigenvalue = 1.0;
	eigen->inf = 0;
	Gen_eigensol * Eigen=malloc(sizeof(struct Gen_eigensol));
	Eigen->solution = eigen;
	Eigen->dim = 1;

	destroyGen_eigensol(&Eigen);
}

void testprintGen_eigensol(void)
{
	Polyonym poly;
	double * matrix = NULL;
	matrix=malloc(sizeof(double)*1);
	matrix[0] = 0.0;
	poly.matrix = matrix;
	poly.var = 'y';
	poly.d = 1;
	Vector vector;
	vector.matrix = &poly;
	vector.dim = 1;
	eigensol eigen;
	eigen.eigenvector = vector;
	eigen.eigenvalue = 1.0;
	eigen.eigenvalue = 1.0;
	eigen.inf = 0;
	Gen_eigensol Eigen;
	Eigen.solution = &eigen;
	Eigen.dim = 1;

	printGen_eigensol(&Eigen);

	free(matrix);
}

void testchooseMatrix(void)
{
	ProductMatrices * prodMat=malloc(sizeof(struct ProductMatrices));
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
	prodMat->matrix = matrix;
	prodMat->dim = 2;
	prodMat->hidden = 'y';
	prodMat->degree = 1;
	prodMat->k = 1.0;
	Eigenstruct * Eigen = NULL;
	int V =7;

	CU_ASSERT(chooseMatrix(prodMat, &Eigen, V)>=0);

	free(matrix[1][1]);
	free(matrix[1][0]);
	free(matrix[1]);
	free(matrix[0][1]);
	free(matrix[0][0]);
	free(matrix[0]);
	free(matrix);
}

void testdeleteGen_sol(void)
{
	sol * solution=malloc(sizeof(struct sol));
	solution->value[0] = 1.0;
	solution->value[1] = 2.0;
	solution->value_imaginary[0] = 3.0;
	solution->value_imaginary[1] = 4.0;
	solution->multiplicity = 1;
	solution->inf = 0;
	Gen_sol * Eigen=malloc(sizeof(struct Gen_sol));
	Eigen->solution = solution;
	Eigen->p = 1;
	Eigen->dim = 2;

	deleteGen_sol(&Eigen);
}

void testprintGen_sol(void)
{
	sol solution;
	solution.value[0] = 1.0;
	solution.value[1] = 2.0;
	solution.value_imaginary[0] = 3.0;
	solution.value_imaginary[1] = 4.0;
	solution.multiplicity = 1;
	solution.inf = 0;
	Gen_sol Eigen;
	Eigen.solution = &solution;
	Eigen.p = 1;
	Eigen.dim = 2;
	Polyonym2 poly1;
	int ** matrix1 = NULL;
	matrix1=malloc(sizeof(int*)*2);
	matrix1[0]=malloc(sizeof(int)*2);
	matrix1[1]=malloc(sizeof(int)*2);
	matrix1[0][0] = 0;
	matrix1[0][1] = 1;
	matrix1[1][0] = 2;
	matrix1[1][1] = 3;
	poly1.matrix=matrix1;
	poly1.dy = 2;
	poly1.dx = 2;
	Polyonym2 poly2;
	int ** matrix2 = NULL;
	matrix2=malloc(sizeof(int*)*2);
	matrix2[0]=malloc(sizeof(int)*2);
	matrix2[1]=malloc(sizeof(int)*2);
	matrix2[0][0] = 0;
	matrix2[0][1] = 1;
	matrix2[1][0] = 2;
	matrix2[1][1] = 3;
	poly2.matrix=matrix2;
	poly2.dy = 2;
	poly2.dx = 2;
	int imag_flag = 0;

	printGen_sol(&Eigen, &poly1, &poly2, imag_flag);

	free(matrix1[0]);
	free(matrix1[1]);
	free(matrix1);
	free(matrix2[0]);
	free(matrix2[1]);
	free(matrix2);
}

void testchangevarback(void)
{
	sol solution;
	solution.value[0] = 1.0;
	solution.value[1] = 2.0;
	solution.value_imaginary[0] = 3.0;
	solution.value_imaginary[1] = 4.0;
	solution.multiplicity = 1;
	solution.inf = 0;
	Gen_sol Eigen;
	Eigen.solution = &solution;
	Eigen.p = 1;
	Eigen.dim = 2;
	Gen_sol * s = &Eigen;
	int * t = NULL;
	t = malloc (sizeof(int)*4);
	t[0] = 1;
	t[1] = 2;
	t[2] = 3;
	t[3] = 4;

	changevarback(&s , t);

	free(t);
}
