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
// !((t[2]*real+t[2]*imag+t[3])<=0.00001 && (t[2]*real+t[2]*imag+t[3])>=-0.00001) || 

void changevarback(Gen_sol ** GSol, int t[4]){
	int i=0;
	double real, imag;
	for (i=0 ; i < (*GSol)->dim ; i++) {
		real=(*GSol)->solution[i].value[(*GSol)->p];
		imag=(*GSol)->solution[i].value_imaginary[(*GSol)->p];
		//printf("Changing %i from %f + i* %f (with inf=%d) to ",i,real,imag,(*GSol)->solution[i].inf);
		if( (((t[2]*real+t[3])>0.00001 || (t[2]*real+t[3])<-0.00001) || (t[2]*imag>0.00001 || t[2]*imag<-0.00001) && ((t[2]*real+t[2]*imag+t[3])>0.00001 || (t[2]*real+t[2]*imag+t[3])<-0.00001)) || (((t[0]*real+t[1])>0.00001 || (t[0]*real+t[1])<-0.00001) || (t[0]*imag>0.00001 || t[1]*imag<-0.00001) && ((t[0]*real+t[0]*imag+t[1])>0.00001 || (t[0]*real+t[0]*imag+t[1])<-0.00001)) ){
			(*GSol)->solution[i].value[(*GSol)->p]= t[0]*t[2]*real*real + t[0]*t[3]*real +(-1)*t[0]*t[2]*imag*imag + t[1]*t[2]*real + t[1]*t[3];
			(*GSol)->solution[i].value[(*GSol)->p]=(*GSol)->solution[i].value[(*GSol)->p]/(t[2]*t[2]*real*real + 2*t[2]*t[3]*real+t[3]*t[3] - t[2]*t[2]*imag*imag);
			(*GSol)->solution[i].value_imaginary[(*GSol)->p]= 2*t[0]*t[2]*imag*real + t[0]*t[3]*imag + t[1]*t[2]*imag;
			(*GSol)->solution[i].value_imaginary[(*GSol)->p]=(*GSol)->solution[i].value_imaginary[(*GSol)->p]/(t[2]*t[2]*real*real + 2*t[2]*t[3]*real+t[3]*t[3] - t[2]*t[2]*imag*imag);		//printf(" %f \n ",(*GSol)->solution[i].value[(*GSol)->p]);
		}
		else{
			(*GSol)->solution[i].inf=1;
		}
	}
}
// && ((*GSol)->solution[i].value_imaginary[a]==(*GSol)->solution[i+1].value_imaginary[a]*(-1))
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
	i=0;j=0;
	while(i < eigensol->dim){
			flag=0;
			for(k=0;k<j;k++){
				if(eigensol->solution[i].eigenvalue==(*GSol)->solution[k].value[a] && eigensol->solution[i].eigenvalue_imaginary==(*GSol)->solution[k].value_imaginary[a]){
					flag=1;
					(*GSol)->solution[k].multiplicity=(*GSol)->solution[k].multiplicity+1;
				}
			}
			if(flag==0){
				(*GSol)->solution[j].value[1-a]=eigensol->solution[i].eigenvector.matrix[eigensol->solution[i].eigenvector.dim -2].matrix[0];
				(*GSol)->solution[j].value[a]=eigensol->solution[i].eigenvalue;
				(*GSol)->solution[j].value_imaginary[a]=eigensol->solution[i].eigenvalue_imaginary;
				(*GSol)->solution[j].multiplicity=(*GSol)->solution[j].multiplicity+1;
				(*GSol)->solution[j].inf=eigensol->solution[i].inf;
				
				if(i<eigensol->dim-1 && (*GSol)->solution[i].value_imaginary[a]!=0.0){

					if(eigensol->solution[i-1].eigenvalue-eigensol->solution[i].eigenvalue<=0.00001 && eigensol->solution[i-1].eigenvalue-eigensol->solution[i].eigenvalue>=-0.00001){
						(*GSol)->solution[j-1].value[1-a]=eigensol->solution[i-1].eigenvector.matrix[eigensol->solution[i-1].eigenvector.dim -2].matrix[0];
						(*GSol)->solution[j-1].value_imaginary[1-a]=eigensol->solution[i].eigenvector.matrix[eigensol->solution[i].eigenvector.dim -2].matrix[0];
						(*GSol)->solution[j].value[1-a]=eigensol->solution[i-1].eigenvector.matrix[eigensol->solution[i-1].eigenvector.dim -2].matrix[0];
						(*GSol)->solution[j].value_imaginary[1-a]=eigensol->solution[i].eigenvector.matrix[eigensol->solution[i].eigenvector.dim -2].matrix[0]*(-1);
						printf("Got in here for i=%d eival=%f , eivect=%f\n",i,(*GSol)->solution[j].value[a],(*GSol)->solution[j].value[1-a]);
						//j++; i++;
					}
				}
				j++;
			}
			i++;
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
	for (i=0 ; i<dim ; i++) {(*solution)->solution[i].inf=0;}

	for (i=0 ; i<dim ; i++) {
		temp2[i]=0.0;
		temp3[i]=0.0;
		if ((betaSolution[i]>=0.00001 || betaSolution[i]<=-0.00001)) {
			temp2[i]=realSolution[i]/betaSolution[i];
			temp3[i]=imaginarySolution[i]/betaSolution[i];
			(*solution)->solution[i].inf=0;
		}
		if ((betaSolution[i]<0.00001 && betaSolution[i]>-0.00001)){
			(*solution)->solution[i].inf=1;
		}
	}
		
	for (i=0 ; i<dim ; i++) {
		for (j=0 ; j<dim ; j++) {
			temp1[i*dim+j]=eigenVector[j*dim+i];
			
		}
	}
	
	for (i=0 ; i<dim ; i++) {
		// -> if ((temp1[i*dim+dim/grade-1]>=0.00001 || temp1[i*dim+dim/grade-1]<=-0.00001) && (*solution)->solution[i].inf==0) {
		if (temp1[i*dim+dim/grade-1]!=0.0 && (*solution)->solution[i].inf==0){
			if(imaginarySolution[i]==0.0){
				a=temp1[i*dim+dim/grade-1];
				for (j=0 ; j<grade ; j++) {
					for (k=0 ; k<dim/grade ; k++){
						temp1[i*dim+j*dim/grade+k]=temp1[i*dim+j*dim/grade+k]/a;
					}
				a=a*temp2[i];
				}
			}
			else{
				a=temp1[i*dim+dim/grade-1];
				j=0;
				for (k=0 ; k<dim/grade ; k++){
					temp1[i*dim+j*dim/grade+k]=temp1[i*dim+j*dim/grade+k]/a;
				}
				a=a*temp2[i];
			}
		}
		// -> else if(temp1[i*dim+dim/grade-1]<0.00001 && temp1[i*dim+dim/grade-1]>-0.00001){
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
	double a=0,b=0,c;
	double r1,I1,r2,I2;
	int i;
	printf("---------------------------------------------\n");
	printf("Roots:\n");
	for(i=0;i < GSol->dim; i++){
		if((GSol)->solution[i].inf==0 && (GSol)->solution[i].multiplicity==1){
			if((GSol)->solution[i].value_imaginary[0]==0.0 && (GSol)->solution[i].value_imaginary[1]==0.0){
				printf("Real:\t\t[%f , %f]\t\t\t",(GSol)->solution[i].value[0],(GSol)->solution[i].value[1]);
				if(poly1!=NULL || poly2!=NULL){
					if(poly1!=NULL){
						printf("F(1) value: %f",polyonymtryvalue(poly1, (GSol)->solution[i].value[0], (GSol)->solution[i].value[1]));
					}
					//if(poly1!=NULL && poly2!=NULL){printf(" and ");}
					if(poly2!=NULL){
						printf("\t\t\tF(2) value is %f",polyonymtryvalue(poly2, (GSol)->solution[i].value[0], (GSol)->solution[i].value[1]));
					}
				}
				printf("\n");
			}
			else if((GSol)->solution[i].value_imaginary[0]!=0.0 || (GSol)->solution[i].value_imaginary[1]!=0.0){
				printf("Imaginary:\t");
				printf("[%f",(GSol)->solution[i].value[0]);
				if((GSol)->solution[i].value_imaginary[0]!=0.0){printf(" +i*(%f)",(GSol)->solution[i].value_imaginary[0]);}
				printf(" , %f",(GSol)->solution[i].value[1]);
				if((GSol)->solution[i].value_imaginary[1]!=0.0){printf(" +i*(%f)",(GSol)->solution[i].value_imaginary[1]);}
				printf("]");
				if(poly1!=NULL || poly2!=NULL){
					if(poly1!=NULL){
						polyonymtry_imag_value(poly1, (GSol)->solution[i].value[0], (GSol)->solution[i].value_imaginary[0], (GSol)->solution[i].value[1], (GSol)->solution[i].value_imaginary[1], &r1, &I1);
						printf("\tF(1) value: %f +i*%f",r1,I1);
}
					//if(poly1!=NULL && poly2!=NULL){printf(" and ");}
					if(poly2!=NULL){
						polyonymtry_imag_value(poly2, (GSol)->solution[i].value[0], (GSol)->solution[i].value_imaginary[0], (GSol)->solution[i].value[1], (GSol)->solution[i].value_imaginary[1], &r2, &I2);
						printf("\tF(2) value: %f +i*%f",r2,I2);
					}
				}
				printf("\n");
			}
		}
		else if((GSol)->solution[i].inf==0 && (GSol)->solution[i].multiplicity>1){
			if((GSol)->solution[i].value_imaginary[0]!=0.0 || (GSol)->solution[i].value_imaginary[1]!=0.0 ){
				printf("Imaginary:\t%f +i*(%f) with multiplicity %d \n",(GSol)->solution[i].value[(GSol)->p],(GSol)->solution[i].value_imaginary[(GSol)->p],(GSol)->solution[i].multiplicity);
			}
			else{
				printf("Real:\t\t%f with multiplicity %d \n",(GSol)->solution[i].value[(GSol)->p],(GSol)->solution[i].multiplicity);
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
		if(solution->solution[i].inf==0 && solution->solution[i].eigenvalue_imaginary==0.0){
			printf("=====Vector-%d=====\n",i+1);
			printVector(&(solution->solution[i].eigenvector));
			printf("with Eigenvalue: %f\n",solution->solution[i].eigenvalue);
		}
		else if(solution->solution[i].inf==1){
			printf("=====Vector-%d=====\n",i+1);
			printf("The Eigenvalue is Infinite\n");
		}
		else if(solution->solution[i].eigenvalue_imaginary!=0.0){
			printf("=====Vector-%d=====\n",i+1);
			printVector(&(solution->solution[i].eigenvector));
			printf("with Imaginary Eigenvalue: %f + i*(%f)\n",solution->solution[i].eigenvalue,solution->solution[i].eigenvalue_imaginary);
		}
	}
}
