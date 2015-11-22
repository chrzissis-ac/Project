#include <stdio.h>
#include <stdlib.h>
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

void createSolution(Gen_eigensol ** solution, int dim, double * eigenValue, double * eigenVector,char c) {
	int i,j;
	(*solution)=malloc(sizeof(struct Gen_eigensol));
	if((*solution)==NULL){perror("malloc GeneralSolution");exit(0);}
	(*solution)->solution=malloc(sizeof(struct eigensol)*dim);
	if((*solution)->solution==NULL){perror("malloc Solution");exit(0);}
	
	for (i=0 ; i<dim ; i++) {
			if (eigenVector[i*dim]!=0.0) {
				for (j=0 ; j<dim ; j++) {
					eigenVector[i*dim+j]=eigenVector[i*dim+j]/eigenVector[(i+1)*dim-1];
				}
		}
	}

	for (i=0 ; i<dim ; i++) {
		createStableVector(&((*solution)->solution[i].eigenvector), &(eigenVector[i*dim]), dim, 'b');
		printf("====Vector-%d=====\n\n",i);
		printVector(&((*solution)->solution[i].eigenvector));
		(*solution)->solution->eigenvalue=eigenValue[i];
		printf("\n with eigenvalue %f\n",eigenValue[i]);
	}
	(*solution)->dim=dim;
	return;
}


