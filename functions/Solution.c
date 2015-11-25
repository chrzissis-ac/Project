#include <stdio.h>
#include <stdlib.h>
#include <lapacke.h>
#include <cblas.h>
#include "../headers/Solution.h"
#include "../headers/Vector.h"

struct Eigenstruct{
	CompanionMatrix * Comp;
	CMatrix * C;
	char eigenvar;
	int grade;
	int problemisGen;
};

struct Gen_eigensol{
	eigensol * solution;
	int dim;
};

struct Vector{
	Polyonym * matrix;
	int dim;
};

struct eigensol{
	Vector eigenvector;
	double eigenvalue;
	double eigenvalue_imaginary;
	int inf;
};

typedef double * Poly;
struct Polyonym{
	Poly matrix;
	char var;
	int d;
};

struct Gen_sol{
	sol * solution;
	int p;
	int dim;
};

struct sol{
	double value[2];
	double value_imaginary[2];
	int multiplicity;
	int inf;
};

void changevarback(Gen_sol ** GSol, int t[4]){
	int i=0;
	double realx, realy, imagx, imagy;
	for (i=0 ; i < (*GSol)->dim ; i++) {
		realx=(*GSol)->solution[i].value[(*GSol)->p];
		//realy=(*GSol)->solution[i].value[1];
		imagx=(*GSol)->solution[i].value_imaginary[(*GSol)->p];
		//imagy=(*GSol)->solution[i].value_imaginary[1];
		if( ((t[2]*realx+t[3])!=0 || (t[2]*imagx!=0)) && ((t[2]*realy+t[3])!=0 || (t[2]*imagy!=0)) ){
			(*GSol)->solution[i].value[(*GSol)->p]= t[0]*t[2]*realx*realx + t[0]*t[3]*realx +(-1)*t[0]*t[2]*imagx*imagx + t[1]*t[2]*realx + t[1]*t[3];
			//(*GSol)->solution[i].value[1]=t[0]*t[2]*realy*realy + t[0]*t[3]*realy +(-1)*t[0]*t[2]*imagy*imagy + t[1]*t[2]*realy + t[1]*t[3];
			(*GSol)->solution[i].value_imaginary[(*GSol)->p]= 2*t[0]*t[2]*imagx*realx + t[0]*t[3]*imagx + t[1]*t[2]*imagx;
			//(*GSol)->solution[i].value_imaginary[1]=2*t[0]*t[2]*imagy*realy + t[0]*t[3]*imagy + t[1]*t[2]*imagy;
		}
		else{
			(*GSol)->solution[i].inf=1;
		}
	}
}

static void createGen_sol(Gen_eigensol * eigensol,Gen_sol ** GSol){
	int i, j=0,k,flag=0,a=0;
	double temp1[eigensol->dim];
	double temp2[eigensol->dim];
	(*GSol)=malloc(sizeof(Gen_sol));
	if((*GSol)==NULL){perror("Gen sol create malloc");exit(0);}
	(*GSol)->solution=NULL;
	(*GSol)->solution=malloc(sizeof(sol) * (eigensol->dim));
	if((*GSol)->solution==NULL){perror("Gen sol - sol create malloc");exit(0);}
	for(i=0;i < eigensol->dim;i++){
		(*GSol)->solution[i].value[0]=0.0;
		(*GSol)->solution[i].value[1]=0.0;
		(*GSol)->solution[i].value_imaginary[0]=0.0;
		(*GSol)->solution[i].value_imaginary[1]=0.0;
		(*GSol)->solution[i].inf=0;
		(*GSol)->solution[i].multiplicity=0;
	}
	if(eigensol->solution[0].eigenvector.matrix[0].var=='x'){a=1;}
	(*GSol)->p=a;
	for(i=0;i < eigensol->dim;i++){
			flag=0;
			for(k=0;k<j;k++){
				if(eigensol->solution[i].eigenvalue==(*GSol)->solution[k].value[a] && eigensol->solution[i].eigenvalue_imaginary==(*GSol)->solution[k].value_imaginary[a]){
				//if(eigensol->solution[i].eigenvalue-(*GSol)->solution[k].value[a]<=0.00000001 && eigensol->solution[i].eigenvalue-(*GSol)->solution[k].value[a]>=-0.00000001){
					flag=1;
					(*GSol)->solution[k].multiplicity=(*GSol)->solution[k].multiplicity+1;
					if((*GSol)->solution[k].inf==0){
						(*GSol)->solution[k].inf=-2;
						(*GSol)->solution[k].value[1-a]=0.0;
						(*GSol)->solution[k].value_imaginary[1-a]=0.0;
					}
				}
			}
			if(flag==0){
				(*GSol)->solution[j].value[1-a]=eigensol->solution[i].eigenvector.matrix[eigensol->solution[i].eigenvector.dim -2].matrix[0];
				(*GSol)->solution[j].value[a]=eigensol->solution[i].eigenvalue;
				(*GSol)->solution[j].value_imaginary[a]=eigensol->solution[i].eigenvalue_imaginary;
				(*GSol)->solution[j].multiplicity=(*GSol)->solution[j].multiplicity+1;
				(*GSol)->solution[j].inf=eigensol->solution[i].inf;
				j++;
			}
	}
	(*GSol)->solution=realloc((*GSol)->solution,sizeof(sol)*j);
	(*GSol)->dim=j;
	
}

static void createSolution(Gen_eigensol ** solution, int dim, int grade, double * realSolution, double * imaginarySolution,double * betaSolution, double * eigenVector,char c) {
	int i,j,k;
	double a,b;
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
	double * temp3=NULL;
	temp3=malloc(sizeof(double)*dim);
	if(temp3==NULL){perror("malloc temp3 create solution");exit(0);}
	
	for (i=0 ; i<dim ; i++) {
		temp2[i]=0.0;
		temp3[i]=0.0;
		if (betaSolution[i]!=0.0 && imaginarySolution[i]==0.0) {
			temp2[i]=realSolution[i]/betaSolution[i];
			(*solution)->solution[i].inf=0;
		}
		else if (imaginarySolution[i]!=0.0){
			temp2[i]=realSolution[i]/betaSolution[i];
			temp3[i]=imaginarySolution[i]/betaSolution[i];
			(*solution)->solution[i].inf=-1;
		}
		if (betaSolution[i]==0.0){
			(*solution)->solution[i].inf=1;
		}
	}
		
	for (i=0 ; i<dim ; i++) {
		for (j=0 ; j<dim ; j++) {
			temp1[i*dim+j]=eigenVector[j*dim+i];
			
		}
	}
	
	for (i=0 ; i<dim ; i++) {
		if (temp1[i*dim+dim/grade-1]!=0.0 && (*solution)->solution[i].inf==0) {
			a=temp1[i*dim+dim/grade-1];
			for (j=0 ; j<grade ; j++) {
				for (k=0 ; k<dim/grade ; k++){
					temp1[i*dim+j*dim/grade+k]=temp1[i*dim+j*dim/grade+k]/a;
				}
			a=a*temp2[i];
			}
		}
		else if(temp1[i*dim+dim/grade-1]==0.0){
			(*solution)->solution[i].inf=-3;
		}
	}
	
	for (i=0 ; i<dim ; i++) {
		createStableVector(&((*solution)->solution[i].eigenvector), &(temp1[i*dim]), dim/grade, c);
		(*solution)->solution[i].eigenvalue=temp2[i];
		(*solution)->solution[i].eigenvalue_imaginary=temp3[i];
	}
	(*solution)->dim=dim;
	free(temp1);
	free(temp2);
	free(temp3);
	return;
}


void printGen_sol(Gen_sol * GSol,Polyonym2 * poly1,Polyonym2 * poly2){
	//double polyonymtryvalue(Polyonym2 * poly, double vx, double vy);
	double a=0,b=0,c;
	int i;
	printf("---------------------------------------------\n");
	printf("Roots:\n");
	for(i=0;i < GSol->dim; i++){
		if((GSol)->solution[i].inf==0){
			printf("Real: (%f , %f)",(GSol)->solution[i].value[0],(GSol)->solution[i].value[1]);
			if(poly1!=NULL || poly2!=NULL){
				if(poly1!=NULL){
					a=polyonymtryvalue(poly1, (GSol)->solution[i].value[0], (GSol)->solution[i].value[1]);
				}
				if(poly2!=NULL){
					b=polyonymtryvalue(poly2, (GSol)->solution[i].value[0], (GSol)->solution[i].value[1]);
				}
				printf(" with function value = %.5f",a-b);
			}
				printf("\n");
		}
		else if((GSol)->solution[i].inf==-2){
			if((GSol)->solution[i].value_imaginary[0]!=0.0 || (GSol)->solution[i].value_imaginary[1]!=0.0 ){
				if((GSol)->solution[i].value_imaginary[0]!=0.0){
					printf("Imaginary: %f +i*(%f) with multiplicity %d \n",(GSol)->solution[i].value[0],(GSol)->solution[i].value_imaginary[0],(GSol)->solution[i].multiplicity);
				}
				else{
					printf("Imaginary: %f +i*(%f) with multiplicity %d \n",(GSol)->solution[i].value[1],(GSol)->solution[i].value_imaginary[1],(GSol)->solution[i].multiplicity);
				}
			}
			else{
				if((GSol)->solution[i].value[1]==0.0){
					printf("Real: %f with multiplicity %d \n",(GSol)->solution[i].value[0],(GSol)->solution[i].multiplicity);
				}
				else{
					printf("Real: %f with multiplicity %d \n",(GSol)->solution[i].value[1],(GSol)->solution[i].multiplicity);
				}
			}
		}
		else if((GSol)->solution[i].inf==-1){
			if((GSol)->solution[i].value_imaginary[0]!=0.0){
				printf("Imaginary: %f +i*(%f)\n",(GSol)->solution[i].value[0],(GSol)->solution[i].value_imaginary[0]);
			}
			else{
				printf("Imaginary: %f +i*(%f)\n",(GSol)->solution[i].value[1],(GSol)->solution[i].value_imaginary[1]);
			}
		}
	}
	printf("---------------------------------------------\n");
}

void deleteGen_sol(Gen_sol ** GSol){
	int i;
	free((*GSol)->solution);
	free((*GSol));

}

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

int chooseMatrix(ProductMatrices * prodMat, Eigenstruct ** eigenstruct, int V) {
	createEigenstruct(eigenstruct);
	CompanionMatrix ** compMatr=&((*eigenstruct)->Comp);
	CMatrix ** cMatr=&((*eigenstruct)->C);
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
		(*eigenstruct)->problemisGen=1;
		(*eigenstruct)->grade=get_Productdegree(prodMat);
	}
	else if (get_Productk(prodMat) <= limit) {
		createCompanionMatrix(prodMat, compMatr);
		(*eigenstruct)->problemisGen=0;
		(*eigenstruct)->grade=get_Productdegree(prodMat);
	}
	else if(get_Productk(prodMat) > limit){
		createCMatrix(prodMat, cMatr);
		(*eigenstruct)->problemisGen=1;
		(*eigenstruct)->grade=get_Productdegree(prodMat);
	}
	(*eigenstruct)->eigenvar=get_Producthidden(prodMat);
	if((*eigenstruct)->problemisGen==0){printf("----------\nEigen-Problem is Standard!\n----------\n");}
	else if((*eigenstruct)->problemisGen==1){printf("----------\nEigen-Problem is Generalized!\n----------\n");}
	return (*eigenstruct)->problemisGen;
}

void solver(Eigenstruct * eigen, Gen_eigensol ** solution, Gen_sol ** GSol) {
	int i,j;
	double * insertMatrix = NULL;
	double * insertMatrixB = NULL;
	double * realSolution = NULL;
	double * imaginarySolution = NULL;
	double * betaSolution = NULL;
	double * leftEigenvectors = NULL;
	double * rightEigenvectors = NULL;
	
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

		createSolution(solution,get_Companiondim(eigen->Comp),eigen->grade,realSolution,imaginarySolution,betaSolution,rightEigenvectors,eigen->eigenvar);
	
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

				
		createSolution(solution,get_Cdim(eigen->C),eigen->grade,realSolution,imaginarySolution,betaSolution,rightEigenvectors,eigen->eigenvar);
		
		free(insertMatrixB);
	}
	createGen_sol(*solution,GSol);
	free(insertMatrix);
	LAPACKE_free(realSolution);
	LAPACKE_free(imaginarySolution);
	LAPACKE_free(betaSolution);
	LAPACKE_free(leftEigenvectors);
	LAPACKE_free(rightEigenvectors);	
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
			printf("=====Vector-%d=====\n",i+1);
			printVector(&(solution->solution[i].eigenvector));
			printf("with Eigenvalue: %f\n",solution->solution[i].eigenvalue);
		}
		else if(solution->solution[i].inf==1){
			printf("=====Vector-%d=====\n",i+1);
//			printVector(&(solution->solution[i].eigenvector));
			printf("The Eigenvalue is Infinite\n");
		}
		else if(solution->solution[i].inf==-1){
			printf("=====Vector-%d=====\n",i+1);
			printVector(&(solution->solution[i].eigenvector));
			printf("with Imaginary Eigenvalue: %f + i*(%f)\n",solution->solution[i].eigenvalue,solution->solution[i].eigenvalue_imaginary);
		}
	}
}
