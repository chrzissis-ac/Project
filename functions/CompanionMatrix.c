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

struct Eigenstruct{
	CompanionMatrix * Comp;
	CMatrix * C;
	int problemisGen;
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

struct Gen_eigensol{
	eigensol * solution;
	int dim;
};

void createEigenstruct(Eigenstruct ** eigenstruct){
	(*eigenstruct)=NULL;
	(*eigenstruct)=malloc(sizeof(Eigenstruct));
	if(*eigenstruct==NULL){perror("malloc Eigenstruct");exit(0);}
	(*eigenstruct)->Comp=NULL;
	(*eigenstruct)->C=NULL;
}

void deleteEigenstruct(Eigenstruct ** eigenstruct){
	if((*eigenstruct)->problemisGen==0){
		deleteCompanionMatrix(&((*eigenstruct)->Comp));
	}
	else if((*eigenstruct)->problemisGen==1){
		deleteCMatrix(&((*eigenstruct)->C));
	}
	free(*eigenstruct);
}

void printEigenstruct(Eigenstruct * eigenstruct){
	if(eigenstruct->problemisGen==1){printCMatrix(eigenstruct->C);}
	else{printCompanionMatrix(eigenstruct->Comp);}

}


int chooseMatrix(ProductMatrices * prodMat, Eigenstruct * eigenstruct, int V) {
	CompanionMatrix ** compMatr=&(eigenstruct->Comp);
	CMatrix ** cMatr=&(eigenstruct->C);
	int K, i;
	double limit;
	limit=1.0;
	if(prodMat->degree==0){return -1;}
	if(V>=0){
		for (i=0 ; i<V ; i++) {
			limit=limit*10.0;
		}
	}
	else{
		for (i=0 ; i>V ; i--) {
			limit=limit/10.0;
		}
	}
	printf("10^B Limit for K is 10^(%d) = %.2f\n",V,limit);
	printf("---------------------------------------------\n");
	if (prodMat->k == -1) {
		createCMatrix(prodMat, cMatr);
		eigenstruct->problemisGen=1;
	}
	else if (prodMat->k <= limit) {
		createCompanionMatrix(prodMat, compMatr);
		eigenstruct->problemisGen=0;
	}
	else if(prodMat->k > limit){
		createCMatrix(prodMat, cMatr);
		eigenstruct->problemisGen=1;
	}
	if(eigenstruct->problemisGen==0){printf("----------\nEigen-Problem is Standard!\n----------\n");}
	else if(eigenstruct->problemisGen==1){printf("----------\nEigen-Problem is Generalized!\n----------\n");}
	return eigenstruct->problemisGen;
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
//	printCompanionMatrix(*compMatr);
	destroyProdMatr(prodMatr);
}

void printCompanionMatrix(CompanionMatrix * compMatr) {
	int i, j, dim;
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
//	printf("Creating companion matrix!\n");
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
void printCMatrix(CMatrix * compMatr) {
	int i, j, dim;
	printf("---------------------------------------------\n");
	dim=compMatr->dim;
	printf("Dimension of Generalized matrices is: %dx%d\n", dim,dim);
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
	printf("---------------------------------------------\n");
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

void solver(Eigenstruct * eigen, Gen_eigensol ** solution) {
	int i;
	double * insertMatrix = NULL;
	double * insertMatrixB = NULL;
	double * realSolution = NULL;
	double * imaginarySolution = NULL;
	double * betaSolution = NULL;
	double * leftEigenvectors = NULL;
	double * rightEigenvectors = NULL;
	if (eigen->problemisGen==0) {
		realSolution=LAPACKE_malloc(sizeof(double)*(eigen->Comp->dim));
		if(realSolution==NULL){perror("malloc realSolution");exit(0);}
		imaginarySolution=LAPACKE_malloc(sizeof(double)*(eigen->Comp->dim));
		if(imaginarySolution==NULL){perror("malloc imaginarySolution");exit(0);}
		leftEigenvectors=LAPACKE_malloc(sizeof(double)*(eigen->Comp->dim*eigen->Comp->dim));
		if(leftEigenvectors==NULL){perror("malloc leftEigenvectors");exit(0);}
		rightEigenvectors=LAPACKE_malloc(sizeof(double)*(eigen->Comp->dim*eigen->Comp->dim));
		if(rightEigenvectors==NULL){perror("malloc rightEigenvectors");exit(0);}
		from2Dto1D_double(eigen->Comp->matrix,&insertMatrix,eigen->Comp->dim,eigen->Comp->dim);

		LAPACKE_dgeev(LAPACK_ROW_MAJOR,'N','V',1,insertMatrix,eigen->Comp->dim,realSolution,imaginarySolution,leftEigenvectors,eigen->Comp->dim,rightEigenvectors,eigen->Comp->dim);
		createSolution(solution,eigen->Comp->dim,realSolution,rightEigenvectors,'a');
		
		free(insertMatrix);
		LAPACKE_free(realSolution);
		LAPACKE_free(imaginarySolution);
		LAPACKE_free(leftEigenvectors);
		LAPACKE_free(rightEigenvectors);
	}
	else {
		realSolution=LAPACKE_malloc(sizeof(double)*(eigen->C->dim));
		if(realSolution==NULL){perror("malloc realSolution");exit(0);}
		imaginarySolution=LAPACKE_malloc(sizeof(double)*(eigen->C->dim));
		if(imaginarySolution==NULL){perror("malloc imaginarySolution");exit(0);}
		betaSolution=LAPACKE_malloc(sizeof(double)*(eigen->C->dim));
		if(betaSolution==NULL){perror("malloc betaSolution");exit(0);}
		leftEigenvectors=LAPACKE_malloc(sizeof(double)*(eigen->C->dim*eigen->C->dim));
		if(leftEigenvectors==NULL){perror("malloc leftEigenvectors");exit(0);}
		rightEigenvectors=LAPACKE_malloc(sizeof(double)*(eigen->C->dim*eigen->C->dim));
		if(rightEigenvectors==NULL){perror("malloc rightEigenvectors");exit(0);}

		from2Dto1D_double(eigen->C->matrixY,&insertMatrix,eigen->C->dim,eigen->C->dim);
		from2Dto1D_double(eigen->C->matrix,&insertMatrixB,eigen->C->dim,eigen->C->dim);
		LAPACKE_dggev(LAPACK_ROW_MAJOR,'N','V',1,insertMatrix,eigen->C->dim,insertMatrixB,eigen->C->dim,realSolution,imaginarySolution,betaSolution,leftEigenvectors,eigen->C->dim,rightEigenvectors,eigen->C->dim);
		for (i=0 ; i<eigen->C->dim ; i++) {
			if (betaSolution[i]!=0.0) {
				realSolution[i]=realSolution[i]/betaSolution[i];
			}
		}
		createSolution(solution,eigen->C->dim,realSolution,rightEigenvectors,'a');
		free(insertMatrix);
		free(insertMatrixB);
		LAPACKE_free(realSolution);
		LAPACKE_free(imaginarySolution);
		LAPACKE_free(betaSolution);
		LAPACKE_free(leftEigenvectors);
		LAPACKE_free(rightEigenvectors);
	}
	return;
}
