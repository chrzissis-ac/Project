#include <stdio.h>
#include <stdlib.h>
#include "../headers/ProdMatr.h"
#include "../headers/CompanionMatrix.h"

struct ProductMatrices{
	double *** matrix;
	int dim;
	char hidden;
	int degree;
	double k;
};

struct CompanionMatrixA{
	double ** matrix;
	int dim;
};

struct CompanionMatrixB{
	double ** matrixY;
	double ** matrix;
	int dim;
};

void createCompanionMatrixA(ProductMatrices * startProdMatr, CompanionMatrixA ** compMatr) {
	int dim, subDim, compDim, i, j, k, l;
	printf("Creating companion matrix!\n");
	(*compMatr)=NULL;
	(*compMatr)=malloc(sizeof(struct CompanionMatrixA));
	if ((*compMatr)==NULL) {perror("CompanionMatrixA struct malloc!");exit(0);}
	subDim=(startProdMatr->degree)+1;
	dim=startProdMatr->dim;
	compDim=dim*subDim;
	(*compMatr)->dim=compDim;
	(*compMatr)->matrix=NULL;
	(*compMatr)->matrix=malloc(sizeof(double*)*compDim);
	if ((*compMatr)->matrix==NULL) {perror("CompanionMatrixA matrix malloc!");exit(0);}
	for (i=0 ; i<compDim ; i++) {
		(*compMatr)->matrix[i]=malloc(sizeof(double)*compDim);
		if ((*compMatr)->matrix[i]==NULL) {perror("CompanionMatrixA matrix cell malloc!");exit(0);}
	}
	printf("Dimension of product matrices is: %d, ", dim);
	printf("so dimension of companion matrix is: %d\n", compDim);
	for (i=0 ; i<subDim ; i++) {
		for (j=0 ; j<subDim ; j++) {
			if (i==subDim-1){
				for (k=0 ; k<dim ; k++) {
					for (l=0 ; l<dim ; l++) {
						(*compMatr)->matrix[i*dim+k][j*dim+l]=startProdMatr->matrix[j][k][l];
						//printf("cell: (%d,%d)=", i*dim+k, j*dim+l);
						//printf("%.2f ", (*compMatr)->matrix[i*dim+k][j*dim+l]);
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
						//printf("cell: (%d,%d)=", i*dim+k, j*dim+l);
						//printf("%.2f ", (*compMatr)->matrix[i*dim+k][j*dim+l]);
					}
				}
			}
			else {
				for (k=0 ; k<dim ; k++) {
					for (l=0 ; l<dim ; l++) {
						(*compMatr)->matrix[i*dim+k][j*dim+l]=0.0;
						//printf("cell: (%d,%d)=", i*dim+k, j*dim+l);
						//printf("%.2f ", (*compMatr)->matrix[i*dim+k][j*dim+l]);
					}
				}
			}
		}
	}
	return;
}

void printCompanionMatrixA(CompanionMatrixA * compMatr) {
	int i, j, dim;
	printf("Printing companion matrix!\n");
	dim=compMatr->dim;
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



void deleteCompanionMatrixA(CompanionMatrixA ** compMatr) {
	int i, j, dim;
	printf("Deleting companion matrix!\n");
	dim=(*compMatr)->dim;
	for (i=0 ; i<dim ; i++) {
		free((*compMatr)->matrix[i]);
	}
	free((*compMatr)->matrix);
	free(*compMatr);
	return;
}

void createCompanionMatrixB(ProductMatrices * prodMatr, CompanionMatrixB ** compMatr) {
	int dim, subDim, compDim, i, j, k, l;
	printf("Creating companion matrix!\n");
	(*compMatr)=NULL;
	(*compMatr)=malloc(sizeof(struct CompanionMatrixB));
	if ((*compMatr)==NULL) {perror("CompanionMatrixB struct malloc!");exit(0);}
	subDim=(prodMatr->degree);
	dim=prodMatr->dim;
	compDim=dim*subDim;
	(*compMatr)->dim=compDim;
	(*compMatr)->matrixY=NULL;
	(*compMatr)->matrixY=malloc(sizeof(double*)*compDim);
	if ((*compMatr)->matrixY==NULL) {perror("CompanionMatrixB matrixY malloc!");exit(0);}
	for (i=0 ; i<compDim ; i++) {
		(*compMatr)->matrixY[i]=malloc(sizeof(double)*compDim);
		if ((*compMatr)->matrixY[i]==NULL) {perror("CompanionMatrixB matrix cell malloc!");exit(0);}
	}
	(*compMatr)->matrix=NULL;
	(*compMatr)->matrix=malloc(sizeof(double*)*compDim);
	if ((*compMatr)->matrix==NULL) {perror("CompanionMatrixB matrix malloc!");exit(0);}
	for (i=0 ; i<compDim ; i++) {
		(*compMatr)->matrix[i]=malloc(sizeof(double)*compDim);
		if ((*compMatr)->matrix[i]==NULL) {perror("CompanionMatrixB matrix cell malloc!");exit(0);}
	}
	printf("Dimension of product matrices is: %d, ", dim);
	printf("so dimension of companion matrix is: %d\n", compDim);
	for (i=0 ; i<subDim ; i++) {
		for (j=0 ; j<subDim ; j++) {
			if (i==subDim && j==subDim){
				for (k=0 ; k<dim ; k++) {
					for (l=0 ; l<dim ; l++) {
						(*compMatr)->matrixY[i*dim+k][j*dim+l]=prodMatr->matrix[j+1][k][l];
						//printf("cell: (%d,%d)=", i*dim+k, j*dim+l);
						//printf("%.2f ", (*compMatr)->matrix[i*dim+k][j*dim+l]);
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
						//printf("cell: (%d,%d)=", i*dim+k, j*dim+l);
						//printf("%.2f ", (*compMatr)->matrix[i*dim+k][j*dim+l]);
					}
				}
			}
			else {
				for (k=0 ; k<dim ; k++) {
					for (l=0 ; l<dim ; l++) {
						(*compMatr)->matrixY[i*dim+k][j*dim+l]=0.0;
						//printf("cell: (%d,%d)=", i*dim+k, j*dim+l);
						//printf("%.2f ", (*compMatr)->matrix[i*dim+k][j*dim+l]);
					}
				}
			}
		}
	}
	for (i=0 ; i<subDim ; i++) {
		for (j=0 ; j<subDim ; j++) {
			if (i==subDim){
				for (k=0 ; k<dim ; k++) {
					for (l=0 ; l<dim ; l++) {
						(*compMatr)->matrix[i*dim+k][j*dim+l]=prodMatr->matrix[j][k][l];
						//printf("cell: (%d,%d)=", i*dim+k, j*dim+l);
						//printf("%.2f ", (*compMatr)->matrix[i*dim+k][j*dim+l]);
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
						//printf("cell: (%d,%d)=", i*dim+k, j*dim+l);
						//printf("%.2f ", (*compMatr)->matrix[i*dim+k][j*dim+l]);
					}
				}
			}
			else {
				for (k=0 ; k<dim ; k++) {
					for (l=0 ; l<dim ; l++) {
						(*compMatr)->matrix[i*dim+k][j*dim+l]=0.0;
						//printf("cell: (%d,%d)=", i*dim+k, j*dim+l);
						//printf("%.2f ", (*compMatr)->matrix[i*dim+k][j*dim+l]);
					}
				}
			}
		}
	}
	return;
}

void printCompanionMatrixB(CompanionMatrixB * compMatr) {
	int i, j, dim;
	printf("Printing companion matrix!\n");
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

void deleteCompanionMatrixB(CompanionMatrixB ** compMatr) {
	int i, j, dim;
	printf("Deleting companion matrix!\n");
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
