#include <CUnit/CUnit.h>
#include "../headers/ComplexPoly.h"

void testpolyonymtryvalue(void);
void testcreatepolyonym2anddeletepoly2(void);
void testprintpolymatrix(void);
void testprintpoly(void);
void testprintpoly_byvar(void);
void testgetDegree2(void);
void testget_polymatrix2(void);

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
	
	CU_basic_set_mode(CU_BRM_VERBOSE);
	CU_basic_run_tests();
	CU_cleanup_registry();
	return CU_get_error();
}

void testpolyonymtryvalue(void)
{
	struct Polyonym2{
		int ** matrix;
		int dx;
		int dy;
	} poly = { {{0, 0}, {0, 0}}, 2, 2 };
	double vx = 2.0;
	double vy = 2.0;

	CU_ASSERT(polyonymtryvalue(&poly, dx, dy)>0.0);
}

void testcreatepolyonym2anddeletepoly2(void)
{
	char function = "x^3-3yx+5";
	struct Polyonym2 * poly;
	int d = 3;

	CU_ASSERT(createpolyonym2(function, &poly, d));
	CU_ASSERT(deletepoly2(poly));
}

void testprintpolymatrix(void)
{
	struct Polyonym2{
		int ** matrix;
		int dx;
		int dy;
	} poly = { {{0, 0}, {0, 0}}, 2, 2 };

	CU_ASSERT(printpolymatrix(&poly));
}

void testprintpoly(void)
{
	struct Polyonym2{
		int ** matrix;
		int dx;
		int dy;
	} poly = { {{0, 0}, {0, 0}}, 2, 2 };

	CU_ASSERT(printpoly(&poly));
}

void testprintpoly_byvar(void)
{
	struct Polyonym2{
		int ** matrix;
		int dx;
		int dy;
	} poly = { {{0, 0}, {0, 0}}, 2, 2 };

	CU_ASSERT(printpoly_byvar(&poly));
}

void testgetDegree2(void)
{
	struct Polyonym2{
		int ** matrix;
		int dx;
		int dy;
	} poly = { {{0, 0}, {0, 0}}, 2, 2 };
	char v = 'x';
	
	CU_ASSERT(getDegree2(&poly, v)>0);
}


void testget_polymatrix2(void)
{
	struct Polyonym2{
		int ** matrix;
		int dx;
		int dy;
	} poly = { {{0, 0}, {0, 0}}, 2, 2 };
	int i = 2;
	int j = 2;
	
	CU_ASSERT(get_polymatrix2(&poly, i, j)>0);
}