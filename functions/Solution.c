#include "stdlib.h"
#include "../headers/Solution.h"
#include "../headers/Vector.h"

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

struct Gen_eigensol{
	eigensol * solution;
	int dim;
};

struct eigensol{
	Vector eigenvector;
	double eigenvalue;
};

void createSolution(Gen_eigensol * solution, int dim, double * eigenValue, double * eigenVector) {
	int i;
	solution=malloc(sizeof(struct Gen_eigensol));
	if(solution==NULL){perror("malloc GeneralSolution");exit(0);}
	for (i=0 ; i<dim ; i++) {
		solution->solution=malloc(sizeof(struct eigensol));
		if(solution->solution==NULL){perror("malloc Solution");exit(0);}
		//TODO use createStableVector() here
		//solution->solution->eigenvector=
		solution->solution->eigenvalue=eigenValue[i];
	}
	solution->dim=dim;
	return;
}

