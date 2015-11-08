#include <stdio.h>
#include <stdlib.h>

#include "../headers/ProdMatr.h"
#include "../headers/Sylvester.h"

typedef int * Poly;
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
	int *** matrix;
	int dim;
	char hidden;
	int degree;
};

//---------------------------------------------------------Product matrices of Sylvester management--------------------------------------------------

// createProdMatr() creates a ProductMatrices struct  ('prodMat') and its matrices[i] are filled with the coefficients of hidden variable ^ i that are stored in the matrix of 'sylvester'
void createProdMatr (Sylvester * sylvester, ProductMatrices ** prodMat) {
	int degree, dim, i, j, m;
	(*prodMat)=NULL;
	(*prodMat)=malloc(sizeof(ProductMatrices));
	if ((*prodMat)==NULL) {perror("Product Matrix malloc!");exit(0);}
	(*prodMat)->hidden=sylvester->hidden;
	degree=sylvester->degree;
	(*prodMat)->degree=degree;
	dim=sylvester->dim;
	(*prodMat)->dim=dim;
	(*prodMat)->matrix=NULL;
	(*prodMat)->matrix=malloc(sizeof(int**)*(degree+1));
	if ((*prodMat)->matrix==NULL) {perror("Product Matrices malloc!");exit(0);}
	for (i=0 ; i<=degree ; i++) {
		(*prodMat)->matrix[i]=NULL;
		(*prodMat)->matrix[i]=malloc(sizeof(int*)*dim);
		if ((*prodMat)->matrix[i]==NULL) {perror("Product Matrices 1D malloc!");exit(0);}
		for (j=0 ; j<dim ; j++) {
			(*prodMat)->matrix[i][j]=NULL;
			(*prodMat)->matrix[i][j]=malloc(sizeof(int)*dim);
			if ((*prodMat)->matrix[i][j]==NULL) {perror("Product 2D malloc!");exit(0);}
		}
	}
	for (m=0 ; m<=degree ; m++) {
		for (i=0 ; i<dim ; i++) {
			for (j=0 ; j<dim ; j++) {
				(*prodMat)->matrix[m][i][j]=get1NumByDegree(&(sylvester->matrix[i][j]), m);
			}
		}
	}

	return;
}

// printProdMatr() prints the matrix['in'] of 'prodMat'
void printProdMatr (ProductMatrices * prodMat, int in) {
	if(in>prodMat->degree || in<0){
		printf("There is no %d grade in the Sylvester Product Matrices!\n",in);
		return;
	}
	printf("Product matrix of grade %d is:\n\n",in);
	int degree, dim, i, j, k;
	i=in;
	degree=prodMat->degree;
	dim=prodMat->dim;
		for (j=0 ; j<dim ; j++) {
			for (k=0 ; k<dim ; k++) {
				printf("%d", prodMat->matrix[i][j][k]);
				printf("|\t");
			}
			printf("\n");
		}
		printf("\n");
	printf("With dimension %dx%d.\n",prodMat->dim,prodMat->dim);
	return;
}

// destroyProdMatr() frees the memory that was allocated for 'prodMat'
void destroyProdMatr (ProductMatrices * prodMat){
	int degree, dim, i, j, k;
	degree=prodMat->degree;
	dim=prodMat->dim;
	for (i=0 ; i<=degree ; i++) {
		for (j=0 ; j<dim ; j++) {
			free(prodMat->matrix[i][j]);
		}
		free(prodMat->matrix[i]);
	}
	
	free(prodMat->matrix);
	free(prodMat);
	return;
}

