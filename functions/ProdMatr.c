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
	(*prodMat)->matrix=malloc(sizeof(double**)*(degree+1));
	if ((*prodMat)->matrix==NULL) {perror("Product Matrices malloc!");exit(0);}
	for (i=0 ; i<=degree ; i++) {
		(*prodMat)->matrix[i]=NULL;
		(*prodMat)->matrix[i]=malloc(sizeof(double*)*dim);
		if ((*prodMat)->matrix[i]==NULL) {perror("Product Matrices 1D malloc!");exit(0);}
		for (j=0 ; j<dim ; j++) {
			(*prodMat)->matrix[i][j]=NULL;
			(*prodMat)->matrix[i][j]=malloc(sizeof(double)*dim);
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
				printf("%d", (int)(prodMat->matrix[i][j][k]));
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

void multProdMatr(ProductMatrices ** target, Polyonym * poly, ProductMatrices * matrix, int g){
	int i=0,j=0,m=0;
	(*target)=NULL;
	(*target)=malloc(sizeof(ProductMatrices));
	if((*target)==NULL){perror("prod matrices multiplication malloc");exit(0);}
	(*target)->dim=matrix->dim;
	(*target)->hidden=poly->var;
	(*target)->degree=poly->d;
	(*target)->matrix=NULL;
	(*target)->matrix=malloc(sizeof(double**)*((*target)->degree+1));
	if ((*target)->matrix==NULL) {perror("Product Matrices multiplication malloc!");exit(0);}
	for (i=0 ; i<=(*target)->degree ; i++) {
		(*target)->matrix[i]=NULL;
		(*target)->matrix[i]=malloc(sizeof(double*)*(*target)->dim);
		if ((*target)->matrix[i]==NULL) {perror("Product Matrices multiplication 1D malloc!");exit(0);}
		for (j=0 ; j<(*target)->dim ; j++) {
			(*target)->matrix[i][j]=NULL;
			(*target)->matrix[i][j]=malloc(sizeof(double)*(*target)->dim);
			if ((*target)->matrix[i][j]==NULL) {perror("Product multiplication 2D malloc!");exit(0);}
		}
	}
	for (m=0 ; m<=(*target)->degree ; m++) {
		for (i=0 ; i<(*target)->dim ; i++) {
			for (j=0 ; j<(*target)->dim ; j++) {
				(*target)->matrix[m][i][j]=(matrix->matrix[g][i][j])*(poly->matrix[m]);
			}
		}
	}
}

void addProdMatr(ProductMatrices ** target, ProductMatrices * matrix1, ProductMatrices * matrix2){
	int i=0,j=0,m=0;
	(*target)=NULL;
	(*target)=malloc(sizeof(ProductMatrices));
	if((*target)==NULL){perror("prod matrices multiplication malloc");exit(0);}
	(*target)->dim=matrix1->dim;
	(*target)->hidden=matrix1->hidden;
	(*target)->degree=matrix1->degree;
	(*target)->matrix=NULL;
	(*target)->matrix=malloc(sizeof(double**)*((*target)->degree+1));
	if ((*target)->matrix==NULL) {perror("Product Matrices multiplication malloc!");exit(0);}
	for (i=0 ; i<=(*target)->degree ; i++) {
		(*target)->matrix[i]=NULL;
		(*target)->matrix[i]=malloc(sizeof(double*)*(*target)->dim);
		if ((*target)->matrix[i]==NULL) {perror("Product Matrices multiplication 1D malloc!");exit(0);}
		for (j=0 ; j<(*target)->dim ; j++) {
			(*target)->matrix[i][j]=NULL;
			(*target)->matrix[i][j]=malloc(sizeof(double)*(*target)->dim);
			if ((*target)->matrix[i][j]==NULL) {perror("Product multiplication 2D malloc!");exit(0);}
		}
	}
	for (m=0 ; m<=(*target)->degree ; m++) {
		for (i=0 ; i<(*target)->dim ; i++) {
			for (j=0 ; j<(*target)->dim ; j++) {
				(*target)->matrix[m][i][j]=(matrix1->matrix[m][i][j])+(matrix2->matrix[m][i][j]);
			}
		}
	}

}
