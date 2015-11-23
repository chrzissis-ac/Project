#include <stdio.h>
#include <stdlib.h>
#include <lapacke.h>
#include <cblas.h>
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
	int inf;
};

struct Eigenstruct{
	CompanionMatrix * Comp;
	CMatrix * C;
	char eigenvar;
	int grade;
	int problemisGen;
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
	if(get_Productdegree(prodMat)==0){return -1;}
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
	if (get_Productk(prodMat) == -1) {
		createCMatrix(prodMat, cMatr);
		eigenstruct->problemisGen=1;
		eigenstruct->grade=get_Productdegree(prodMat);
	}
	else if (get_Productk(prodMat) <= limit) {
		createCompanionMatrix(prodMat, compMatr);
		eigenstruct->problemisGen=0;
		eigenstruct->grade=get_Productdegree(prodMat);
	}
	else if(get_Productk(prodMat) > limit){
		createCMatrix(prodMat, cMatr);
		eigenstruct->problemisGen=1;
		eigenstruct->grade=get_Productdegree(prodMat);
	}
	eigenstruct->eigenvar=get_Producthidden(prodMat);
	if(eigenstruct->problemisGen==0){printf("----------\nEigen-Problem is Standard!\n----------\n");}
	else if(eigenstruct->problemisGen==1){printf("----------\nEigen-Problem is Generalized!\n----------\n");}
	return eigenstruct->problemisGen;
}

void solver(Eigenstruct * eigen, Gen_eigensol ** solution) {
	int i,j;
	double * insertMatrix = NULL;
	double * insertMatrixB = NULL;
	double * realSolution = NULL;
	double * imaginarySolution = NULL;
	double * betaSolution = NULL;
	double * leftEigenvectors = NULL;
	double * rightEigenvectors = NULL;
	//double * temp=NULL;
	//double insertMatrixtemp[3][3]={0,1,1,1,0,1,1,1,0};
	
	if (eigen->problemisGen==0){
		realSolution=LAPACKE_malloc(sizeof(double)*get_Companiondim(eigen->Comp));
		if(realSolution==NULL){perror("malloc realSolution");exit(0);}
		imaginarySolution=LAPACKE_malloc(sizeof(double)*get_Companiondim(eigen->Comp));
		if(imaginarySolution==NULL){perror("malloc imaginarySolution");exit(0);}
		leftEigenvectors=LAPACKE_malloc(sizeof(double)*get_Companiondim(eigen->Comp)*get_Companiondim(eigen->Comp));
		if(leftEigenvectors==NULL){perror("malloc leftEigenvectors");exit(0);}
		rightEigenvectors=LAPACKE_malloc(sizeof(double)*get_Companiondim(eigen->Comp)*get_Companiondim(eigen->Comp));
		if(rightEigenvectors==NULL){perror("malloc rightEigenvectors");exit(0);}
		betaSolution=LAPACKE_malloc(sizeof(double)*get_Companiondim(eigen->Comp));
		if(betaSolution==NULL){perror("malloc betaSolution");exit(0);}

		
		from2Dto1D_double(get_Companionmatrix(eigen->Comp),&insertMatrix,get_Companiondim(eigen->Comp),get_Companiondim(eigen->Comp));
		LAPACKE_dgeev(LAPACK_ROW_MAJOR,'N','V',get_Companiondim(eigen->Comp),insertMatrix,get_Companiondim(eigen->Comp),realSolution,imaginarySolution,leftEigenvectors,get_Companiondim(eigen->Comp),rightEigenvectors,get_Companiondim(eigen->Comp));

		for(i=0;i<get_Companiondim(eigen->Comp); i++){
			imaginarySolution[i]=0.0;
			betaSolution[i]=1.0;
		}
		
		createSolution(solution,get_Companiondim(eigen->Comp),realSolution,imaginarySolution,betaSolution,rightEigenvectors,eigen->eigenvar);
			
	}
	else {
		
		realSolution=LAPACKE_malloc(sizeof(double)*get_Cdim(eigen->C));
		if(realSolution==NULL){perror("malloc realSolution");exit(0);}
		imaginarySolution=LAPACKE_malloc(sizeof(double)*get_Cdim(eigen->C));
		if(imaginarySolution==NULL){perror("malloc imaginarySolution");exit(0);}
		betaSolution=LAPACKE_malloc(sizeof(double)*get_Cdim(eigen->C));
		if(betaSolution==NULL){perror("malloc betaSolution");exit(0);}
		leftEigenvectors=LAPACKE_malloc(sizeof(double)*get_Cdim(eigen->C)*get_Cdim(eigen->C));
		if(leftEigenvectors==NULL){perror("malloc leftEigenvectors");exit(0);}
		rightEigenvectors=LAPACKE_malloc(sizeof(double)*get_Cdim(eigen->C)*get_Cdim(eigen->C));
		if(rightEigenvectors==NULL){perror("malloc rightEigenvectors");exit(0);}

		from2Dto1D_double(get_CmatrixY(eigen->C),&insertMatrix,get_Cdim(eigen->C),get_Cdim(eigen->C));
		from2Dto1D_double(get_Cmatrix(eigen->C),&insertMatrixB,get_Cdim(eigen->C),get_Cdim(eigen->C));
		
		for(i=0;i<get_Cdim(eigen->C) * get_Cdim(eigen->C); i++){insertMatrix[i]=insertMatrix[i]*(-1);}

		LAPACKE_dggev(LAPACK_ROW_MAJOR,'N','V',get_Cdim(eigen->C),insertMatrixB,get_Cdim(eigen->C),insertMatrix,get_Cdim(eigen->C),realSolution,imaginarySolution,betaSolution,leftEigenvectors,get_Cdim(eigen->C),rightEigenvectors,get_Cdim(eigen->C));

				
		createSolution(solution,get_Cdim(eigen->C),realSolution,imaginarySolution,betaSolution,rightEigenvectors,eigen->eigenvar);
		
		free(insertMatrixB);
	}
		free(insertMatrix);
		LAPACKE_free(realSolution);
		LAPACKE_free(imaginarySolution);
		LAPACKE_free(betaSolution);
		LAPACKE_free(leftEigenvectors);
		LAPACKE_free(rightEigenvectors);
}

void createSolution(Gen_eigensol ** solution, int dim, double * realSolution, double * imaginarySolution,double * betaSolution, double * eigenVector,char c) {
	int i,j;
	(*solution)=malloc(sizeof(struct Gen_eigensol));
	if((*solution)==NULL){perror("malloc GeneralSolution");exit(0);}
	(*solution)->solution=malloc(sizeof(struct eigensol)*dim);
	if((*solution)->solution==NULL){perror("malloc Solution");exit(0);}
	double * temp1=NULL;
	temp1=malloc(sizeof(double)*dim*dim);
	if(temp1==NULL){perror("malloc temp1 create solution");exit(0);}
	double * temp2=NULL;
	temp2=malloc(sizeof(double)*dim);
	if(temp2==NULL){perror("malloc temp2 create solution");exit(0);}
	
	for (i=0 ; i<dim ; i++) {
		//printf("1-%.2f + %.2f*i /%.2f , temp[%d]=%f\n",i,realSolution[i],imaginarySolution[i],i,betaSolution[i],i,temp2[i]);
		temp2[i]=0.0;
		if (betaSolution[i]!=0.0 && imaginarySolution[i]==0.0) {
			temp2[i]=realSolution[i]/betaSolution[i];
			(*solution)->solution[i].inf=0;
		}
		else if (imaginarySolution[i]!=0.0){
			(*solution)->solution[i].inf=-1;
		}
		else{
			(*solution)->solution[i].inf=1;
		}
		//printf("2-rSL[%d]=%f + %f*i = bSL[%d]=%f , temp[%d]=%f\n",i,realSolution[i],imaginarySolution[i],i,betaSolution[i],i,temp2[i]);
	}
		
	for (i=0 ; i<dim ; i++) {
		for (j=0 ; j<dim ; j++) {
			temp1[i*dim+j]=eigenVector[j*dim+i];
		}
	}
	
	for (i=0 ; i<dim ; i++) {
			if (temp1[(i+1)*dim-1]!=0.0 && (*solution)->solution[i].inf==0) {
				for (j=0 ; j<dim ; j++) {
					temp1[i*dim+j]=temp1[i*dim+j]/temp1[(i+1)*dim-1];
				}
		}
	}
	for (i=0 ; i<dim ; i++) {
		createStableVector(&((*solution)->solution[i].eigenvector), &(temp1[i*dim]), dim, c);
		(*solution)->solution[i].eigenvalue=temp2[i];
	}
	
	(*solution)->dim=dim;
	free(temp1);
	free(temp2);
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
		if(solution->solution[i].inf==0){
			printf("====Vector-%d=====\n",i+1);
			printVector(&(solution->solution[i].eigenvector));
			if(solution->solution[i].eigenvector.matrix[solution->solution[i].eigenvector.dim-1].matrix[0]==0){
				printf("(Not acceptable)");
			}
			printf("\nwith Eigenvalue: %f\n",solution->solution[i].eigenvalue);
		}
		else if(solution->solution[i].inf==1){
			printf("====Vector-%d=====\n",i+1);
			printVector(&(solution->solution[i].eigenvector));
			printf("(Not acceptable)\n");
			printf("The Eigenvalue is Infinite\n");
		}
		else if(solution->solution[i].inf==-1){
			printf("====Vector-%d=====\n",i+1);
			printVector(&(solution->solution[i].eigenvector));
			printf("(Not acceptable)\n");
			printf("The Eigenvalue is Imaginary\n");
		}
	}
}
