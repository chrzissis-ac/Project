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
	double * temp=NULL;
	temp=malloc(sizeof(double)*dim*dim);
	if(temp==NULL){perror("malloc temp create solution");exit(0);}
	
	for (i=0 ; i<dim ; i++) {
		for (j=0 ; j<dim ; j++) {
			temp[i*dim+j]=eigenVector[j*dim+i];
		}
	}
	
	for (i=0 ; i<dim ; i++) {
			if (temp[(i+1)*dim-1]!=0.0) {
				for (j=0 ; j<dim ; j++) {
					temp[i*dim+j]=temp[i*dim+j]/temp[(i+1)*dim-1];
				}
		}
	}
	for (i=0 ; i<dim ; i++) {
		createStableVector(&((*solution)->solution[i].eigenvector), &(temp[i*dim]), dim, c);
		(*solution)->solution->eigenvalue=eigenValue[i];
	}
	(*solution)->dim=dim;
	free(temp);
	return;
}

void destroyGen_eigensol(Gen_eigensol ** solution){
	int i;
	for(i=0;i<(*solution)->dim;i++){
		deleteVector_static(&((*solution)->solution[i].eigenvector));
	}
	free((*solution)->solution);
	free(*solution);
}

void printGen_eigensol(Gen_eigensol * solution){
	int i;
	for (i=0 ; i < solution->dim ; i++) {
		printf("====Vector-%d=====\n",i+1);
		printVector(&(solution->solution[i].eigenvector));
		printf("\nwith Eigenvalue: %f\n",solution->solution[i].eigenvalue);
	}
}
