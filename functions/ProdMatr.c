#include <stdio.h>
#include <stdlib.h>
#include <lapacke.h>


#include "../headers/ProdMatr.h"
#include "../headers/Sylvester.h"
#include "../headers/SimplePoly.h"
#include "../headers/Routines.h"

typedef double * Poly;
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
	double *** matrix;
	int dim;
	char hidden;
	int degree;
	double k;
};

//---------------------------------------------------------Product matrices of Sylvester management--------------------------------------------------

// createProdMatr() creates a ProductMatrices struct  ('prodMat') and its matrices[i] are filled with the coefficients of hidden variable ^ i that are stored in the matrix of 'sylvester'
void createProdMatr (Sylvester * sylvester, ProductMatrices ** prodMat){
//	printf("Creating Product Matrices!\n");
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
	(*prodMat)->k=-1;
	calculate_K(*prodMat);
//	printf("Created Product Matrices!\n");
	return;
}

// printProdMatr() prints the matrix['in'] of 'prodMat'
void printProdMatr(ProductMatrices * prodMat, int in) {
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
				printf("%.2f", (prodMat->matrix[i][j][k]));
				printf("|\t");
			}
			printf("\n");
		}
		printf("\n");
	printf("With dimension %dx%d.\n",prodMat->dim,prodMat->dim);
	return;
}

// printProdMatr_int() prints the matrix['in'] of 'prodMat' as integers
void printProdMatr_int (ProductMatrices * prodMat, int in) {
	printf("---------------------------------------------\n");
	if(in>prodMat->degree || in<0){
		printf("There is no %d grade in the Sylvester Product Matrices!\n",in);
		printf("---------------------------------------------\n");
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
	printf("---------------------------------------------\n");
	return;
}

// destroyProdMatr() frees the memory that was allocated for 'prodMat'
void destroyProdMatr (ProductMatrices * prodMat){
	if(prodMat==NULL){return;}
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

int calculate_K(ProductMatrices * prodMat){
//	printf("Calculating K!\n");
	double * matrix=NULL;
	double * sva=NULL;
	double * stat=NULL;
	double * v=NULL;
	int i=0;
	int ldv=prodMat->dim;
	double maxs=0,mins=0,info=0;
	sva=LAPACKE_malloc(sizeof(double)*(prodMat->dim));
	if(sva==NULL){perror("LAPACKE malloc sva to calc K failed");exit(0);}
	stat=LAPACKE_malloc(sizeof(double)*(prodMat->dim)*2);
	if(stat==NULL){perror("LAPACKE malloc stat to calc K failed");exit(0);}

	from2Dto1D_double( prodMat->matrix[prodMat->degree], &matrix, prodMat->dim, prodMat->dim);
	
	info=LAPACKE_dgesvj(LAPACK_ROW_MAJOR, 'G','N', 'N', prodMat->dim, prodMat->dim, matrix, prodMat->dim, sva, 0, v, ldv, stat);

	maxs=sva[0];
	mins=sva[0];
	i=1;
	while(i<prodMat->dim){
		if(maxs<sva[i]){maxs=sva[i];}
		if(mins>sva[i]){mins=sva[i];}
		i++;
	}
	
	printf("Singular Values:\n");
	printf("Max Singular value is %f\n",maxs);
	printf("Min Singular value is %f\n",mins);
	if(mins==0){
		prodMat->k=-1;
		printf("K is infinity.\n");
	}
	else{
		prodMat->k=maxs/mins;
		printf("K is %f\n",prodMat->k);
	}
	printf("---------------------------------------------\n");
	free(matrix);
	LAPACKE_free(sva);
	LAPACKE_free(stat);
	LAPACKE_free(v);
}

void multProdMatr(ProductMatrices ** target, Polyonym * poly, ProductMatrices * prodMat, int g){
	int i=0,j=0,m=0;
	(*target)=NULL;
	(*target)=malloc(sizeof(ProductMatrices));
	if((*target)==NULL){perror("prod matrices multiplication malloc");exit(0);}
	(*target)->dim=prodMat->dim;
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
				(*target)->matrix[m][i][j]=(prodMat->matrix[g][i][j])*get1NumByDegree(poly, m);
				//printf("pollaplasiasmos: %d= %d*%d // m=%d,i=%d,j=%d\n",(*target)->matrix[m][i][j],prodMat->matrix[g][i][j],get1NumByDegree(poly,m),m,i,j);
			}
		}
	}
}

void addProdMatr(ProductMatrices ** target, ProductMatrices * matrix1, ProductMatrices * matrix2){
	int i=0,j=0,m=0;
	(*target)=NULL;
	(*target)=malloc(sizeof(ProductMatrices));
	if((*target)==NULL){perror("prod matrices add malloc");exit(0);}
	(*target)->dim=matrix1->dim;
	(*target)->hidden=matrix1->hidden;
	(*target)->degree=matrix1->degree;
	(*target)->matrix=NULL;
	(*target)->matrix=malloc(sizeof(double**)*((*target)->degree+1));
	if ((*target)->matrix==NULL) {perror("Product Matrices add malloc!");exit(0);}
	for (i=0 ; i<=(*target)->degree ; i++) {
		(*target)->matrix[i]=NULL;
		(*target)->matrix[i]=malloc(sizeof(double*)*(*target)->dim);
		if ((*target)->matrix[i]==NULL) {perror("Product Matrices add 1D malloc!");exit(0);}
		for (j=0 ; j<(*target)->dim ; j++) {
			(*target)->matrix[i][j]=NULL;
			(*target)->matrix[i][j]=malloc(sizeof(double)*(*target)->dim);
			if ((*target)->matrix[i][j]==NULL) {perror("Product add 2D malloc!");exit(0);}
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

void create_newProd(ProductMatrices ** finl, ProductMatrices * prodMat){
	if(prodMat->degree==0){
		printf("The grade of Mi is zero (0)\n");
		return;
	}
	int t1=rand()%30 +1;
	int t2=rand()%30 +1;
	int t3=rand()%30 +1;
	int t4=rand()%30 +1;	
	printf("For t1=%d , t2=%d, t3=%d, t4=%d\n",t1,t2,t3,t4);
	int i=0, a=0,b=0,j=0;
	ProductMatrices * target[prodMat->degree+1];
	ProductMatrices * tempprod=NULL;
	Polyonym * temp=NULL;
	Polyonym * fin=NULL;
	Polyonym * poly1=NULL;
	Polyonym * poly2=NULL;
	poly1=malloc(sizeof(Polyonym));
	if(poly1==NULL){perror("malloc poly1 newprod");exit(0);}
	poly2=malloc(sizeof(Polyonym));
	if(poly2==NULL){perror("malloc poly2 newprod");exit(0);}
	poly1->d=1;
	poly2->d=1;
	poly1->var='z';
	poly2->var='z';
	poly1->matrix=NULL;
	poly1->matrix=malloc(sizeof(double)*2);
	if(poly1->matrix==NULL){perror("new prod polyonym malloc matrix1");exit(0);}
	poly2->matrix=NULL;
	poly2->matrix=malloc(sizeof(double)*2);
	if(poly2->matrix==NULL){perror("new prod polyonym malloc matrix2");exit(0);}

	change1polyonym(poly1,0,t2);
	change1polyonym(poly1,1,t1);
	change1polyonym(poly2,0,t4);
	change1polyonym(poly2,1,t3);

	i=0;
	while(i<=prodMat->degree){
		create1polyonym_one(&temp,'z');
		a=0;b=0;
		while(a<i){
			if(a!=0){
				delete1polyonym(temp);
				temp=fin;
			}
			mult_polyonym1polyonym(&fin, temp, poly2);
			a++;
		}
		while(b<prodMat->degree-i){
			if(b+a!=0){
				delete1polyonym(temp);
				temp=fin;
			}
			mult_polyonym1polyonym(&fin, temp, poly1);
			b++;
		}
		delete1polyonym(temp);
		multProdMatr(&(target[i]), fin, prodMat, i);
		delete1polyonym(fin);
		i++;
	}

	addProdMatr(finl, target[0], target[1]);
	i=2;
	while(i<=prodMat->degree){
		if(tempprod!=NULL){destroyProdMatr(tempprod);}
		tempprod=*finl;
		addProdMatr(finl, tempprod, target[i]);
		i++;
	}

	if(tempprod!=NULL){destroyProdMatr(tempprod);}
	delete1polyonym(poly1);
	delete1polyonym(poly2);
	i=0;
	while(i<=prodMat->degree){
		destroyProdMatr(target[i]);
		i++;
	}
	calculate_K(*finl);
}

int changeofvar3(ProductMatrices ** finl, ProductMatrices * prodMat){
	int i=0;
	if(prodMat->degree==0){
		printf("The grade of Mi is zero (0)\n");
		*finl=prodMat;
		return 0;
	}
	do{
		create_newProd(finl,prodMat);
		i++;
		if( (prodMat->k==-1 && (*finl)->k>=0) || (prodMat->k>=0 && (*finl)->k<prodMat->k) ){break;}
		destroyProdMatr (*finl);
		*finl=NULL;
	}while(i<3);
	if(*finl!=NULL){
		printf("Changed variable to z!\n");
		printf("---------------------------------------------\n");
		return 1;
	}
	*finl=prodMat;
	return 0;



}
