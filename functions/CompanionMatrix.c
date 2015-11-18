#include <stdio.h>
#include <stdlib.h>
#include <lapacke.h>
#include <cblas.h>
#include "../headers/ProdMatr.h"
#include "../headers/CompanionMatrix.h"

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

int chooseMatrix(ProductMatrices * prodMat, CompanionMatrix ** compMatr, CMatrix ** cMatr, int V) {
	int K, i;
	double limit;
	limit=1.0;
	if(prodMat->degree==0){return -1;}
	for (i=0 ; i<V ; i++) {
		limit=limit*10.0;
	}
	printf("Limit is %.2f\n",limit);
	if (prodMat->k == -1) {
		createCMatrix(prodMat, cMatr);
		return 1;
	}
	else if (prodMat->k <= limit) {
		printf("here i go\n");
		createCompanionMatrix(prodMat, compMatr);
		return 0;
	}
	else if(prodMat->k > limit){
		createCMatrix(prodMat, cMatr);
		return 1;
	}
}

void createCompanionMatrix(ProductMatrices * startProdMatr, CompanionMatrix ** compMatr) {
	int dim, subDim, compDim, i, j, k, l, m;
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
			printf("MDM[%d] = %.2f",i,modifiedMatrix[i]);
			modifiedMatrix[i]=modifiedMatrix[i]*(-1);
			printf("MDM[%d] = %.2f\n",i,modifiedMatrix[i]);
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
	printf("Dimension of product matrices is: %d, and degree is: %d ", dim, subDim+1);
	printf("so dimension of companion matrix is: %d\n", compDim);
	for (i=0 ; i<=subDim ; i++) {
		for (j=0 ; j<=subDim ; j++) {
			if (i==subDim){
				for (k=0 ; k<dim ; k++) {
					for (l=0 ; l<dim ; l++) {
						printf("Copying %.2f to element [%d][%d]\n",prodMatr->matrix[j][k][l],i*dim+k,j*dim+l);
						(*compMatr)->matrix[i*dim+k][j*dim+l]=prodMatr->matrix[j][k][l];
					}
				}
			}
			else if (i==j-1) {
				for (k=0 ; k<dim ; k++) {
					for (l=0 ; l<dim ; l++) {
						if (k==l) {
							printf("Putting 1 to element [%d][%d]\n",i*dim+k,j*dim+l);
							(*compMatr)->matrix[i*dim+k][j*dim+l]=1.0;
						}
						else {
							printf("Putting 0 to element [%d][%d] - case 1\n",i*dim+k,j*dim+l);
							(*compMatr)->matrix[i*dim+k][j*dim+l]=0.0;
						}
					}
				}
			}
			else{
				for (k=0 ; k<dim ; k++){
					for (l=0 ; l<dim ; l++){
						printf("Putting 0 to element [%d][%d] - case 2\n",i*dim+k,j*dim+l);
						(*compMatr)->matrix[i*dim+k][j*dim+l]=0.0;
					}
				}
			}
		}
	}
	printCompanionMatrix(*compMatr);
	destroyProdMatr(prodMatr);
}

void printCompanionMatrix(CompanionMatrix * compMatr) {
	int i, j, dim;
	printf("Printing companion matrix!\n");
	dim=compMatr->dim;
	for (i=0 ; i<dim ; i++) {
		for (j=0 ; j<dim ; j++) {
			printf ("%.2f", compMatr->matrix[i][j]);
			printf("|\t");
		}
		printf("-->\n");
	}
	printf("\n");
	return;
}



void deleteCompanionMatrix(CompanionMatrix ** compMatr) {
	int i, j, dim;
	dim=(*compMatr)->dim;
	for (i=0 ; i<dim ; i++) {
		free((*compMatr)->matrix[i]);
	}
	free((*compMatr)->matrix);
	free(*compMatr);
	return;
}

void createCMatrix(ProductMatrices * prodMatr, CMatrix ** compMatr) {
	int dim, subDim, compDim, i, j, k, l;
	printf("Creating companion matrix!\n");
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
	printf("Dimension of product matrices is: %d and degree is: %d, ", dim, subDim);
	printf("so dimension of C matrix is: %d\n", compDim);
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
void printCMatrix(CMatrix * compMatr) {
	int i, j, dim;
	printf("Printing C matrices!\n");
	dim=compMatr->dim;
	for (i=0 ; i<dim ; i++) {
		for (j=0 ; j<dim ; j++) {
			printf ("%.2f", compMatr->matrixY[i][j]);
			printf("|\t");
		}
		printf("\n");
	}
	printf("\n            +\n");
	for (i=0 ; i<dim ; i++) {
		for (j=0 ; j<dim ; j++) {
			printf ("%.2f", compMatr->matrix[i][j]);
			printf("|\t");
		}
		printf("\n");
	}
	printf("\n");
	return;
}

void deleteCMatrix(CMatrix ** compMatr) {
	int i, j, dim;
//	printf("Deleting companion matrix!\n");
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
