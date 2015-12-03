#include <stdio.h>
#include <stdlib.h>
#include <lapacke.h>
#include <cblas.h>
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



void createCompanionMatrix(ProductMatrices * startProdMatr, CompanionMatrix ** compMatr) {//Creates Companion Matrix
	int dim=0, subDim=0, compDim=0, i=0, j=0, k=0, l=0, m=0;
	ProductMatrices * prodMatr=NULL;
	double * modifiedMatrix=NULL;
	double * modifiedMatrixA=NULL;
	double * modifiedMatrixB=NULL;
	lapack_int * ipiv=NULL;
	prodMatr=malloc(sizeof(struct ProductMatrices));
	if (prodMatr==NULL) {perror("ProductMatrices struct malloc!");exit(0);}
	prodMatr->dim=startProdMatr->dim;
	prodMatr->degree=startProdMatr->degree-1;
	prodMatr->matrix=NULL;
	prodMatr->matrix=malloc(sizeof(double**)*(prodMatr->degree+1));
	if (prodMatr->matrix==NULL) {perror("Product Matrices malloc!");exit(0);}
	for (i=0 ; i<=prodMatr->degree ; i++) {
		prodMatr->matrix[i]=NULL;
		prodMatr->matrix[i]=malloc(sizeof(double*)*prodMatr->dim);
		if (prodMatr->matrix[i]==NULL) {perror("Product Matrices 1D malloc!");exit(0);}
		for (j=0 ; j< prodMatr->dim ; j++) {
			prodMatr->matrix[i][j]=NULL;
			prodMatr->matrix[i][j]=malloc(sizeof(double)*prodMatr->dim);
			if (prodMatr->matrix[i][j]==NULL) {perror("Product 2D malloc!");exit(0);}
		}
	}
	for (i=0 ; i<=prodMatr->degree ; i++) {
		for (j=0 ; j<prodMatr->dim ; j++) {
			for (k=0 ; k<prodMatr->dim ; k++) {
				prodMatr->matrix[i][j][k]=0.0;
			}
		}
	}


	ipiv=NULL;
	if(startProdMatr->dim>=6){
		ipiv=LAPACKE_malloc(sizeof(int)*startProdMatr->dim);
	}
	else{
		ipiv=LAPACKE_malloc(sizeof(int)*6);
	}
	if(ipiv==NULL){perror("ipiv malloc comp matrx creation");exit(0);}
	from2Dto1D_double(startProdMatr->matrix[startProdMatr->degree], &modifiedMatrix, startProdMatr->dim, startProdMatr->dim);
	LAPACKE_dgetrf(LAPACK_ROW_MAJOR, startProdMatr->dim, startProdMatr->dim, modifiedMatrix, startProdMatr->dim, ipiv);
	LAPACKE_dgetri(LAPACK_ROW_MAJOR, startProdMatr->dim, modifiedMatrix, startProdMatr->dim, ipiv);
	LAPACKE_free(ipiv);
	modifiedMatrixB=LAPACKE_malloc(sizeof(double)*(startProdMatr->dim)*(startProdMatr->dim));
		if(modifiedMatrixB==NULL){perror("malloc modifiedMatrixB");exit(0);}

	for (i=0 ; i<(startProdMatr->dim)*(startProdMatr->dim) ; i++) {
			modifiedMatrix[i]=modifiedMatrix[i]*(-1);
	}
	for (m=0 ; m<=prodMatr->degree ; m++) {

		from2Dto1D_double(startProdMatr->matrix[m], &modifiedMatrixA, startProdMatr->dim, startProdMatr->dim);
		cblas_dgemm(LAPACK_ROW_MAJOR, CblasNoTrans, CblasNoTrans, prodMatr->dim, prodMatr->dim, prodMatr->dim, 1.0,modifiedMatrix, startProdMatr->dim, modifiedMatrixA, startProdMatr->dim, 0.0, modifiedMatrixB, startProdMatr->dim);
		for(i=0 ; i<prodMatr->dim ; i++){
			for(j=0; j<prodMatr->dim; j++){
				prodMatr->matrix[m][i][j]=modifiedMatrixB[i*(prodMatr->dim)+j];
			}
		}
		free(modifiedMatrixA);

	}
LAPACKE_free(modifiedMatrixB);
	free(modifiedMatrix);
	(*compMatr)=NULL;
	(*compMatr)=malloc(sizeof(struct CompanionMatrix));
	if ((*compMatr)==NULL) {perror("CompanionMatrix struct malloc!");exit(0);}
	subDim=(prodMatr->degree);
	dim=prodMatr->dim;
	compDim=dim*(subDim+1);
	(*compMatr)->dim=compDim;
	(*compMatr)->matrix=NULL;
	(*compMatr)->matrix=malloc(sizeof(double*)*compDim);
	if ((*compMatr)->matrix==NULL) {perror("CompanionMatrix matrix malloc!");exit(0);}
	for (i=0 ; i<compDim ; i++) {
		(*compMatr)->matrix[i]=malloc(sizeof(double)*compDim);
		if ((*compMatr)->matrix[i]==NULL) {perror("CompanionMatrix matrix cell malloc!");exit(0);}
	}

	printf("Dimension of product matrices is: %dx%d, and Sylvester Grade is: %d\n", dim,dim, subDim+1);
	printf("thus dimension of Companion matrix is: %dx%d\n", compDim,compDim);
	for (i=0 ; i<=subDim ; i++) {
		for (j=0 ; j<=subDim ; j++) {
			if (i==subDim){
				for (k=0 ; k<dim ; k++) {
					for (l=0 ; l<dim ; l++) {
						(*compMatr)->matrix[i*dim+k][j*dim+l]=prodMatr->matrix[j][k][l];
					}
				}
			}
			else if (i==j-1) {
				for (k=0 ; k<dim ; k++) {
					for (l=0 ; l<dim ; l++) {
						if (k==l) {
							(*compMatr)->matrix[i*dim+k][j*dim+l]=1.0;
						}
						else {
							(*compMatr)->matrix[i*dim+k][j*dim+l]=0.0;
						}
					}
				}
			}
			else{
				for (k=0 ; k<dim ; k++){
					for (l=0 ; l<dim ; l++){
						(*compMatr)->matrix[i*dim+k][j*dim+l]=0.0;
					}
				}
			}
		}
	}
	destroyProdMatr(prodMatr);
}

int get_Companiondim(CompanionMatrix * comp){	//Gives Companion dimension
	return comp->dim;
}

double ** get_Companionmatrix(CompanionMatrix * comp){	//Returns a pointer to the companion matrix
	return comp->matrix;
}

void printCompanionMatrix(CompanionMatrix * compMatr) {	//Prints Companion matrix
	int i=0, j=0, dim=0;
	printf("---------------------------------------------\n");
	dim=compMatr->dim;
	printf("Dimension of Companion matrix is: %dx%d\n", dim,dim);
	for (i=0 ; i<dim ; i++) {
		for (j=0 ; j<dim ; j++) {
			printf ("%.2f", compMatr->matrix[i][j]);
			printf("|\t");
		}
		printf("\n");
	}
	printf("\n");
	printf("---------------------------------------------\n");
	return;
}



void deleteCompanionMatrix(CompanionMatrix ** compMatr) {	//Destructor
	int i=0, j=0, dim=0;
	dim=(*compMatr)->dim;
	for (i=0 ; i<dim ; i++) {
		free((*compMatr)->matrix[i]);
	}
	free((*compMatr)->matrix);
	free(*compMatr);
	return;
}

void createCMatrix(ProductMatrices * prodMatr, CMatrix ** compMatr) {	//Creates Generalized Problem Matrices
	int dim=0, subDim=0, compDim=0, i=0, j=0, k=0, l=0;
	(*compMatr)=NULL;
	(*compMatr)=malloc(sizeof(struct CMatrix));
	if ((*compMatr)==NULL) {perror("CMatrix struct malloc!");exit(0);}
	subDim=(prodMatr->degree);
	dim=prodMatr->dim;
	compDim=dim*subDim;
	(*compMatr)->dim=compDim;
	(*compMatr)->matrixY=NULL;
	(*compMatr)->matrixY=malloc(sizeof(double*)*compDim);
	if ((*compMatr)->matrixY==NULL) {perror("CMatrix matrixY malloc!");exit(0);}
	for (i=0 ; i<compDim ; i++) {
		(*compMatr)->matrixY[i]=malloc(sizeof(double)*compDim);
		if ((*compMatr)->matrixY[i]==NULL) {perror("CMatrix matrix cell malloc!");exit(0);}
	}
	(*compMatr)->matrix=NULL;
	(*compMatr)->matrix=malloc(sizeof(double*)*compDim);
	if ((*compMatr)->matrix==NULL) {perror("CMatrix matrix malloc!");exit(0);}
	for (i=0 ; i<compDim ; i++) {
		(*compMatr)->matrix[i]=malloc(sizeof(double)*compDim);
		if ((*compMatr)->matrix[i]==NULL) {perror("CMatrix matrix cell malloc!");exit(0);}
	}
	printf("Dimension of product matrices is: %dx%d, and Sylvester Grade is: %d\n", dim,dim, subDim);
	printf("thus dimension of Generalized matrices is: %dx%d\n", compDim,compDim);
	for (i=0 ; i<subDim ; i++) {
		for (j=0 ; j<subDim ; j++) {
			if (i==subDim-1 && j==subDim-1){
				for (k=0 ; k<dim ; k++) {
					for (l=0 ; l<dim ; l++) {
						(*compMatr)->matrixY[i*dim+k][j*dim+l]=prodMatr->matrix[j+1][k][l];
					}
				}
			}
			else if (i==j) {
				for (k=0 ; k<dim ; k++) {
					for (l=0 ; l<dim ; l++) {
						if (k==l) {
							(*compMatr)->matrixY[i*dim+k][j*dim+l]=1.0;
						}
						else {
							(*compMatr)->matrixY[i*dim+k][j*dim+l]=0.0;
						}
					}
				}
			}
			else {
				for (k=0 ; k<dim ; k++) {
					for (l=0 ; l<dim ; l++) {
						(*compMatr)->matrixY[i*dim+k][j*dim+l]=0.0;
					}
				}
			}
		}
	}
	for (i=0 ; i<subDim ; i++) {
		for (j=0 ; j<subDim ; j++) {
			if (i==subDim-1){
				for (k=0 ; k<dim ; k++) {
					for (l=0 ; l<dim ; l++) {
						(*compMatr)->matrix[i*dim+k][j*dim+l]=prodMatr->matrix[j][k][l];
					}
				}
			}
			else if (i==j-1) {
				for (k=0 ; k<dim ; k++) {
					for (l=0 ; l<dim ; l++) {
						if (k==l) {
							(*compMatr)->matrix[i*dim+k][j*dim+l]=-1.0;
						}
						else {
							(*compMatr)->matrix[i*dim+k][j*dim+l]=0.0;
						}
					}
				}
			}
			else {
				for (k=0 ; k<dim ; k++) {
					for (l=0 ; l<dim ; l++) {
						(*compMatr)->matrix[i*dim+k][j*dim+l]=0.0;
					}
				}
			}
		}
	}
	return;
}

int get_Cdim(CMatrix * c){ //Returns Dimension of Generalized Problem Matrices
	return c->dim;
}

double ** get_CmatrixY(CMatrix * c){	//Returns pointer to 1st matrix
	return c->matrixY;
}

double ** get_Cmatrix(CMatrix * c){	//Returns pointer to 2nd matrix
	return c->matrix;
}

void printCMatrix(CMatrix * compMatr) {	//Prints Generalized Problem Matrices
	int i=0, j=0, dim=0;
	printf("---------------------------------------------\n");
	dim=compMatr->dim;
	printf("Dimension of Generalized matrices is: %dx%d\n", dim,dim);
	for (i=0 ; i<dim ; i++) {
		for (j=0 ; j<dim ; j++) {
			printf ("%.2f", compMatr->matrix[i][j]);
			printf("|\t");
		}
		printf("\n");
	}
	printf("\n+y*\n");
	for (i=0 ; i<dim ; i++) {
		for (j=0 ; j<dim ; j++) {
			printf ("%.2f", compMatr->matrixY[i][j]);
			printf("|\t");
		}
		printf("\n");
	}
	printf("\n");
	printf("---------------------------------------------\n");
	return;
}

void deleteCMatrix(CMatrix ** compMatr) { //Destructor
	int i=0, j=0, dim=0;
	dim=(*compMatr)->dim;
	for (i=0 ; i<dim ; i++) {
		free((*compMatr)->matrixY[i]);
	}
	free((*compMatr)->matrixY);
	for (i=0 ; i<dim ; i++) {
		free((*compMatr)->matrix[i]);
	}
	free((*compMatr)->matrix);
	free(*compMatr);
	return;
}
